This is the Lexical Analyzer for Project 1
CS 460 - Spring 2016.

Written by: Mackenzie Larson 

What works:
My program successfully recognizes lexemes for identifiers, numeric literals, and symbols listed on the document we discussed in class.
It opens an input file and creates dbg and lst files. 
It handles errors and prints error messages/ what the error was to the terminal and to the dbg and lst files. 
It also counts and identifies the number of errors that occur in the file correctly. 

What doesn't work:
My output is slighly off. Comments and errors throw off my line count (varies case by case). The first line after a comment that is not a comment will share the same line number as the line before it. I am also not sure if comments should display the new line token after them (my program does) as there is a new line at the end of each comment so I left it in. (The reason why I am noting this issue is because the expected output sheet did not display the new line after comments). 

