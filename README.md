txt2fnc is a tool allows a user to input text, which is then converted into reverse byte (little endian) order into a “fake function” with the ARM naked attribute (a function without the stack prologue/epilogue). By using a pointer to the function, one is able to print the function as a string. The idea behind it was to find a way to fool disassemblers and keep data hidden, which originated from this blog post.

# Usage
========
Included are two variations. One that can be compiled as a standalone C program which will output a .h file containing the function to be included in your main program. The other is a vue.js app which achieves the same result. In the event that you are unsure of the text you entered, a custom comment of said text is created above the function for easy reference in both versions.

Once you've finalized what you want to use for your function, pass a pointer to it in order to display it. If there are any bugs, please open and issue so I can look into it.

Example 1
=========
String: "Hello world!"

Arguments: txt2fnc out text_function Hello World!

Example 2
=========
If you want to include optional extra spaces in your text, use " AFTER the last word/character, followed by the number of spaces, followed by " to finish.
Lets say we want to use 3 spaces between "Hello" and "World!".

String: "Hello"   "world!"

Arguments: txt2fnc out text_function Hello"   "World!