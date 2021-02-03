#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    char c;
    int count = 0;
    while (!feof(stdin))
    {
        c = getchar();
        if (!isalpha(c))
            putchar(c), ++count;
    }
    fprintf(stderr, "\n%d\n", count);
    exit(0);
}