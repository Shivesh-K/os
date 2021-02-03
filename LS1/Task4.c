#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "\nError: Expected 2 arguments. Received either too many or too few!\n");
        exit(0);
    }
    else
    {
        int fdin, fdout;
        fdin = open(argv[1], O_RDONLY);
        if (fdin == -1)
            printf("\nError: File-1 could not be opened!\n");
        fdout = creat(argv[2], 0644);
        if (fdout == -1)
            printf("\nError: File-2 could not be opened!\n");

        close(0);
        dup(fdin);
        close(fdin);
        close(1);
        dup(fdout);
        close(fdout);

        int st, fd[2];
        pid_t p1;
        pid_t p2;

        if (pipe(fd) == -1)
        {
            fprintf(stderr, "\nError: Pipe failed!\n");
            exit(1);
        }
        p1 = fork();

        if (p1 < 0)
        {
            fprintf(stderr, "\nError: Child-1 could not be forked!\n");
            exit(1);
        }
        else if (p1 == 0)
        {
            close(fd[1]);
            close(0);
            dup(fd[0]);
            execl("Task2.c", "Task2.c", (char *)0);
        }
        p2 = fork();
        if (p2 < 0)
        {
            fprintf(stderr, "\nError: Child-2 could not be forked!\n");
            exit(1);
        }
        else if (p2 == 0)
        {
            close(fd[0]);
            close(0);
            dup(fd[1]);
            execl("Task3.c", "Task3.c", (char *)0);
        }
        close(fd[0]);
        close(fd[1]);
        wait(&st);
        wait(&st);

        close(fdin);
        close(fdout);
    }
}