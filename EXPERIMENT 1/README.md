# Linux System Administration: Directory Operations, I/O Redirection & Process Management

## 1. Aim

To study and execute various Linux commands related to directory operations, file management, input/output redirection, pipes, text processing, text editors, and process management.

## 2. Theory

Linux is an open-source operating system that provides a command-line interface called the Shell. The Bash shell allows users to interact with the operating system using commands.

Linux commands are used to manage files and directories, control processes, search data, redirect input and output, and monitor system resources.

This experiment covers the following concepts:

1. Directory Operations
2. File Operations
3. I/O Redirection and Pipes
4. Text Processing using grep and find
5. Text Editors (Vi/Vim and Nano)
6. Process Management

## 3. Directory Operations

Directory operations are used to navigate, create, and remove directories in Linux.

### Commands Used

| Command | Description                            |
| ------- | -------------------------------------- |
| pwd     | Displays the current working directory |
| cd      | Changes the current directory          |
| mkdir   | Creates a new directory                |
| rmdir   | Removes an empty directory             |
| chmod   | Changes directory permissions          |

### Practical Commands

```bash
pwd
cd ..
cd ~
cd /etc/netplan
mkdir scripts
mkdir -p Documents/projects/app
mkdir -v Downloads/iso
rmdir scripts
chmod 755 Documents/projects
```

## 4. File Operations

File operations are used to create, view, copy, move, rename, and delete files.

### Commands Used

| Command | Description                      |
| ------- | -------------------------------- |
| ls      | Lists files and directories      |
| touch   | Creates an empty file            |
| cp      | Copies files                     |
| mv      | Moves or renames files           |
| rm      | Removes files                    |
| cat     | Displays file contents           |
| head    | Displays the beginning of a file |
| tail    | Displays the end of a file       |

### Practical Commands

```bash
ls -lah
touch file.txt
cp file.txt backup.txt
mv backup.txt newfile.txt
cat file.txt
cat -n file.txt
head -n 10 file.txt
tail -n 10 file.txt
rm newfile.txt
```

## 5. I/O Redirection

I/O Redirection is used to change the default input and output locations of commands.

Linux uses three standard file descriptors:

| File Descriptor | Name   | Description     |
| --------------- | ------ | --------------- |
| 0               | stdin  | Standard Input  |
| 1               | stdout | Standard Output |
| 2               | stderr | Standard Error  |

### Redirection Operators

| Operator | Description                                      |
| -------- | ------------------------------------------------ |
| >        | Redirects output and overwrites existing content |
| >>       | Appends output to an existing file               |
| <        | Takes input from a file                          |
| 2>       | Redirects error messages                         |
| &>       | Redirects both standard output and errors        |

### Practical Commands

```bash
echo "Hello" > myfile
echo "Welcome" >> myfile
cat < myfile
cd /root/ 2> error.txt
ls &> output.txt
```

## 6. Pipes, Tee and Xargs

A pipe (|) connects the output of one command to the input of another command.

### Practical Commands

**Combining and Sorting Files**

```bash
cat names.txt countries.txt | sort
```

**Removing Duplicate Records**

```bash
cat names.txt | sort | uniq
```

**Displaying Specific Lines**

```bash
cat data.txt | head -n 37 | tail -n 7
```

**Tee Command**

The tee command displays output on the terminal and saves it into a file simultaneously.

```bash
ls | tee test.txt
```

**Xargs Command**

The xargs command converts standard input into command-line arguments.

```bash
cat file_names.txt | xargs touch
```

## 7. Text Processing Using grep

The grep command stands for Global Regular Expression Print. It is used to search for specific patterns or words inside files.

### Common Options

| Option | Description                      |
| ------ | -------------------------------- |
| -i     | Ignores case sensitivity         |
| -v     | Displays lines that do not match |
| -c     | Counts matching lines            |
| -w     | Searches for exact words         |
| -n     | Displays matching line numbers   |

### Practical Commands

```bash
grep -i "error" logs.txt
grep -v "error" logs.txt
grep -c "Doctor" users.csv
grep -w "Carly" users.csv
grep -n "Carly" users.csv
```

## 8. File Searching Using find

The find command is used to search for files and directories based on different conditions.

### Syntax

```bash
find [options] [path] [expression]
```

### Practical Commands

```bash
find . -size 4M
find . -name "a123"
find . -iname "a123"
find . -user root
find . -empty
```

### Description

* -size: Searches files according to size.
* -name: Searches using an exact, case-sensitive filename.
* -iname: Searches without considering case sensitivity.
* -user: Searches files owned by a particular user.
* -empty: Finds empty files and directories.

## 9. Text Editors: Vi/Vim and Nano

Linux provides terminal-based text editors for creating and modifying files.

### Vi/Vim Editor

```bash
vim file.txt
```

Common shortcuts:

| Shortcut | Function               |
| -------- | ---------------------- |
| i        | Enters Insert mode     |
| Esc      | Returns to Normal mode |
| :w       | Saves the file         |
| :q       | Exits the editor       |
| :wq      | Saves and exits        |
| :q!      | Exits without saving   |
| dd       | Deletes a line         |
| yy       | Copies a line          |
| p        | Pastes a line          |
| u        | Undo                   |

### Nano Editor

```bash
nano file.txt
```

Common shortcuts:

| Shortcut | Function               |
| -------- | ---------------------- |
| Ctrl + O | Saves the file         |
| Ctrl + X | Exits the editor       |
| Ctrl + W | Searches text          |
| Ctrl + K | Cuts a line            |
| Ctrl + U | Pastes a line          |
| Ctrl + _ | Jumps to a line number |

## 10. Linux Process Management

A process is a program currently being executed by the operating system.

Linux provides several commands to view, manage, control, and monitor processes.

### A. Job Control Commands

| Command | Description                               |
| ------- | ----------------------------------------- |
| jobs    | Displays active jobs of the current shell |
| bg      | Resumes a stopped job in the background   |
| fg      | Brings a background job to the foreground |

Practical commands:

```bash
sleep 100 &
jobs
```

To stop a running foreground process, press Ctrl + Z.

```bash
bg
fg
```

### B. Process Inspection Commands

| Command   | Description                                  |
| --------- | -------------------------------------------- |
| ps        | Displays current session processes           |
| ps -e     | Displays all system processes                |
| ps -ef    | Displays detailed process information        |
| ps -p PID | Displays a specific process                  |
| ps aux    | Displays processes with CPU and memory usage |
| top       | Provides live process monitoring             |

Practical commands:

```bash
ps
ps -e
ps -ef
ps aux
ps -p 6721 -f
top
```

### C. Process Termination Commands

The kill command sends signals to processes to control their execution.

| Command        | Description                   |
| -------------- | ----------------------------- |
| kill PID       | Sends SIGTERM by default      |
| kill -15 PID   | Requests graceful termination |
| kill -9 PID    | Forces immediate termination  |
| kill -l        | Lists available signals       |
| kill -STOP PID | Stops a process               |
| kill -CONT PID | Resumes a stopped process     |

Practical commands:

```bash
kill 6721
kill -15 6721
kill -9 6721
kill -l
kill -STOP 6721
kill -CONT 6721
```

### D. Process Priority Management

Linux uses nice values to influence CPU scheduling priority.

The nice value ranges from -20 to +19.

* -20: Highest scheduling priority.
* 0: Default priority.
* +19: Lowest scheduling priority.

**nice:** Sets the priority when starting a process.

```bash
nice -n 10 sleep 300 &
```

**renice:** Changes the priority of an already running process.

```bash
renice 10 -p 7100
```

**Checking Process Priority**

```bash
ps -o pid,ni,cmd
```

## 11. Live Process Monitoring Using top

The top command provides a continuously updating view of running processes and system resource usage.

```bash
top
```

Common interactive shortcuts:

| Shortcut | Function                      |
| -------- | ----------------------------- |
| q        | Exits top                     |
| k        | Sends a signal to a process   |
| c        | Toggles command display       |
| u        | Filters processes by username |
| f        | Manages displayed columns     |
| z        | Toggles colour display        |
| b        | Toggles process highlighting  |

## 12. Procedure

1. Open the Linux terminal.
2. Execute directory navigation commands such as pwd and cd.
3. Create and remove directories using mkdir and rmdir.
4. Perform file operations using touch, ls, cp, mv, rm and cat.
5. Execute input/output redirection commands.
6. Use pipes to combine commands and process data.
7. Search text using grep and locate files using find.
8. Open and edit files using Vim and Nano.
9. Create and manage background and foreground jobs.
10. Inspect processes using ps and ps aux.
11. Control processes using kill and different signals.
12. Change process priorities using nice and renice.
13. Monitor system processes using top.

## 13. Applications

1. Managing files and directories in Linux.
2. Automating system administration tasks.
3. Searching and filtering large amounts of data.
4. Managing background and foreground processes.
5. Monitoring CPU and memory utilization.
6. Controlling process execution and priority.
7. Managing system resources efficiently.

## 14. Result

Successfully studied and executed various Linux commands related to directory management, file operations, I/O redirection, pipes, text processing, text editors, and process management.

The experiment provided practical knowledge of Linux command-line operations and process administration.



B.Tech – Computer Science and Engineering
