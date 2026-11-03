# EXPERIMENT 4: USER SESSION TRACKING & TEXT STREAM PROCESSING

## 1. Aim

To study and implement user session tracking and text stream processing in Linux using `who`, `awk`, `date`, `sed`, and Bash scripting. To calculate user working time, display a specific range of lines, and delete matching words across multiple files.

## 2. Theory

### A. User Session Tracking Using who

The `who` command is used to display information about users currently logged into a Linux system.

It retrieves active login session information from the system's utmp database.

**Command:**

```bash
who
```

**Sample Output:**

```text
aniket pts/0 2026-09-09 10:30
rahul  pts/1 2026-09-09 11:15
```

The output contains:

* Username
* Terminal name
* Login date
* Login time

### B. AWK Stream Processing

AWK is a text-processing utility used to search, filter, and extract information from structured text.

It divides each input line into fields.

**Example:**

```bash
who | awk -v u="$user" '$1 == u {print $3, $4; exit}'
```

**Explanation:**

| Component      | Function                                            |                                   |
| -------------- | --------------------------------------------------- | --------------------------------- |
| `who`          | Displays currently logged-in users                  |                                   |
| `              | `                                                   | Passes output to the next command |
| `awk`          | Processes the input text                            |                                   |
| `-v u="$user"` | Passes the Bash variable into AWK                   |                                   |
| `$1 == u`      | Checks whether the first field matches the username |                                   |
| `print $3, $4` | Displays the login date and time                    |                                   |
| `exit`         | Stops processing after the first match              |                                   |

### C. Unix Epoch Time

Unix Epoch time represents the number of seconds elapsed since January 1, 1970, UTC.

It allows two timestamps to be subtracted to calculate the time difference.

**Convert login time into epoch seconds:**

```bash
login_seconds=$(date -d "$login_time" +%s)
```

**Get current epoch time:**

```bash
current_seconds=$(date +%s)
```

**Calculate total working time:**

```bash
total_seconds=$((current_seconds - login_seconds))
```

### D. Hour and Minute Calculation

The total seconds are converted into hours and minutes using integer division and modulo operations.

**Calculate hours:**

```bash
hours=$((total_seconds / 3600))
```

**Calculate minutes:**

```bash
minutes=$(((total_seconds % 3600) / 60))
```

Here:

* 3600 seconds = 1 hour.
* 60 seconds = 1 minute.
* `%` calculates the remainder.
* `/` performs integer division.

### E. Stream Editor (sed)

`sed` stands for Stream Editor. It is used to search, print, delete, and modify text in files.

Common operations:

| Command  | Function                            |
| -------- | ----------------------------------- |
| `sed -n` | Suppresses automatic printing       |
| `p`      | Prints selected lines               |
| `d`      | Deletes matching lines              |
| `-i`     | Modifies the original file directly |

### F. shift Command

The `shift` command is used to rotate positional parameters in a Bash script.

It removes the first positional argument and shifts the remaining arguments one position to the left.

**Example:**

Before `shift`:

```text
$1 = Aniket
$2 = names.txt
$3 = students.txt
```

After `shift`:

```text
$1 = names.txt
$2 = students.txt
```

This is useful when a script needs to separate one main argument from multiple filenames.

## 3. Core Lab Task 1: Determine User Working Period

### Aim

To create a Bash script that determines the working duration of a currently logged-in user using `who`, `awk`, and Unix Epoch calculations.

### Program: user_time.sh

```bash
#!/bin/bash

# Experiment 4 - Task 1: Determine User Working Time

read -p "Enter username: " user

# Extract login date and time for specified user
login_time=$(who | awk -v u="$user" '$1 == u {print $3, $4; exit}')

if [ -z "$login_time" ]; then
    echo "User '$user' is not currently logged in."
else
    echo "Login time: $login_time"

    login_seconds=$(date -d "$login_time" +%s)
    current_seconds=$(date +%s)

    total_seconds=$((current_seconds - login_seconds))

    hours=$((total_seconds / 3600))
    minutes=$(((total_seconds % 3600) / 60))

    echo "Total working time: $hours hours $minutes minutes"
fi
```

### Explanation

| Statement                   | Function                                     |
| --------------------------- | -------------------------------------------- |
| `read -p`                   | Displays a prompt and accepts the username   |
| `who`                       | Retrieves active login sessions              |
| `awk`                       | Extracts the login date and time             |
| `-v u="$user"`              | Passes the username to AWK                   |
| `[ -z "$login_time" ]`      | Checks whether the login time is empty       |
| `date -d "$login_time" +%s` | Converts login time into Epoch seconds       |
| `date +%s`                  | Retrieves the current Epoch time             |
| `total_seconds`             | Calculates the difference between timestamps |
| `hours`                     | Converts seconds into hours                  |
| `minutes`                   | Calculates the remaining minutes             |

### Execution Steps

**Step 1: Create the file**

```bash
nano user_time.sh
```

Enter the program and save it.

**Step 2: Give execution permission**

```bash
chmod +x user_time.sh
```

**Step 3: Execute the script**

```bash
./user_time.sh
```

### Sample Output

```text
Enter username: aniket
Login time: 2026-09-09 10:30
Total working time: 4 hours 15 minutes
```

*Note: The displayed duration is illustrative. Actual output depends on the current login session and system time.*

## 4. Core Lab Task 2: Display Line Range

### Aim

To create a Bash script that displays a specified range of lines from a text file using the `sed` command.

### Program: display_range.sh

```bash
#!/bin/bash

# Experiment 4 - Task 2: Display Lines Between Start & End

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 filename start_line end_line"
    exit 1
fi

file="$1"
start="$2"
end="$3"

sed -n "${start},${end}p" "$file"
```

### Explanation

| Statement          | Function                                            |
| ------------------ | --------------------------------------------------- |
| `[ "$#" -ne 3 ]`   | Checks whether exactly three arguments are supplied |
| `exit 1`           | Terminates the script if arguments are incorrect    |
| `file="$1"`        | Stores the filename                                 |
| `start="$2"`       | Stores the starting line number                     |
| `end="$3"`         | Stores the ending line number                       |
| `sed -n`           | Suppresses automatic printing                       |
| `${start},${end}p` | Prints the specified line range                     |

### Execution Steps

**Step 1: Create the file**

```bash
nano display_range.sh
```

Enter the program and save it.

**Step 2: Give execution permission**

```bash
chmod +x display_range.sh
```

**Step 3: Create a sample text file**

```bash
nano names.txt
```

Enter:

```text
Rahul
Aman
Aniket
Rohit
Neha
Priya
```

Save the file.

**Step 4: Execute the script**

```bash
./display_range.sh names.txt 3 6
```

### Sample Output

```text
Aniket
Rohit
Neha
Priya
```

The script displays lines 3 to 6 from the specified file.

## 5. Core Lab Task 3: Multi-File Word Deletion

### Aim

To create a Bash script that deletes all lines containing a specified word from multiple files using the `shift` and `sed` commands.

### Program: delete_word.sh

```bash
#!/bin/bash

# Experiment 4 - Task 3: Delete Matching Word Across Files

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 word file1 [file2 ...]"
    exit 1
fi

word="$1"

shift

for file in "$@"
do
    sed -i "/$word/d" "$file"

    echo "Processed: $file (lines with '$word' deleted)"
done
```

### Explanation

| Statement          | Function                                                      |
| ------------------ | ------------------------------------------------------------- |
| `[ "$#" -lt 2 ]`   | Checks that at least two arguments are supplied               |
| `word="$1"`        | Stores the word to be deleted                                 |
| `shift`            | Removes the first argument and shifts the remaining arguments |
| `for file in "$@"` | Iterates through all remaining filenames                      |
| `sed -i`           | Modifies the original file directly                           |
| `/$word/d`         | Deletes lines containing the specified word                   |
| `echo`             | Displays the processing status                                |

### Execution Steps

**Step 1: Create the file**

```bash
nano delete_word.sh
```

Enter the program and save it.

**Step 2: Give execution permission**

```bash
chmod +x delete_word.sh
```

**Step 3: Create sample files**

```bash
nano names.txt
```

Enter:

```text
Aniket
Rahul
Rohit
Aniket Sharma
Neha
```

Create another file:

```bash
nano students.txt
```

Enter:

```text
Aniket
Aman
Priya
Aniket Singh
```

**Step 4: Execute the script**

```bash
./delete_word.sh Aniket names.txt students.txt
```

### Sample Output

```text
Processed: names.txt (lines with 'Aniket' deleted)
Processed: students.txt (lines with 'Aniket' deleted)
```

**Step 5: Verify the modified files**

```bash
cat names.txt
cat students.txt
```

Output of `names.txt`:

```text
Rahul
Rohit
Neha
```

Output of `students.txt`:

```text
Aman
Priya
```

The matching lines are permanently deleted from both files.

## 6. Quick Reference: Commands and Parameters

| Command / Construct  | Function                               |
| -------------------- | -------------------------------------- |
| `who`                | Displays logged-in users               |
| `awk`                | Extracts and processes text fields     |
| `who \| awk`         | Passes user session information to AWK |
| `-v`                 | Passes a variable into AWK             |
| `date -d "..." +%s`  | Converts a date into Epoch seconds     |
| `date +%s`           | Displays current Epoch time            |
| `$(( ))`             | Performs arithmetic operations         |
| `sed -n`             | Suppresses automatic printing          |
| `sed -n '2,5p' file` | Displays lines 2 to 5                  |
| `sed -i`             | Modifies a file directly               |
| `shift`              | Shifts positional parameters           |
| `$1`                 | First positional argument              |
| `$@`                 | All positional arguments               |
| `$#`                 | Number of arguments                    |

## 7. Procedure

1. Open the Ubuntu Linux terminal.
2. Create a Bash script using the Nano editor.
3. Write the Shebang directive at the beginning of each script.
4. Use the `who` command to retrieve active user sessions.
5. Use AWK to extract the username, login date, and login time.
6. Calculate the working duration using Unix Epoch arithmetic.
7. Create a script to display a specified line range using `sed`.
8. Create a script to delete matching lines from multiple files.
9. Use the `shift` command to process multiple filenames.
10. Grant execution permissions using `chmod +x`.
11. Execute all three scripts and verify their outputs.

## 8. Applications

* Monitoring active Linux user sessions.
* Calculating user login duration.
* Extracting information from command output.
* Processing and filtering text files.
* Displaying specific portions of large files.
* Performing automated deletion across multiple files.
* Managing command-line arguments in Bash scripts.

## 9. Result

Successfully studied and implemented user session tracking and text stream processing using Bash scripting, `who`, AWK, Unix Epoch arithmetic, `sed`, and the `shift` command. Successfully created and executed programs to calculate user working time, display a specified line range, and delete matching words across multiple files.
