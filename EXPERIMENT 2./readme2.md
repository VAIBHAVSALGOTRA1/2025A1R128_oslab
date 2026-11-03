# Experiment: Combined Redirection and Stream Editor (sed)

## 1. Aim

To study and implement combined command execution, I/O redirection, and text manipulation using the Linux Stream Editor (`sed`). To perform line printing, deletion, substitution, in-place modification, regular expression matching, and word swapping.

## 2. Theory

Linux provides commands and utilities to manage files, redirect input/output streams, and manipulate text.

### A. Combined Command Execution

Multiple commands can be executed in sequence using command separators.

**Command:**

```bash
date; who > logged_users.txt
```

**Explanation:**

* `date` – Displays the current date and time.
* `;` – Executes commands sequentially, regardless of success or failure.
* `who` – Displays currently logged-in users.
* `>` – Redirects output to a file.
* `logged_users.txt` – Stores the output of the `who` command.

Another execution operator is `&&`, which executes the next command only if the previous command succeeds.

### B. I/O Redirection

I/O redirection is used to control where commands receive input and send output.

| File Descriptor | Stream | Description     |
| --------------- | ------ | --------------- |
| 0               | stdin  | Standard Input  |
| 1               | stdout | Standard Output |
| 2               | stderr | Standard Error  |

Common redirection operators:

| Operator | Function                                                 |
| -------- | -------------------------------------------------------- |
| `>`      | Redirects output to a file, overwriting existing content |
| `>>`     | Appends output to a file                                 |
| `<`      | Takes input from a file                                  |
| `2>`     | Redirects error messages                                 |
| `&>`     | Redirects both standard output and standard error        |

### C. Stream Editor (sed)

`sed` stands for Stream Editor. It is a non-interactive text editor that reads input line by line, applies specified operations, and produces modified output.

Unlike interactive editors such as Nano and Vim, `sed` performs text transformations directly through commands.

**Main operations:**

| Command | Function                   |
| ------- | -------------------------- |
| `p`     | Prints selected lines      |
| `d`     | Deletes selected lines     |
| `/`     | Searches for patterns      |
| `s`     | Performs text substitution |

## 3. Printing Operations

The `-n` option suppresses automatic printing. The `p` command prints the selected lines.

**Command:**

```bash
sed -n 'p' Names.txt
```

**Explanation:**

* `sed` – Invokes the stream editor.
* `-n` – Suppresses automatic printing.
* `p` – Explicitly prints lines.
* `Names.txt` – Input file.

## 4. Line Addressing

Line addressing allows us to select specific lines or ranges of lines.

### A. Display a Specific Line

```bash
sed -n '2p' Names.txt
```

Displays only the second line.

### B. Display a Range of Lines

```bash
sed -n '2,4p' Names.txt
```

Displays lines 2 through 4.

## 5. Line Deletion

The `d` command deletes selected lines from the output stream. It does not permanently modify the original file unless in-place editing is used.

### A. Delete the Second Line

```bash
sed '2d' Names.txt
```

### B. Delete the First Line

```bash
sed '1d' Names.txt
```

### C. Delete the Last Line

```bash
sed '$d' Names.txt
```

Here, `$` represents the last line of the file.

## 6. Text Substitution

The substitution command replaces one text pattern with another.

**Syntax:**

```bash
sed 's/old/new/' filename
```

### A. Replace First Occurrence

```bash
sed 's/John/Amit/' Names.txt
```

By default, only the first occurrence of the matching text on each line is replaced.

### B. Replace All Occurrences

```bash
sed 's/John/Amit/g' Names.txt
```

The `g` flag performs global replacement on each line.

## 7. Permanent File Modification

The `-i` option modifies the original file directly.

### A. Direct In-Place Modification

```bash
sed -i 's/John/Amit/g' Names.txt
```

This permanently replaces all occurrences of `John` with `Amit` in the file.

### B. In-Place Modification with Backup

```bash
sed -i.bak 's/John/Amit/g' Names.txt
```

This modifies the original file and creates a backup named `Names.txt.bak`.

## 8. Regular Expression Anchors

Regular expression anchors are used to match text at specific positions.

### A. Caret (^) – Beginning of Line

```bash
sed 's/^John/Amit/' Names.txt
```

Replaces `John` only when it appears at the beginning of a line.

Example:

* `John Doe` becomes `Amit Doe`.
* `My friend John` remains unchanged.

### B. Dollar ($) – End of Line

```bash
sed 's/John$/Amit/' Names.txt
```

Replaces `John` only when it appears at the end of a line.

Example:

* `My friend John` becomes `My friend Amit`.
* `John Doe` remains unchanged.

## 9. Whitespace Transformation

The `sed` command can also replace spaces with other characters.

### A. Replace First Space

```bash
sed 's/ /_/' Names.txt
```

Example:

```text
John Michael Doe
```

Output:

```text
John_Michael Doe
```

### B. Replace All Spaces

```bash
sed 's/ /_/g' Names.txt
```

Output:

```text
John_Michael_Doe
```

## 10. Regular Expression Characters

### A. Dot (.)

The dot represents any single character.

```bash
sed 's/.at/XXX/' file.txt
```

It can match patterns such as `cat`, `bat`, and `hat`.

### B. Negation Character Class [^ ]

The expression `[^ ]` matches any character except a space.

### C. Word Matching [^ ]*

The expression `[^ ]*` matches zero or more non-space characters.

```bash
sed 's/[^ ]*/WORD/' file.txt
```

This replaces the first sequence of non-space characters in each line with `WORD`.

## 11. Capturing Groups and Backreferences

Capturing groups allow selected portions of text to be stored and reused during substitution.

### A. Capturing the First Word

```bash
sed 's/\([^ ]*\)/[\1]/' Names.txt
```

Example:

Input:

```text
John Doe
```

Output:

```text
[John] Doe
```

Here:

* `\(...\)` – Captures a group.
* `\1` – Refers to the first captured group.

### B. Capturing Two Words

```bash
sed 's/\([^ ]*\) \([^ ]*\)/\1-\2/' Names.txt
```

Example:

Input:

```text
John Doe
```

Output:

```text
John-Doe
```

Here:

* `\1` – First captured word.
* `\2` – Second captured word.

## 12. Core Experiment: Swapping the First Two Words

The following command swaps the first two words of every line in the file.

**Command:**

```bash
sed -i 's/^\([^ ]*\) \([^ ]*\)/\2 \1/' Names.txt
```

### Input File: Names.txt

```text
John Doe
Alice Smith
Rahul Sharma
Aniket Singh
```

### Output

```text
Doe John
Smith Alice
Sharma Rahul
Singh Aniket
```

### Explanation

| Pattern     | Function                                                               |
| ----------- | ---------------------------------------------------------------------- |
| `^`         | Matches the beginning of a line                                        |
| `\([^ ]*\)` | Captures the first word as Group 1                                     |
| ` `         | Matches the space between the words                                    |
| `\([^ ]*\)` | Captures the second word as Group 2                                    |
| `\2 \1`     | Replaces the original order with the second word followed by the first |

The `-i` option permanently saves the changes in the original file.

## 13. Procedure

1. Open the Linux terminal.
2. Create a text file named `Names.txt` using the `touch` command.
3. Add sample names to the file using Nano or another text editor.
4. Execute the combined command `date; who > logged_users.txt`.
5. Perform printing operations using `sed -n`.
6. Display specific lines and ranges using line addressing.
7. Delete selected lines using the `d` command.
8. Perform text substitution using the `s` command.
9. Use the `-i` option for permanent file modification.
10. Apply regular expression anchors to match text positions.
11. Use capturing groups and backreferences to swap the first two words.
12. Verify the modified contents using the `cat` command.

## 14. Applications

* Automating text editing in Linux.
* Searching and replacing text in files.
* Removing unwanted lines from files.
* Modifying configuration files.
* Processing large text files.
* Performing batch text transformations.
* Automating repetitive file-editing tasks.

## 15. Result

Successfully studied and implemented combined command execution, I/O redirection, and text manipulation using the Linux Stream Editor (`sed`). Performed line printing, deletion, substitution, permanent file modification, regular expression matching, and word swapping using captured groups and backreferences.
