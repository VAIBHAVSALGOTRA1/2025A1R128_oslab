# LINUX LAB – EXPERIMENT 6

## Memory Allocation and Virtual Memory in C

### 1. Aim

To understand dynamic heap memory allocation in C using `malloc()` and `free()`, observe demand paging by accessing memory in 4096-byte (4 KB) intervals, and monitor system RAM usage using the Linux `free -h` command.

### 2. Objectives

* Understand virtual memory and physical memory.
* Study dynamic memory allocation using `malloc()`.
* Understand demand paging and page faults.
* Observe Resident Set Size (RSS).
* Monitor RAM usage using `free -h`.
* Understand how memory is reclaimed after process termination.

### 3. Theory

#### Virtual Memory

Virtual memory is a memory management technique that allows a process to use a virtual address space independently of the actual physical RAM available.

#### Dynamic Memory Allocation – malloc()

The `malloc()` function requests a block of memory from the heap.

Syntax:

```c
pointer = malloc(size);
```

Example:

```c
char *memory = malloc(500 * 1024 * 1024);
```

This requests 500 MB of virtual memory. However, physical RAM is generally not allocated for every page immediately.

#### Demand Paging

Demand paging is a technique in which the operating system provides physical memory pages when a process actually accesses them.

For example:

```c
for (int i = 0; i < 500 * 1024 * 1024; i += 4096)
    memory[i] = 1;
```

This loop writes to one location every 4096 bytes, causing the operating system to back the accessed pages with physical memory.

#### Virtual Memory vs Physical Memory

| Term             | Meaning                                                                                 |
| ---------------- | --------------------------------------------------------------------------------------- |
| VSZ              | Total virtual address space used by a process.                                          |
| RSS              | Physical RAM currently occupied by a process.                                           |
| Page Frame       | A fixed-size block of physical memory.                                                  |
| Page Fault       | Occurs when a memory access requires the operating system to establish a valid mapping. |
| Minor Page Fault | A page fault that can be handled without reading the page from storage.                 |

**Note:** 4096 bytes (4 KB) is a common Linux page size, but the actual page size depends on the system.

### 4. Program – memory.c

Create a file named `memory.c` and write the following code:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <memory_in_MB>\n", argv[0]);
        return 1;
    }

    int mb = atoi(argv[1]);

    char *memory = (char *)malloc(mb * 1024 * 1024);

    if (memory == NULL)
    {
        printf("Allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < mb * 1024 * 1024; i += 4096)
    {
        memory[i] = 1;
    }

    printf("%d MB allocated. Running... Press Ctrl+C to exit.\n", mb);

    while (1)
        sleep(1);

    return 0;
}
```

### 5. Explanation of the Program

| Statement        | Explanation                                                            |
| ---------------- | ---------------------------------------------------------------------- |
| `int argc`       | Stores the number of command-line arguments.                           |
| `char *argv[]`   | Stores the command-line arguments.                                     |
| `atoi(argv[1])`  | Converts the memory size from string to integer.                       |
| `malloc()`       | Requests a memory block from the heap.                                 |
| `memory == NULL` | Checks whether allocation failed.                                      |
| `i += 4096`      | Moves to the next 4 KB memory page.                                    |
| `memory[i] = 1`  | Writes to each page, causing physical memory to be backed as required. |
| `sleep(1)`       | Keeps the program running for observation.                             |

### 6. Compilation and Execution

**Step 1: Create the C file**

```bash
nano memory.c
```

Paste the program and save it.

**Step 2: Compile the program**

```bash
gcc memory.c -o memory
```

**Step 3: Execute the program**

```bash
./memory 500
```

Sample output:

```text
500 MB allocated. Running... Press Ctrl+C to exit.
```

The program continues running until you press `Ctrl + C`.

### 7. System Memory Monitoring

Open a second terminal while the C program is running.

Execute:

```bash
watch -n 1 free -h
```

This displays RAM usage every second.

Example output:

```text
               total        used        free      shared  buff/cache   available
Mem:           3.8Gi       1.6Gi       1.6Gi       100Mi       600Mi       2.0Gi
Swap:          2.0Gi          0B       2.0Gi
```

After pressing `Ctrl + C` in the first terminal, observe the memory usage again.

The memory occupied by the terminated process becomes available for reuse by the operating system.

### 8. Experimental Observations

| Experimental Phase        | Memory Observation       | Explanation                                            |
| ------------------------- | ------------------------ | ------------------------------------------------------ |
| Before execution          | Normal RAM usage         | Operating system and background processes are running. |
| After `malloc()`          | Virtual memory increases | Memory address space is requested.                     |
| After page touching       | RSS generally increases  | Physical memory backs the accessed pages.              |
| After program termination | Memory is reclaimed      | Operating system releases the process memory.          |

**Note:** Actual RAM values depend on your computer, background processes, available memory and Linux configuration. The example values are illustrative.

### 9. Important Linux Commands

| Command                  | Purpose                             |
| ------------------------ | ----------------------------------- |
| `gcc memory.c -o memory` | Compiles the C program.             |
| `./memory 500`           | Requests 500 MB of memory.          |
| `free -h`                | Displays RAM and swap usage.        |
| `watch -n 1 free -h`     | Monitors memory usage every second. |
| `Ctrl + C`               | Stops the running program.          |
| `getconf PAGESIZE`       | Displays the system page size.      |

### 10. Precautions

* Do not allocate more memory than your system can safely handle.
* Start with a smaller value, such as `100 MB`, before trying `500 MB`.
* Large allocations may cause the Linux Out-of-Memory (OOM) mechanism to terminate processes.
* `malloc()` does not guarantee that all requested physical memory is immediately available.
* The program does not lock memory in RAM; pages may still be swapped under memory pressure.

### 11. Result

Successfully studied dynamic memory allocation using `malloc()`, demand paging through 4 KB page touching, and virtual versus physical memory concepts. Observed system RAM usage using the `free -h` and `watch` commands.
