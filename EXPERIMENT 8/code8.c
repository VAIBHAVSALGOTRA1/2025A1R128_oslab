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
