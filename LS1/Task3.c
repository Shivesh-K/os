#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    char c;
    while (!feof(stdin))
    {
        c = getchar();
        if (c >= 'A' && c <= 'Z')
            c = c + 13 > 'Z' ? c - 13 : c + 13;
        else if (c >= 'a' && c <= 'z')
            c = c + 13 > 'z' ? c - 13 : c + 13;

        putchar(c);
    }
}