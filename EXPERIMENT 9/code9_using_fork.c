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
