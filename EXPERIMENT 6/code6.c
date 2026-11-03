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
