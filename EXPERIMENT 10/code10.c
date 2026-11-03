#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p = fork();

    if (p == 0)
    {
        printf("Child running with PID: %d\n", getpid());
        sleep(2);
        printf("Child exiting...\n");
        exit(0);
    }
    else if (p > 0)
    {
        printf("Parent waiting for child to terminate...\n");

        pid_t terminated_pid = wait(NULL);

        printf("Parent terminated child PID: %d\n", terminated_pid);
    }
    else
    {
        printf("Fork failed!\n");
        return 1;
    }

    return 0;
}
