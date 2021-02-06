#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define INPUT_LEN 1024

void parseCmd(char cmd[], char *par[])
{
	char line[INPUT_LEN];
	int count = 0, i = 0, j = 0;
	char *array[100], *pch;

	while (true)
	{
		int c = fgetc(stdin);
		line[count++] = (char)c;
		if (c == '\n')
			break;
	}

	if (count == 1)
		return;
	pch = strtok(line, " \n");

	while (pch != NULL)
	{
		array[i++] = strdup(pch);
		pch = strtok(NULL, " \n");
	}

	strcpy(cmd, array[0]);

	for (int j = 0; j < i; ++j)
	{
		par[j] = array[j];
	}
	par[i] = NULL;
}

int main()
{
	char cmd[100], cmd[100], *parameters[20];
	int error = 1;

	while (true)
	{
		printf("$ ");
		parseCmd(cmd, parameters);

		if (fork() != 0)
		{
			wait(NULL);
		}
		else
		{
			strcpy(cmd, "/bin/");
			strcat(cmd, cmd);

			if (!strncmp(cmd, "cd", 2))
				chdir(parameters[1]);
			else
				error = execvp(cmd, parameters);
		}

		if (strcmp(cmd, "exit") == 0)
			return 0;

		if (error < 0)
			printf("Invalid Command \n\n");
	}

	return 0;
}