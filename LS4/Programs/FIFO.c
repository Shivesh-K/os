/*
	Written by: Vishv Malhotra
	For:	KXA254 Operating System
	Date:	August 2001
	
	The filter FIFO takes one command line arguments indicating 
	(1) the number of available page frames
	[BTW: FIFO=First paged in, fisrt paged out when a page frame needed.]
	
	The standard input is a stream of lines containing two items.
	Each line is: (1) Action and (2) page number. 
	
	An action can be R (=read to page); W (=write into page); or
	F (=Finish). Second argument is the page number on which the 
	action happenes.
	
	The program simulates a virtual memory system. It prints the 
	result indicating the number of read and write actions in 
	the stdin stream. It also tells us the number of page faults
	that resulted in page ins to occur. Number of page faults 
	leading to disk writes of dirty pages are also generated.
*/
	
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PAGES 1000
#define MAXINT 9999999

long frame[PAGES], dirty[PAGES], 
	where, frames;

void setup() {
	int i;
	
	where =0;
	for (i=0;i<frames;i++) {
		frame[i]=-1;
		dirty[i]=0;
	}
	ungetc(' ',stdin);
}

int fifo() {
	
	return where=(where+1)%frames;		
}
	
	

int main(int argc, char *argv[]) {
	long reads=0, writes=0, diskReads=0, diskWrites=0;
	int ll, i;
	long pg;
	char rw;

	if (argc!=2) {
		fprintf(stderr,"Usage: FIFO FrameCount\n");
		fprintf(stderr,"Frame count not to be over 128\n");
		exit(1);
	}
	
	frames = atoi(argv[1]);
	setup();
	
	while (1) { // Process pages
	
		scanf(" %c %li", &rw, &pg);		
		if (rw=='R') {
			reads++;
			for (i=0;i<frames;i++)
				if (frame[i]==pg) {
					i=frames+10;
				}
			if (i==frames)  {
				diskReads++;
				ll=fifo();  // Where read
			
				if (dirty[ll]==1) 
					diskWrites++;
				
				dirty[ll]=0;
				frame[ll]=pg;
			}
		}
		else if (rw=='W') {
			writes++;
			for (i=0;i<frames;i++)
				if (frame[i]==pg) {
					dirty[i]=1;
					i=frames+10;
				}
			if (i==frames) {//page did not exist
				diskReads++;
				ll=fifo();  // Where read
			
				if (dirty[ll]==1) 
					diskWrites++;
				
				dirty[ll]=1;
				frame[ll]=pg;
			}
		}
		else {break;}
	}
	
	printf("Stats\nRead accesses %15li\nWrite accesses %15li\n",reads,writes);
	printf("Reads from the disk %15li\nWrites to disk %15li\n", 
		diskReads,diskWrites);
	exit(0);
}
			
				
				
		
