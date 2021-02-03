#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    bool isEmpty = true;

    // Loop starts with 1 because the argument at index 0 is the path of the file which is not required
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] != '-')
        {
            isEmpty = false;
            printf("%s ", argv[i]);
        }
    }
    if (!isEmpty)
        printf("\n");
}