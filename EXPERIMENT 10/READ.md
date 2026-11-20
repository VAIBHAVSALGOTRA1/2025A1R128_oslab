# Experiment 10: Process Creation and Termination using C

## Aim
To write and execute a C program that creates a child process, waits for its termination, and displays its Process ID (PID).

## Objectives
* To understand process creation in Operating Systems.
* To create a child process using `fork()`.
* To wait for child process termination using `wait()`.
* To display the PID of both parent and child processes.

## Theory
A **process** is a program that is currently running. The following system calls and functions are used in this experiment:

1. **`fork()`**: Creates a new child process.
2. **`getpid()`**: Returns the current process ID.
3. **`getppid()`**: Returns the parent process ID.
4. **`wait()`**: Makes the parent process wait until the child process terminates.
5. **`exit()`**: Terminates a process.

## Source Code (`exp10.c`)
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    printf("Parent Process ID: %d\n", getpid());
    pid = fork();

    if (pid < 0) {
        printf("Process creation failed.\n");
    } else if (pid == 0) {
        printf("Child process created.\n");
        printf("Child Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());
        exit(0);
    } else {
        wait(NULL);
    }

    return 0;
}
