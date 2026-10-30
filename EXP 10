# Process Creation and Synchronization Using fork() and wait()

## Aim

To write and execute a C program to create a child process using the `fork()` system call and synchronize the parent and child processes using the `wait()` system call.

## Description

This program demonstrates process creation and synchronization in the Linux operating system.

The `fork()` system call creates a new child process from an existing parent process. Both processes execute independently.

The child process displays its Process ID (PID) using `getpid()`, sleeps for 2 seconds using `sleep(2)`, and terminates using `exit(0)`.

Meanwhile, the parent process uses `wait(NULL)` to wait until the child process terminates. After termination, the parent displays the child's PID.

## Concepts Used

| Function     | Description                                  |
| ------------ | -------------------------------------------- |
| `fork()`     | Creates a new child process.                 |
| `getpid()`   | Returns the PID of the current process.      |
| `sleep(2)`   | Pauses execution for 2 seconds.              |
| `wait(NULL)` | Makes the parent wait for child termination. |
| `exit(0)`    | Terminates the process successfully.         |

## Header Files Used

* `stdio.h` – For input and output operations.
* `stdlib.h` – For the exit() function.
* `unistd.h` – For fork(), getpid() and sleep().
* `sys/wait.h` – For the wait() function.

## Source Code

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t p = fork();

    if(p == 0) {
        printf("child running with pid:%d", getpid());
        sleep(2);
        printf("child exiting...\n");
        exit(0);
    }
    else {
        printf("parent waiting for child to terminate \n");
        pid_t terminated_pid = wait(NULL);
        printf("parent terminated child pid:%d\n", terminated_pid);
    }

    return 0;
}
```

## Compilation

Compile the program using GCC:

```bash
gcc pidd.c -o pidd
```

## Execution

Run the program using:

```bash
./pidd
```

## Expected Output

```text
parent waiting for child to terminate
child running with pid:1234
child exiting...
parent terminated child pid:1234
```

*Note: The PID will be different each time the program runs. The order of the first two messages may also vary.*

## Working

1. The program starts execution from the main() function.
2. The fork() system call creates a child process.
3. The child process receives 0 as the return value of fork().
4. The child displays its PID using getpid().
5. The child sleeps for 2 seconds and then terminates.
6. The parent process executes wait(NULL) and waits for the child to finish.
7. After the child terminates, wait() returns the child's PID.
8. The parent displays the terminated child's PID and completes execution.

## Result

The program successfully demonstrates process creation using fork() and process synchronization using wait() in Linux. The parent process waits until the child process terminates.

## Author

**Vaibhav Salgotra**

B.Tech – Computer Science and Engineering

