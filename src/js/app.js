new Vue({
  el: '#app',
  data: {
	  fncIn: '',
    strIn: '',
    res: "You didn't enter anything",
  },
  methods: {
    reverseString: function(str) {
      var i;
      var tmpStr = "";
      var len = str.length - 1;

      for(i = len; i >= 0; i--) {
        tmpStr += str.charCodeAt(i).toString(16);
      }

      return tmpStr;
    },
    htmlspecialchars: function(str) {
      if (typeof(str) == "string") {
        /* must do &amp; first */
        str = str.replace(/&/g, "&amp;");
        str = str.replace(/"/g, "&quot;");
        str = str.replace(/'/g, "&#039;");
        str = str.replace(/</g, "&lt;");
        str = str.replace(/>/g, "&gt;");
      }
    return str;
  },
    start: function() {
      var i;
      var blocks;
      var alignSize = 4;
      var fncStr = "";
      var blankStr = "";
      var finalStr = "";
      var maxFLen = 1024 / 64;
      var maxSLen = 1024;
      var fncLen = this.fncIn.length;
      var strLen = this.strIn.length;
      var arr = new Array();

      // Verify the function and text string lengths
      if((fncLen == 0 || strLen == 0) || (fncLen == 0 && strLen == 0)) {
        this.res = "You didn't enter anything";
        return;
      } else if((fncLen >= maxFLen) || (strLen >= maxSLen)) {
        this.res = "Function or Text string is too long!<br>Max function length: " + maxFLen + "<br>Max text length: " + 
          maxSLen + "<br>Function length: " + fncLen + "<br>Text length: " + strLen;
        return;
      }
      
      // Clear out previous output
      this.res = 'Clear!';

      // Validate the number of blocks.
      // Make sure the string size is divisible by alignment size. If not, add another block to print the remaining data.
      if(strLen % alignSize == 0) {
        blocks = Math.floor((strLen / alignSize));
      } else {
        blocks = Math.floor((strLen / alignSize)) + 1;

      // Assuming len is not a multiple of the alignment size, let's append bytes to it. Using 0x00 assures it doesn't get printed after the initial string.
        do{
          blankStr += "\x00" + "\x00";
          strLen++;
        } while(strLen % alignSize != 0)
      }

      this.res += "blocks: " + blocks;

      // Print the header
      this.res = "/**<br>";
      this.res += ' * Function containing text "'
      this.res += this.htmlspecialchars(this.strIn);
      this.res += '"<br>';
      this.res += "*/<br>";
      this.res += "__attribute__ ((naked)) ";
      this.res += this.htmlspecialchars(this.fncIn);
      this.res += "(void) {<br>";

      // Reverses the entire string.
      finalStr = this.strIn + blankStr;
      var revStr = this.reverseString(finalStr);

      // Cycle through and print the hex.
      for(i = blocks * 8; i > 0; i -= 8) {
        this.res += '&nbsp&nbsp&nbspasm (".long ';
        this.res += revStr.substring(i-8, i) + '");<br>' ;
      }

      // Write out the tail.
      this.res += "}";
    }
  }
})