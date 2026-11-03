# EXPERIMENT 3: BASH SCRIPTING, CONDITIONALS & LOOPS

## 1. Aim

To study and implement Bash scripting concepts, including shell script execution, positional parameters, conditional statements, file test operators, looping constructs, and automated file manipulation in Ubuntu Linux.

## 2. Theory

### A. Bash Shell Scripting

A Shell Script is an executable text file containing a sequence of Linux commands that are executed by a shell interpreter.

It is used to automate repetitive tasks and execute multiple commands in a structured manner.

**Example:**

```bash
#!/bin/bash
echo "Starting System Audit..."
date
whoami
```

**Explanation:**

* `#!/bin/bash` – Shebang directive that specifies Bash as the interpreter.
* `echo` – Displays a message on the terminal.
* `date` – Displays the current date and time.
* `whoami` – Displays the current logged-in username.

### B. Shebang Directive

The Shebang (`#!`) is written at the beginning of a shell script.

It tells the Linux kernel which interpreter should execute the script.

Example:

```bash
#!/bin/bash
```

### C. Script Execution Lifecycle

The following steps are used to create and execute a Bash script.

**Step 1: Create a script**

```bash
nano audit.sh
```

**Step 2: Grant execution permission**

```bash
chmod +x audit.sh
```

**Step 3: Execute the script**

```bash
./audit.sh
```

**Explanation:**

* `nano` – Opens the Nano text editor.
* `chmod +x` – Grants executable permission.
* `./` – Specifies that the script is located in the current directory.

## 3. Positional Parameters

Positional parameters are special shell variables used to access arguments passed to a script through the command line.

**Example:**

```bash
./backup.sh data.txt notes.txt /archive
```

Inside the script:

| Parameter | Meaning                          | Example             |
| --------- | -------------------------------- | ------------------- |
| `$0`      | Script name                      | `./backup.sh`       |
| `$1`      | First argument                   | `data.txt`          |
| `$2`      | Second argument                  | `notes.txt`         |
| `$3`      | Third argument                   | `/archive`          |
| `$#`      | Total number of arguments        | `3`                 |
| `$@`      | All arguments separately         | All three arguments |
| `$*`      | All arguments as a joined string | Combined arguments  |
| `$?`      | Exit status of the last command  | `0` means success   |
| `$$`      | Process ID of the current shell  | Process ID          |

These parameters make scripts flexible because inputs can be provided without changing the script code.

## 4. Conditional Testing

Conditional statements are used to execute commands depending on whether a particular condition is true or false.

Bash uses `[ ... ]` or the `test` command to evaluate conditions.

**Example:**

```bash
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <source> <destination>"
    exit 1
fi
```

**Explanation:**

* `if` – Starts the conditional statement.
* `[ ... ]` – Evaluates the condition.
* `$#` – Represents the number of arguments.
* `-ne` – Checks whether two integers are not equal.
* `exit 1` – Terminates the script with an error status.
* `fi` – Ends the conditional statement.

**Important Rules:**

1. A space is required after `[` and before `]`.
2. Variables should be enclosed in double quotes.
3. The condition must return a successful status for the `then` block to execute.

### A. Integer Comparison Operators

| Operator | Meaning                  | Example             |
| -------- | ------------------------ | ------------------- |
| `-eq`    | Equal to                 | `[ "$a" -eq "$b" ]` |
| `-ne`    | Not equal to             | `[ "$a" -ne "$b" ]` |
| `-lt`    | Less than                | `[ "$a" -lt 10 ]`   |
| `-le`    | Less than or equal to    | `[ "$a" -le 10 ]`   |
| `-gt`    | Greater than             | `[ "$a" -gt 50 ]`   |
| `-ge`    | Greater than or equal to | `[ "$a" -ge 18 ]`   |

## 5. File System Auditing

Bash provides file test operators to check the existence, type, size, and permissions of files and directories.

### A. File Type and Existence Operators

| Operator | Meaning                                       |
| -------- | --------------------------------------------- |
| `-e`     | Checks whether a path exists                  |
| `-f`     | Checks whether a regular file exists          |
| `-d`     | Checks whether a directory exists             |
| `-s`     | Checks whether a file exists and is non-empty |

**Example:**

```bash
if [ -f "$target" ]; then
    echo "Valid regular file found."
fi
```

### B. Permission Operators

| Operator | Meaning                                    |
| -------- | ------------------------------------------ |
| `-r`     | Checks read permission                     |
| `-w`     | Checks write permission                    |
| `-x`     | Checks execute permission                  |
| `-h`     | Checks whether the path is a symbolic link |

**Example:**

```bash
if [ -r "$src" ] && [ -w "$dst" ]; then
    cp "$src" "$dst/"
fi
```

Here, `&&` ensures that the copy command executes only when both conditions are true.

## 6. Control Flow Statements

Control flow statements allow a script to make decisions based on conditions.

### A. if-else Statement

The `if-else` statement executes one block when a condition is true and another block when it is false.

**Example:**

```bash
if [ -f "notes.txt" ]; then
    echo "notes.txt is a regular file."
else
    echo "notes.txt does not exist or is not a file."
fi
```

**Explanation:**

* `if` – Checks the condition.
* `then` – Executes commands if the condition is true.
* `else` – Executes commands if the condition is false.
* `fi` – Terminates the conditional statement.

### B. if-elif-else Statement

The `elif` statement is used to check multiple conditions.

**Example:**

```bash
if [ -f "$target" ]; then
    echo "Regular file"
elif [ -d "$target" ]; then
    echo "Directory"
elif [ -e "$target" ]; then
    echo "Special node"
else
    echo "Does not exist"
fi
```

The conditions are checked sequentially. The first true condition is executed.

## 7. Looping Constructs

Loops are used to execute a set of commands repeatedly.

### A. For Loop Using a Word List

```bash
for name in Ali Rahul Aman
do
    echo "Hello $name"
done
```

**Output:**

```text
Hello Ali
Hello Rahul
Hello Aman
```

### B. For Loop Using Integer Ranges

**Using brace expansion:**

```bash
for i in {1..5}
do
    echo "Count: $i"
done
```

**Using C-style syntax:**

```bash
for ((i=1; i<=5; i++))
do
    echo "Index: $i"
done
```

Both examples iterate from 1 to 5.

### C. For Loop Using Command-Line Arguments

```bash
for file in "$@"
do
    echo "Processing: $file"
    chmod 644 "$file"
done
```

Here, `"$@"` represents all arguments passed to the script. The loop processes each argument separately.

## 8. Core Lab Task 1: File/Directory Classifier Script

### Aim

To create a Bash script that checks whether the given path is a regular file, directory, special filesystem node, or does not exist.

### Program: check_type.sh

```bash
#!/bin/bash

# Experiment 3 - Task 1: Check File or Directory

if [ $# -ne 1 ]; then
    echo "No Argument passed, Try Again with an Argument"
    exit 1
fi

target="$1"

if [ -f "$target" ]; then
    echo "$target is a regular file."
elif [ -d "$target" ]; then
    echo "$target is a directory."
elif [ -e "$target" ]; then
    echo "$target exists, but is neither file nor directory."
else
    echo "Error: $target does not exist."
fi
```

### Explanation

| Statement      | Function                                                 |
| -------------- | -------------------------------------------------------- |
| `#!/bin/bash`  | Specifies Bash as the interpreter                        |
| `[ $# -ne 1 ]` | Checks whether exactly one argument was supplied         |
| `exit 1`       | Terminates the script if the argument count is incorrect |
| `target="$1"`  | Stores the first argument in a variable                  |
| `-f "$target"` | Checks whether the path is a regular file                |
| `-d "$target"` | Checks whether the path is a directory                   |
| `-e "$target"` | Checks whether the path exists                           |
| `else`         | Handles a path that does not exist                       |

### Execution Steps

**Step 1: Create the script**

```bash
nano check_type.sh
```

Enter the program and save it.

**Step 2: Give execution permission**

```bash
chmod +x check_type.sh
```

**Step 3: Execute the script**

```bash
./check_type.sh /etc/passwd
```

### Sample Execution and Output

**Case 1: Regular File**

```bash
./check_type.sh /etc/passwd
```

Output:

```text
/etc/passwd is a regular file.
```

**Case 2: Directory**

```bash
./check_type.sh /var/log
```

Output:

```text
/var/log is a directory.
```

**Case 3: Non-existing Path**

```bash
./check_type.sh /fake/file
```

Output:

```text
Error: /fake/file does not exist.
```

**Case 4: No Argument**

```bash
./check_type.sh
```

Output:

```text
No Argument passed, Try Again with an Argument
```

## 9. Core Lab Task 2: Batch Filename Uppercasing Script

### Aim

To create a Bash script that converts the filenames supplied as command-line arguments into uppercase and renames them automatically.

### Program: rename_upper.sh

```bash
#!/bin/bash

# Experiment 3 - Task 2: Uppercase Renaming

# Iterate across all supplied arguments
for file in "$@"
do
    # Check whether file exists
    if [ -e "$file" ]; then

        # Convert filename to uppercase
        new_name=$(echo "$file" | tr '[:lower:]' '[:upper:]')

        # Rename the file
        mv "$file" "$new_name"

    else
        echo "Warning: '$file' not found, skipping."
    fi
done
```

### Explanation

| Statement                    | Function                                            |
| ---------------------------- | --------------------------------------------------- |
| `for file in "$@"`           | Iterates through all supplied arguments             |
| `[ -e "$file" ]`             | Checks whether the file exists                      |
| `echo "$file"`               | Displays the filename as input                      |
| `tr '[:lower:]' '[:upper:]'` | Converts lowercase letters into uppercase           |
| `$(...)`                     | Captures command output and stores it in a variable |
| `new_name`                   | Stores the converted filename                       |
| `mv "$file" "$new_name"`     | Renames the file                                    |
| `else`                       | Displays a warning if the file does not exist       |

### Execution Steps

**Step 1: Create the script**

```bash
nano rename_upper.sh
```

Enter the program and save it.

**Step 2: Give execution permission**

```bash
chmod +x rename_upper.sh
```

**Step 3: Create sample files**

```bash
touch notes.txt report.txt hello.txt
```

**Step 4: Execute the script**

```bash
./rename_upper.sh notes.txt report.txt hello.txt
```

**Step 5: Verify the renamed files**

```bash
ls
```

### Sample Output

```text
HELLO.TXT
NOTES.TXT
REPORT.TXT
```

The filenames are converted into uppercase successfully.

## 10. Quick Reference: Bash Commands and Operators

| Category    | Syntax / Operator      | Function                                      |
| ----------- | ---------------------- | --------------------------------------------- |
| Interpreter | `#!/bin/bash`          | Specifies the Bash interpreter                |
| Parameters  | `$0`, `$1...$n`        | Accesses command-line arguments               |
| Parameters  | `$#`                   | Counts the supplied arguments                 |
| Parameters  | `$@`                   | Accesses all arguments separately             |
| Parameters  | `$*`                   | Represents all arguments as a joined string   |
| Parameters  | `$?`                   | Returns the previous command's exit status    |
| Parameters  | `$$`                   | Returns the current shell process ID          |
| Numeric     | `-eq`, `-ne`           | Integer equality and inequality               |
| Numeric     | `-lt`, `-le`           | Less than and less than or equal to           |
| Numeric     | `-gt`, `-ge`           | Greater than and greater than or equal to     |
| File Tests  | `-e`, `-f`, `-d`       | Checks existence, regular file, and directory |
| File Tests  | `-s`, `-r`, `-w`, `-x` | Checks size and permissions                   |
| Looping     | `for ... do ... done`  | Repeats commands                              |
| Expansion   | `$(command)`           | Captures command output into a variable       |
| Conversion  | `tr`                   | Translates or converts characters             |
| Renaming    | `mv`                   | Renames or moves files                        |

## 11. Procedure

1. Open the Ubuntu Linux terminal.
2. Create a Bash script using the Nano editor.
3. Write the Shebang directive at the beginning of the script.
4. Understand and use positional parameters.
5. Apply integer comparison and file test operators.
6. Implement conditional statements such as `if`, `if-else`, and `elif`.
7. Implement loops using the `for` construct.
8. Create and execute the file/directory classifier script.
9. Create and execute the batch filename uppercasing script.
10. Verify the output using Linux commands.

## 12. Applications

* Automating repetitive Linux commands.
* Managing files and directories.
* Checking file types and permissions.
* Performing batch file renaming.
* Automating system administration tasks.
* Processing command-line arguments.
* Creating automated file management scripts.

## 13. Result

Successfully studied and implemented Bash scripting concepts, positional parameters, conditional statements, integer comparisons, file test operators, and looping constructs. Successfully created and executed scripts for file/directory classification and batch filename uppercasing in Ubuntu Linux.
