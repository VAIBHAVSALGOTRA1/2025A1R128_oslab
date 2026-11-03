# EXPERIMENT 5: STRING OPERATIONS IN SHELL SCRIPT & C

## 1. Aim

To implement string length calculation and substring extraction using Bash scripting and C programming. To compare the execution performance of both implementations using the Linux `time` utility.

## 2. Theory

String manipulation is an important operation in programming. It involves calculating string length, accessing individual characters, and extracting portions of a string.

This experiment implements string operations using two approaches:

1. Bash Shell Scripting
2. C Programming

### A. String Operations in Bash

Bash provides built-in parameter expansion features for string manipulation.

**Example:**

```bash
read -p "Enter a string: " str
echo "Length: ${#str}"
echo "Substring: ${str:$start:$length}"
```

**Important expressions:**

| Expression            | Function                            |
| --------------------- | ----------------------------------- |
| `${#str}`             | Calculates the length of a string   |
| `${str:start:length}` | Extracts a substring                |
| `read -p`             | Displays a prompt and accepts input |

Bash uses zero-based indexing, meaning the first character is at position 0.

### B. String Operations in C

In C programming, strings are stored as character arrays ending with a null terminator (`\0`).

The `fgets()` function is used to safely read string input.

**Example:**

```c
char str[100];
fgets(str, 100, stdin);
```

Here:

* `char str[100]` – Creates a character array of 100 bytes.
* `fgets()` – Reads input from the keyboard.
* `stdin` – Represents standard input.
* `\0` – Marks the end of a C string.

The string length can be calculated by iterating through the character array until a null terminator or newline is encountered.

### C. Substring Extraction in C

A substring can be extracted by accessing characters using their array indexes.

For example:

```c
for (i = start; i < start + length && i < count; i++)
    printf("%c", str[i]);
```

This loop prints the required number of characters without reading beyond the string's length.

## 3. Part A: Bash Implementation

### Aim

To create a Bash script that calculates the length of a string and extracts a substring using parameter expansion.

### Program: string_ops.sh

```bash
#!/bin/bash

# Experiment 5 - Part A: Shell Script String Manipulation

read -p "Enter a string: " str

echo "Length of string: ${#str}"

read -p "Enter starting position: " start

read -p "Enter number of characters: " length

# Extract substring
echo "Substring: ${str:$start:$length}"
```

### Explanation

| Statement               | Function                                   |
| ----------------------- | ------------------------------------------ |
| `#!/bin/bash`           | Specifies Bash as the interpreter          |
| `read -p`               | Accepts input from the user                |
| `str`                   | Stores the entered string                  |
| `${#str}`               | Calculates the string length               |
| `start`                 | Stores the starting position               |
| `length`                | Stores the number of characters to extract |
| `${str:$start:$length}` | Extracts the required substring            |

### Execution Steps

**Step 1: Create the file**

```bash
nano string_ops.sh
```

Enter the program and save it.

**Step 2: Grant execution permission**

```bash
chmod +x string_ops.sh
```

**Step 3: Execute the script**

```bash
./string_ops.sh
```

### Sample Output

```text
Enter a string: OperatingSystem
Length of string: 15
Enter starting position: 9
Enter number of characters: 6
Substring: System
```

## 4. Part B: C Implementation

### Aim

To write a C program that calculates string length and extracts a substring using character arrays and loops.

### Program: string_ops.c

```c
#include <stdio.h>

int main()
{
    char str[100];
    int start, length, i, count = 0;

    printf("Enter a string: ");
    fgets(str, 100, stdin);

    // Calculate string length
    while (str[count] != '\0' && str[count] != '\n')
        count++;

    printf("Length of string: %d\n", count);

    printf("Enter starting position: ");
    scanf("%d", &start);

    printf("Enter number of characters: ");
    scanf("%d", &length);

    printf("Substring: ");

    // Extract substring
    for (i = start; i < start + length && i < count; i++)
        printf("%c", str[i]);

    printf("\n");

    return 0;
}
```

### Explanation

| Statement            | Function                                    |
| -------------------- | ------------------------------------------- |
| `#include <stdio.h>` | Includes standard input/output functions    |
| `char str[100]`      | Creates a character array of 100 bytes      |
| `fgets()`            | Safely reads a string from standard input   |
| `count = 0`          | Initializes the string length counter       |
| `while`              | Iterates through the string characters      |
| `'\0'`               | Represents the null terminator              |
| `'\n'`               | Represents the newline character            |
| `scanf()`            | Accepts integer input                       |
| `&start`             | Provides the memory address of the variable |
| `for`                | Extracts the required substring             |
| `printf()`           | Displays the extracted characters           |
| `return 0`           | Indicates successful program termination    |

### Execution Steps

**Step 1: Create the C file**

```bash
nano string_ops.c
```

Enter the program and save it.

**Step 2: Compile the program**

```bash
gcc string_ops.c -o string_ops
```

**Step 3: Execute the program**

```bash
./string_ops
```

### Sample Output

```text
Enter a string: OperatingSystem
Length of string: 15
Enter starting position: 9
Enter number of characters: 6
Substring: System
```

## 5. Performance Profiling Using the time Utility

### Aim

To measure and compare the execution time of the Bash script and compiled C program using the Linux `time` utility.

The `time` command measures how much time a program takes to execute.

### A. Profiling the Bash Script

**Command:**

```bash
time ./string_ops.sh
```

**Sample Output:**

```text
real    0m0.008s
user    0m0.003s
sys     0m0.005s
```

### B. Profiling the C Program

**Command:**

```bash
time ./string_ops
```

**Sample Output:**

```text
real    0m0.002s
user    0m0.001s
sys     0m0.001s
```

*Note: These timings are illustrative. Actual execution times depend on the computer, operating system, and system load.*

### C. Explanation of Time Metrics

| Metric | Meaning                                                                 |
| ------ | ----------------------------------------------------------------------- |
| `real` | Total elapsed wall-clock time                                           |
| `user` | CPU time spent executing application instructions in user space         |
| `sys`  | CPU time spent executing operating system code on behalf of the process |

**1. Real Time:**
The total time from starting the program until its execution finishes.

**2. User Time:**
The time the CPU spends executing the program's instructions in user mode.

**3. System Time:**
The time the CPU spends performing operating system operations such as input/output system calls.

## 6. Architectural Comparison: Bash vs C

| Feature         | Bash Script                       | C Program                        |
| --------------- | --------------------------------- | -------------------------------- |
| Execution Mode  | Interpreted                       | Compiled                         |
| Execution       | Runs through Bash interpreter     | Runs as a compiled executable    |
| String Length   | `${#str}`                         | Character-by-character loop      |
| Substring       | Parameter expansion               | Array indexing                   |
| Input           | `read`                            | `fgets()`                        |
| Memory Handling | Managed by shell                  | Direct character array handling  |
| Compilation     | Not required                      | Required using GCC               |
| Performance     | Generally higher startup overhead | Generally lower startup overhead |

### Performance Comparison

The Bash script uses the shell interpreter, while the C program is compiled into machine code.

For small string operations, the C program may execute faster. However, actual performance depends on system conditions and the size of the input.

## 7. Important Commands

| Command                          | Function                      |
| -------------------------------- | ----------------------------- |
| `nano string_ops.sh`             | Creates the Bash script       |
| `chmod +x string_ops.sh`         | Grants execution permission   |
| `./string_ops.sh`                | Executes the Bash script      |
| `nano string_ops.c`              | Creates the C source file     |
| `gcc string_ops.c -o string_ops` | Compiles the C program        |
| `./string_ops`                   | Executes the compiled program |
| `time ./string_ops.sh`           | Measures Bash execution time  |
| `time ./string_ops`              | Measures C execution time     |

## 8. Procedure

1. Open the Ubuntu Linux terminal.
2. Create a Bash script named `string_ops.sh`.
3. Implement string length calculation using `${#str}`.
4. Extract a substring using `${str:$start:$length}`.
5. Grant execution permission using `chmod +x`.
6. Create a C program named `string_ops.c`.
7. Read string input using `fgets()`.
8. Calculate string length using a `while` loop.
9. Extract the substring using a `for` loop.
10. Compile the C program using GCC.
11. Execute both programs with the same input.
12. Use the Linux `time` utility to measure execution time.
13. Compare the execution results.

## 9. Applications

* String manipulation in shell scripts.
* Text processing and extraction.
* Character array handling in C.
* Understanding memory management.
* Comparing interpreted and compiled programs.
* Measuring program execution performance.
* Learning Linux command-line programming.

## 10. Result

Successfully implemented string length calculation and substring extraction using Bash scripting and C programming. Successfully compiled and executed the C program using GCC and measured the execution performance of both implementations using the Linux `time` utility.
