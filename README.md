txt2fnc
=======
This tool was created in my spare time. It allows you to enter text and create a function based off of said text in reverse byte order for use in ARM C/C++ development.

Compile it, enter a function name and some text. A ".h" file will be created to be used in your program based on what you entered. In the event that you are unsure of if the text you entered properly is what you want, a custom comment of said text is created above the function for easy reference.

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

What's next?
============
Simply include your header file into your program. Slap a char pointer to the function address and pass it to printf. Voila, you are now able to print functions as if they were text without doing conversions by hand.

This also has other uses, but it requires out-of-the box thinking. Good luck.


Please report any bugs to tshomega@gmail.com
