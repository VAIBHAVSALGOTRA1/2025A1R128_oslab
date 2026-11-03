# LINUX LAB – EXPERIMENT 9

## Process Creation, fork() and Child Synchronization

### 1. Aim

To understand process creation using the `fork()` system call, identify parent and child processes using PIDs, and synchronize their execution using the `wait()` system call in C.

### 2. Objectives

* Understand processes and Process IDs (PIDs).
* Study `getpid()` and `getppid()`.
* Understand process creation using `fork()`.
* Learn the return values of `fork()`.
* Understand parent-child process relationships.
* Synchronize processes using `wait()`.

### 3. Theory

**Process:** A process is a program currently being executed by the operating system.

**PID:** A Process ID is a unique numerical identifier assigned to a process.

**getpid():** Returns the PID of the current process.

**getppid():** Returns the PID of the parent process.

**fork():** Creates a new child process by duplicating the calling process.

### 4. Understanding fork()

The `fork()` system call creates a new child process.

Syntax:

```c
pid_t p = fork();
```

Return values:

| Return Value   | Meaning                                           |
| -------------- | ------------------------------------------------- |
| `0`            | Returned to the child process.                    |
| Positive value | Returned to the parent; contains the child's PID. |
| `-1`           | Process creation failed.                          |

After `fork()`, both parent and child continue execution independently from the point where `fork()` was called.

### 5. Program 1 – Display Process ID

Create a file named `pid_demo.c`.

```c
#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Current PID: %d\n", getpid());

    return 0;
}
```

**Compile and execute:**

```bash
gcc pid_demo.c -o pid_demo
./pid_demo
```

**Sample Output:**

```text
Current PID: 4092
```

The PID will be different on your system.

### 6. Program 2 – Process Creation Using fork()

Create a file named `fork_demo.c`.

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t p = fork();

    if (p == 0)
    {
        printf("Child Process\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    }
    else if (p > 0)
    {
        printf("Parent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", p);
    }
    else
    {
        printf("Fork failed!\n");
        return 1;
    }

    return 0;
}
```

**Compile and execute:**

```bash
gcc fork_demo.c -o fork_demo
./fork_demo
```

**Sample Output:**

```text
Parent Process
Parent PID: 4000
Child PID: 4001
Child Process
Child PID: 4001
Parent PID: 4000
```

*Note: The output order may change because the operating system scheduler decides which process executes first.*

### 7. Program 3 – Parent and Child Synchronization Using wait()

Create a file named `wait_pattern.c`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p = fork();

    if (p == 0)
    {
        printf("Child working...\n");
        sleep(2);
        printf("Child exiting...\n");
        exit(0);
    }
    else if (p > 0)
    {
        pid_t child_pid = wait(NULL);
        printf("Child %d reaped successfully!\n", child_pid);
    }
    else
    {
        printf("Fork failed!\n");
        return 1;
    }

    return 0;
}
```

**Compile and execute:**

```bash
gcc wait_pattern.c -o wait_pattern
./wait_pattern
```

**Sample Output:**

```text
Child working...
Child exiting...
Child 5042 reaped successfully!
```

### 8. Program 4 – Complete Process Creation and Synchronization

Create a file named `main.c`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p = fork();

    if (p == 0)
    {
        printf("Child Running with PID: %d\n", getpid());

        sleep(2);

        printf("Child Exiting...\n");

        exit(0);
    }
    else if (p > 0)
    {
        printf("Parent Waiting for child to terminate...\n");

        pid_t terminated_pid = wait(NULL);

        printf("Parent Terminated Child PID: %d\n", terminated_pid);
    }
    else
    {
        printf("Fork failed!\n");
        return 1;
    }

    return 0;
}
```

**Compile and execute:**

```bash
gcc main.c -o main
./main
```

**Sample Output:**

```text
Parent Waiting for child to terminate...
Child Running with PID: 5042
Child Exiting...
Parent Terminated Child PID: 5042
```

### 9. Understanding wait()

The `wait()` system call is used by the parent process to wait for a child process to finish.

Syntax:

```c
wait(NULL);
```

Important points:

* Suspends the parent until a child terminates.
* Collects the child's termination status.
* Reaps the terminated child process.
* Returns the PID of the terminated child.
* Returns `-1` if no unwaited child is available or an error occurs.

Passing `NULL` means that the program does not store the child's detailed exit status.

### 10. Important System Calls

| Function    | Header File    | Purpose                                  |
| ----------- | -------------- | ---------------------------------------- |
| `fork()`    | `<unistd.h>`   | Creates a child process.                 |
| `getpid()`  | `<unistd.h>`   | Returns the current process ID.          |
| `getppid()` | `<unistd.h>`   | Returns the parent process ID.           |
| `wait()`    | `<sys/wait.h>` | Waits for a child process to terminate.  |
| `sleep()`   | `<unistd.h>`   | Suspends execution for a specified time. |
| `exit()`    | `<stdlib.h>`   | Terminates the calling process.          |

### 11. Parent vs Child Process

| Feature             | Parent Process         | Child Process                           |
| ------------------- | ---------------------- | --------------------------------------- |
| Creation            | Existing process       | Created using `fork()`.                 |
| fork() return value | Child PID              | 0                                       |
| PID                 | Its own PID            | A new PID                               |
| getppid()           | Its parent's PID       | Parent's PID                            |
| Execution           | Continues after fork() | Continues after fork()                  |
| wait()              | Can wait for child     | Does not wait for parent using `wait()` |

### 12. Precautions

* Include the required header files.
* Always check whether `fork()` was successful.
* Use `wait()` to collect the child's termination status.
* Remember that parent and child execution order is not fixed without synchronization.
* Use separate terminal executions for each program.

### 13. Result

Successfully studied process creation using `fork()`, identified parent and child processes using `getpid()` and `getppid()`, and synchronized parent-child execution using the `wait()` system call.
