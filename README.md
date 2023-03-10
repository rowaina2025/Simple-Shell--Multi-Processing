# Simple shell application (Multi-processing)
Simple shell developed with `C language`. 
[![termial_demo](https://i.postimg.cc/RhdJ3BYh/termial1.jpg)](https://postimg.cc/QKBdPRhZ)
## System Requirements
This shell application has been tested on Ubuntu 22.04. However, it should work on any Unix-like operating system.
## How to use
Since the code is divided into three files you have to follow those steps in system terminal:
1. Navigate to the directory that contains the source files (c_files directory) in the terminal using the cd command:
```
$ cd /path/to/source/c_files
```
2. Compile each source file separately using the C compiler gcc with the -c option to create object files:
```
$ gcc -c lab.c
$ gcc -c utilities.c
$ gcc -c builtin_shell
```
3. Link the object files together using the C compiler with the -o option to create an executable file:
```
$ gcc -o <any_chosen_name> lab1.o utilities.o builtin_shell.o
```  
4. Run the executable file by typing its name in the terminal. 
```
$ ./<the_chosen_name>
```
Now the terminal is running the program!
#### Another way to run it:
You can however run the program in the IDE terminal, for example `CLion` which was used to test the program during the development.
