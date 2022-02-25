**Welcome to Ssshhelll!!**

**Steps to Run The Shell :**

- Clone the repository into the system.
- cd into the corresponding directory.
- run `make`
- run `make clean` to remove all object files.
- use `./ashell` to run the shell.
- To exit the shell use quit/q/exit.

Note : 
- Run the shell in the directory that it has been cloned into. 
- The home directory for commands are considered to be the directory where we run the shell.

**Files and functions :**

**Supporting Files :**

- main.c - Calls the prompt() from prompt.c and calls tokenize() which takes input string as argument and does the tokenizing and executing the command.
- prompt.c - Does the printing work on Shell regarding hostname, current directory and machine name.
- tokenize.c - Does all the tokenizing the string, removing the unnecessary spaces/tabs to check and run the command asked for.
- utils.c - It contains supporting functions for the commands implemented.

**Command Files :**

- pwd.c - calls the `pwd` function.
- echo.c - calls the `echo` function with the required string.
- cd.c - calls the `cd` function which helps in navigating between different directories.
- ls.c - calls the `ls` function which helps in listing files and directories according to different flags.
- repeat.c - calls the `repeat` function which runs the input shell command the number of times mentioned.
- pinfo.c - helps in calling the `pinfo` command which gives details about the process.
- history.c - Adds commands to a file history.txt and keeps record of the last 20 commands. It loads and writes the history.txt at appropriate times. Helps in executing the `history` command.
- bg.c - Implements `bg` command which changes the state of a stopped background job to running in the background.
- fg.c - Implements `fg` command which brings the running or stopped background job corresponding to ​job number​ to the foreground, and changes its state to ​running.
- jobs.c - Implements `jobs` command which prints list of commands in alphabetical order with their information.
- pipe.c - Does the parsing work of string and handles the implementation and errors related to piping and calls command_to_exec function to perform the task.
- redirection.c - Handles the redirection part of the string and also helps in implementing piping with redirection.
- replay.c - Implement a `replay` command which executes a particular command in fixed time interval for a certain period.
- sig.c - Implements `sig` command which sends the specified signal to the process with specified job number.

**Commands implemented :**

- `cd` : cd command changes the directory. The cd command has been implemented with the flags -  { cd . , cd .. , cd - , cd ~ , cd `<directory>` }.
- `pwd` : pwd helps in printing the absolute path of the current working directory.
- `ls` : ls helps in listing all the files and directories under the current working directory. The ls command has been implemented with the flags - { ls , ls -a , ls -l , ls -al , ls -la , ls ~ , ls . , ls .. , ls <directory> }.
- `echo` - echo helps in printing a string on the terminal, it neglects tabs and spaces. echo with no arguments prints a blank new line.

      Usage :  echo string

- `pinfo` : pinfo command can be used as pinfo(lists process info for shell itself) or pinfo `<pid>`. The pinfo command gives us the information about the process that is specified.

- `repeat` : repeat command executes a particular command, number of times we ask for.

      Usage : repeat 2 echo "hi" (repeats echo "hi" 2 times)

- `history` : history command can be used in two ways, history and history `<num>`. The history command returns the last 'num' commands entered and preserves it over multiple terminal sessions. When num is not specified it returns last 10 commands by default.

- `jobs` : Can be used as `jobs` to show list of all jobs running in backgrounnd with information in alphabetical order according to process name, `jobs -r` to show processes with "Running" status and `jobs -s` to show processes with "Stopped" status. `jobs -rs, jobs-sr, jobs -r -s` is also implemented though `jobs` does the same work.

- `sig`: Can be used as `sig <job_num> <signal_number>` to send signal of signal_number to process with id as job_number.

- `fg` : Can be used as `fg <job_num>` to bring process with job_num from background to foreground.

- `bg` : Can be used as `bg <job_num>` to change the state of a stopped background job to running in the background.

- `replay` : Can be used as `replay -command <command> -interval <wait_time> -period <time>`.This repeatedly run `command` after every `wait_time` seconds for a total duration of `time` seconds in a subshell in the background. The subshell is though granted access to terminal and runs in the same process group as this shell.

- `quit` : helps us to exit from the current shell session. `exit/q` also works to quit the session. `Ctrl + D` signal also does the work for you.

Coding Style :

This code is completely modular and is distributed over multiple .c and corresponding .h files for each of the functionality. The header.h consists of all the libraries to be used, some declarations of the values to be used and the global variables. The main.c calls the tokenize() function which in turn calls the respective functionality that has been requested. 

Various errors handlings are done in the function for that command itself.

Pipes and Redirecting

- Shell supports input and output redirection using `<`,  `>` and `>>`.
- This is achieved by duplicating the file descriptors(dup,dup2) of the standard I/O files.
- Shell also supports pipelining of commands using `|`, achieved using the `pipe` syscall.
- Piping along with redirection can also be achieved by the shell.

Execution pattern of External Programs and Processes
- The Shell can run external programs in the foreground as well as in the background.
- This is done by forking the shell process into two, replacing the child process's program image with that of the desired program to be run accordingly.
- The parent process does or does not wait for the child process to terminate, for foreground or background processes respectively.
- Program is made to be run in background by adding an ampersand symbol (`&`) after the complete command. It may or may not be separated by whitespace. Any part of the command after the `&` symbol is ignored.
- An alert is printed if a background job terminates(normally/abnormally).
- Processes are stored in a linked list having processes as its nodes and it contains the information regarding that process.
- This all is achieved by maintaining an list of processes, managing processing groups and manipulating the foreground process group of the attached terminal.

Signals handled

- `Ctrl + D` : It exits the shell without disturbing the main terminal. 
- `Ctrl + C` : It interrupts any currently running foreground process, by sending it the `​SIGINT/2`​ signal.
- `Ctrl + Z` : It pushes any currently running foreground process into the background and change its state from running to stopped.

Assumptions made :

- history.txt is already present in the directory that it has been cloned into.
- Input command string doesn't exceeds 8192 characters.
- Files and directory names do not contain special characters or spaces/tabs, but input arguments and commands can be space seperated.
- Commands that may not be executed successfully are also stored in history.txt.
