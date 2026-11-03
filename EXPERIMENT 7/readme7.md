# LINUX LAB – EXPERIMENT 7

## CPU-Bound vs. I/O-Bound C Programs

### 1. Aim

To compare CPU-bound and I/O-bound C programs by observing CPU utilization, process execution states, and accumulated CPU time using the Linux `top` command.

### 2. Objectives

* Understand CPU-bound and I/O-bound processes.
* Study CPU utilization using `%CPU`.
* Understand process states R (Running) and S (Interruptible Sleep).
* Monitor accumulated CPU time using `TIME+`.
* Learn background process execution using `&`.
* Monitor specific processes using `top -p`.

### 3. Theory

**CPU-Bound Process**

A CPU-bound process spends most of its time performing calculations and using the processor.

Characteristics:

* Uses approximately 100% of one logical CPU core.
* Usually remains in state R.
* Accumulated CPU time increases rapidly.
* Performs very little waiting.

**I/O-Bound Process**

An I/O-bound process spends most of its time performing input/output operations or waiting.

Characteristics:

* Uses very little CPU time.
* Frequently enters state S when sleeping.
* Accumulated CPU time increases slowly.
* Performs operations such as file reading and writing.

### 4. Process States

| State | Meaning                                                    |
| ----- | ---------------------------------------------------------- |
| R     | Running or waiting in the CPU run queue.                   |
| S     | Interruptible sleep; waiting for an event.                 |
| D     | Uninterruptible sleep, commonly associated with I/O waits. |
| Z     | Zombie process.                                            |

### 5. Program 1 – I/O-Bound Program

Create a file named `io_bound.c`.

```c
#include <stdio.h>
#include <unistd.h>

int main()
{
    FILE *fp;

    printf("Starting I/O task...\n");

    while (1)
    {
        fp = fopen("dummy.txt", "w");

        if (fp != NULL)
        {
            fprintf(fp, "Writing disk data\n");
            fclose(fp);

            printf("File operation done\n");
        }

        sleep(1);
    }

    return 0;
}
```

**Explanation:**

* `FILE *fp` declares a file pointer.
* `fopen()` opens the file in write mode.
* `fprintf()` writes data into the file.
* `fclose()` closes the file and flushes its buffered output.
* `sleep(1)` pauses the process for one second.

**Sample Output:**

```text
Starting I/O task...
File operation done
File operation done
File operation done
```

### 6. Program 2 – CPU-Bound Program

Create a file named `cpu_bound.c`.

```c
#include <stdio.h>

int main()
{
    long long counter = 0;

    printf("Starting CPU computation task...\n");

    while (1)
    {
        counter++;

        if (counter % 100000000 == 0)
        {
            printf("CPU task running: %lld\n", counter);
        }
    }

    return 0;
}
```

**Explanation:**

* `long long counter = 0` initializes a counter.
* `while(1)` creates an infinite loop.
* `counter++` continuously performs calculations.
* The `if` condition prints a message after every 100 million iterations.
* The program continuously uses CPU resources.

**Sample Output:**

```text
Starting CPU computation task...
CPU task running: 100000000
CPU task running: 200000000
CPU task running: 300000000
```

### 7. Compilation and Execution

**Step 1: Compile both programs**

```bash
gcc io_bound.c -o io_bound
gcc cpu_bound.c -o cpu_bound
```

**Step 2: Run both programs in the background**

```bash
./io_bound &
./cpu_bound &
```

The `&` symbol runs a process in the background.

**Step 3: Find process IDs**

```bash
pgrep -af 'io_bound|cpu_bound'
```

Example:

```text
2451 ./io_bound
2452 ./cpu_bound
```

The numbers are example process IDs (PIDs). Your PIDs will be different.

### 8. Monitoring Using top

Use the following command:

```bash
top -p 2451,2452
```

Replace the example PIDs with your actual process IDs.

**Example Observation:**

```text
PID    USER   PR  NI  VIRT  RES  SHR  S  %CPU  %MEM  TIME+    COMMAND
2452   user   20   0  2488 1152 1024  R  99.8   0.0  2:14.32 cpu_bound
2451   user   20   0  2504 1280 1152  S   0.0   0.0  0:00.04 io_bound
```

### 9. Understanding top Output

| Metric  | Meaning                             |
| ------- | ----------------------------------- |
| PID     | Process identification number.      |
| USER    | Name of the process owner.          |
| PR      | Process priority.                   |
| NI      | Nice value.                         |
| VIRT    | Total virtual memory used.          |
| RES     | Physical memory currently occupied. |
| S       | Current process state.              |
| %CPU    | CPU utilization percentage.         |
| %MEM    | Percentage of physical memory used. |
| TIME+   | Total accumulated CPU time.         |
| COMMAND | Name of the running program.        |

### 10. Comparative Observation

| Evaluation Metric | CPU-Bound Program                 | I/O-Bound Program            |
| ----------------- | --------------------------------- | ---------------------------- |
| CPU Utilization   | Approximately 95–100% of one core | Very low                     |
| Process State     | Mostly R                          | Mostly S                     |
| TIME+             | Increases rapidly                 | Increases slowly             |
| Main Activity     | Continuous calculations           | File operations and sleeping |
| CPU Usage         | High                              | Low                          |

### 11. Important Linux Commands

| Command              | Purpose                                        |
| -------------------- | ---------------------------------------------- |
| `gcc file.c -o file` | Compiles a C program.                          |
| `./program &`        | Runs a program in the background.              |
| `pgrep -af 'name'`   | Finds running processes.                       |
| `top`                | Displays running processes.                    |
| `top -p PID`         | Monitors a specific process.                   |
| `jobs`               | Displays background jobs in the current shell. |
| `kill PID`           | Terminates a process.                          |

### 12. Stopping the Programs

After completing the observation, stop both background processes.

Use:

```bash
pkill -x cpu_bound
pkill -x io_bound
```

Alternatively, use their process IDs:

```bash
kill PID
```

Replace `PID` with the actual process ID.

### 13. Precautions

* Do not leave the CPU-bound program running unnecessarily.
* Use actual PIDs when monitoring processes.
* Stop both programs after completing the experiment.
* Run the programs in separate background processes.
* Observe CPU utilization for a few seconds to get meaningful readings.

### 14. Result

Successfully executed and compared CPU-bound and I/O-bound C programs. Observed CPU utilization, process states (R and S), and accumulated CPU time using the Linux `top` command.
