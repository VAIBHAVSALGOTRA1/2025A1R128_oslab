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
