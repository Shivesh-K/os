/*
	Programmer: Vishv Malhotra
	For:		KXA254
	Date:		Aug 2001
	
	The program is a filter to convert memory addresses into 
	page number references. Page size is given as the command
	line argument.
	
	Looking at the size of the program, it is not much of 
	program, I guess ;-P

   INPUT: THe program is written primarily to read the access lists
   produced by the nameSorter program. 
   
   The program is filter so you can run it as a stannd alone 
   program providing input from the keyboard and
   reading its output on your monitor screen. 
   
   OUTPUT: The accesses to the memory addresses that the 
   nameSorter program generated are converted into references
   to the page numbers that contain those addresses.
   
   USAGE: pageReferences pagesize
   pagesize should be power of 2
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

	long pageSize, j, mem;
	char rw;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: ./pageRefGen 16|32|64|128|256|512\n");
		exit(1);
	}

	j = pageSize = atoi(argv[1]);
	ungetc(' ', stdin);

	if (j != 16 && j != 32 && j != 64 && j != 128 && j != 256 && j != 512)
	{
		fprintf(stderr, "Usage: ./pageRefGen 16|32|64|128|256|512\n");
		exit(1);
	}

	while (1)
	{
		scanf(" %c %li", &rw, &mem);
		printf("%c %li\n", rw, mem / pageSize);
		if (rw == 'F')
			exit(0);
	}
}
