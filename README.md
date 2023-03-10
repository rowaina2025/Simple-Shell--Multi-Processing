# Simple shell application (Multi-processing)
Simple shell developed with `C language`. 
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
$ gcc -c builtin_shell.c
```
3. Link the object files together using the C compiler with the -o option to create an executable file:
```
$ gcc -o <any_chosen_name>.o lab1.o utilities.o builtin_shell.o
```  
4. Run the executable file by typing its name in the terminal. 
```
$ ./<the_chosen_name>
```
Now the shell is running the program!
