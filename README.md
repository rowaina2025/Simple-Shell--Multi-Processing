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
## Commands Supported:
#### Executable commands in the system:
1. The internal shell command "exit" which terminates the shell
2. Commands with no arguments, for exmaple: `ls, cp, rm, pwd`
3. Commands with arguments, for example `ls -l -s`.

#### Built-in:
1. Commands with or without arguments, executed in the backgrounf using `&`, example `gedit & ` 
2. **cd** changes directory:
    * cd
    * cd ~
    * cd ..
    * cd absolute_path
    * cd relative_path_to_current_working_directory
3. **echo** Prints the input after evaluating all expressions:
    * echo "Hello" => Hello
    * export x=5
    * echo "Hello $x" => Hello 5
4. **export** Set values to variables and print variables values:
    Details: Accepts input of two forms, either a string without spaces, or a full string inside double quotations. No mathematical operations are supported.
    * export x=-l
    * ls $x => Will perform ls -l
    * export y="Hello world"
    * echo "$y" => Hello world
## System calls used:
- **execvp()**
- **waitpid()**
- **fork()**
- **exit()**
- **chdir()**

> No Zombie Processes can exist as ``'SIGCHLD'`` signal is assigned at the baginning of the program which interrups the parent process to kill that child on termination.

##### Thank you for taking the time to read this README file!  

