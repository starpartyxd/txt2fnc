# txt2fnc
txt2fnc is a tool allows a user to input text, which is then converted into reverse byte (little endian) order into a “fake function” with the ARM naked attribute (a function without the stack prologue/epilogue). By using a pointer to the function, one is able to print the function as a string. The idea behind it was to find a way to fool disassemblers and keep data hidden, which originated from [this](https://www.evilsocket.net/2015/05/02/using-inline-assembly-and-naked-functions-to-fool-disassemblers/) blog post.

In the event that you are unsure of the text you entered, a custom comment of said text is created above the function for easy reference in both versions. Once you've finalized what you want to use for your function, pass a pointer to it in order to display it. This tool is very much an example based on the post specified above and it is bare bones in terms of functionality.

# Dependencies
* vue.js 1.0.20 or later

# Usage
Included are two variations.

* One that can be compiled as a standalone C program which will output a .h file containing the function to be included in your main program.
    > Usage: txt2fnc fnc_name "text goes here"

* The other is a vue app which achieves the same result, however it displays output directly on the page instead of outputting to a file. A sample snippet to include this exists below. Copy it where you wish to utilize it along with a reference to vue.js to get started.

# Compiling

	git clone https://github.com/0xviviani/txt2fnc
	cd txt2fnc/src/c
	gcc txt2fnc.c -o txt2fnc
	
# Setting up the vue app

	<div id="app">
		<p>Function name: </p>
		<textarea v-model="fncIn" v-on:keyup="start" v-on:keydown="start"></textarea>
		<p>Text input: </p>
		<textarea v-model="strIn" v-on:keyup="start" v-on:keydown="start"></textarea>
		<span><p style="text-align:left">Output: <pre style="text-align:left;white-space: pre-line">{{{res}}}</pre></p>
	</div>

![txt2fnc](https://i.imgur.com/sSLioFw.gifv)