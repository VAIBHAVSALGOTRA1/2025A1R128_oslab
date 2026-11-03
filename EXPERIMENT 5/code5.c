#include <stdio.h>

int main()
{
    char str[100];
    int start, length, i, count = 0;

    printf("Enter a string: ");
    fgets(str, 100, stdin);

    // Calculate string length
    while (str[count] != '\0' && str[count] != '\n')
    {
        count++;
    }

    printf("Length of string: %d\n", count);

    printf("Enter starting position: ");
    scanf("%d", &start);

    printf("Enter number of characters: ");
    scanf("%d", &length);

    printf("Substring: ");

    // Display substring
    for (i = start; i < start + length && i < count; i++)
    {
        printf("%c", str[i]);
    }

    printf("\n");

    return 0;
}
