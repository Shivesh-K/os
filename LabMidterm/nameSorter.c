/*
	Programmer: 	Vishv Malhotra
	For: 		KXA254 Operating Systems
	Date: 		Aug 2001
	Modified in Jan 2021 for use at LNMIIT OS Lab
	
	The program generates names. Many many names.
	It can also sort the names using a quick sort algorithm.
	To convince you that it does these functions, 
	You may specify command line parameters to print
	the lists.
	
	The command line parameters are 
	(1) Number of names you want to list. No more
		than 5000 please.
	(2) You can ask it to listnames or listsorted by
		placing the request as the second command
		line argument (third if you count the command).
		
	There is a third option for the last argument: listaccess.
	In deed, that is the main purpose of the program. You
	can ask the program to list all accesses it makes
	into the arrays in the program. It prints a line for 
	each access, telling the following:
	(1) What was it attempting on the location (read or write)
	(2) Where in the memory the accesss is made (virtual address).
	
	You can pipe this info to virtual memory simulator to
	determine how many page faults the access will causes 
	under different configurations of page size and memory size.
	
	Modifications:
	The original program was for 32-bit machine era!
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FIRST 61
#define LAST 53
int SIZE = sizeof(void *);

char names[500000];
int howmany;
char *list[10001];

void createnames()
{
	char *first[FIRST] = {"Bill", "William", "Jack", "Jill", "Ali",
						  "Lisa", "Charles", "Anne", "Anna", "Kylie",
						  "Malissa", "Jenny", "Julian", "Nicole", "Anglique",
						  "Jeff", "Rick", "John", "Kim", "Chris",
						  "Kris", "Rose", "Amenda", "Kathy", "Tom",
						  "Sue", "Susan", "Val", "Lily", "Joe",
						  "Mikhail", "Peter", "Calra", "Bret", "Alexander",
						  "Suzzy", "Shane", "Greg", "Mike", "Carmen",
						  "Jane", "Zeenat", "Ryk", "Greg", "Yasmin",
						  "Mandi", "Nick", "Tim", "James", "Jim",
						  "Wayne", "Doug", "Kangana", "Arnab",
						  "Narendra", "Siraj", "Rahul", "Donald", "Sushma",
						  "Ranjan", "Kamal"};
	char *last[LAST] = {"Howard", "Keating", "Clinton", "Bush", "Costello",
						"Beazley", "Bachchan", "Border", "Waugh", "Bacon",
						"Nguyen", "Warne", "Major", "Bullen", "McNeal",
						"Walrath", "Joshi", "Smith", "Sharma", "Downer",
						"Clark", "Armstrong", "Flintstone", "Lewis", "Ponting",
						"Cheek", "Orr", "Arafat", "Hussain", "Modi",
						"Raunat", "Goswami", "Gandhi", "Gupta", "Trump",
						"Biden", "Pujara", "Shastri", "Kohli", "Jadeja",
						"Bumrah", "Thakur", "Yadav", "Saini", "Sundar",
						"Mehra", "Saraswat", "Pandit", "Shami", "Meena",
						"Pant", "Singh", "Mittal"};

	int f = 0, m = 0, l = 0, n = 0, i;

	for (i = 0; i < howmany; i++)
	{
		list[i] = (char *)(names + n);
		f = (i + f) % FIRST;
		l = (i + f * l) % LAST;
		strcpy(names + n, first[f]);
		strcat(names + n, " ");
		strcat(names + n, last[l]);
		n += strlen(names + n);
		n++;
	}

	list[howmany] = names + n;
	strcpy(names + n, "");
}

void printlist()
{
	/* Lists the names */
	int i;
	for (i = 0; i < howmany; i++)
	{
		printf("%s\n", list[i]);
	}
}

void READ(void *p, int len)
{
	int i, t;
	t = len / SIZE;
	for (i = 0; i < t; i++)
		printf("R %ld\n", ((long)p) + SIZE * i - (long)p % SIZE);
}

void WRITE(void *p, int len)
{
	int i, t;
	t = len / SIZE;
	for (i = 0; i < t; i++)
		printf("W %ld\n", ((long)p) + SIZE * i - (long)p % SIZE);
}

void qsortnames(int left, int right, int prnt)
{

	/* This routine will sort the names in the global
    array list.
    In addition when prnt is true it prints the 
    accesses to arrays names and list. Thus, if nnn
    is an address in array list or names that is 
    accessed during sortin then it is listed. R indicates
    read access. W indicates a write access. Addresses are
    listed in multiple of SIZE only.
    
    Program is copied (and a bit modified) from The C Programming
    Languae, by Kernighan and Ritchie, 2nd edn, page 87.
*/
	char *tmp;
	int i, last, p;

	if (left >= right)
		return;
	p = (left + right) / 2;
	tmp = list[left];
	list[left] = list[p];
	list[p] = tmp;
	if (prnt)
	{
		READ(list + left, SIZE);
		WRITE(list + left, SIZE);
		READ(list + p, SIZE);
		WRITE(list + p, SIZE);
	}
	last = left;

	for (i = left + 1; i <= right; i++)
	{
		if (prnt)
		{
			READ(list + i, SIZE);
			READ(list + left, SIZE);
			READ(list[i], strlen(list[i]));
			READ(list[left], strlen(list[left]));
		}
		if (strcmp(list[i], list[left]) <= 0)
		{ // less than
			last++;
			tmp = list[last];
			list[last] = list[i];
			list[i] = tmp;
			if (prnt)
			{
				READ(list + last, SIZE), WRITE(list + last, SIZE);
				READ(list + i, SIZE);
				WRITE(list + i, SIZE);
			}
		}
	}
	tmp = list[left];
	list[left] = list[last];
	list[last] = tmp;
	if (prnt)
	{
		READ(list + left, SIZE);
		READ(list + last, SIZE);
		WRITE(list + left, SIZE);
		WRITE(list + last, SIZE);
	}

	qsortnames(left, last - 1, prnt);
	qsortnames(last + 1, right, prnt);
}

int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		fprintf(stderr, "Usage ./nameSorter How_many %s\n",
				"listnames|listsorted|listaccess");
		exit(1);
	}

	howmany = atoi(argv[1]);
	if (howmany < 1000 || howmany > 9999)
	{
		fprintf(stderr, "Please use minimum 1000 names and maximum 9999 names\n");
		exit(0);
	}

	createnames();
	if (strcmp(argv[2], "listnames") == 0)
		printlist();
	/* Sortnames and print info on accesses if required */
	if (strcmp(argv[2], "listaccess") == 0)
		qsortnames(0, howmany - 1, /* Print option */ 1);
	else
		qsortnames(0, howmany - 1, /* Print option */ 0);
	if (strcmp(argv[2], "listsorted") == 0)
		printlist();
	if (strcmp(argv[2], "listaccess") == 0)
		printf("F 000\n");
	exit(0);
}
