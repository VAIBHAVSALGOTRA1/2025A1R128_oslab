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
