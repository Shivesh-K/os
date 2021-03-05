/*
	Written by: Vishv Malhotra
	For:	KXA254 Operating System
	Date:	August 2001
	
	The filter LRU takes a command line argument indicating the
	number of page frames in the main memory of the simulated memory
	in a virtual memory environment using least recently used 
	algorithm to free page frames.
	
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

long frame[PAGES], when[PAGES], dirty[PAGES], frames;

void setup() {
	long i;
	
	for (i=0;i<frames;i++) {
		frame[i]=-1;
		when[i]=-1;
		dirty[i]=0;
	}
	ungetc(' ',stdin);
}

int lru() {
	int i,j, time;
	
	for (i=0;i<frames;i++)
		if (frame[i]==-1)
			return i;
			
	time=MAXINT;
	j=-1;
	
	for (i=0;i<frames;i++) {
		if (when[i]>=time) continue;
		time = when[i];
		j=i;
	}
	return j;
}
	
	

int main(int argc, char *argv[]) {
	long reads=0, writes=0, diskReads=0, diskWrites=0, clock=-1;
	int ll, i;
	long pg;
	char rw;

	if (argc!=2) {
		fprintf(stderr,"Usage: LRU FrameCount\n");
		fprintf(stderr,"Frame count not to be over 1000\n");
		exit(1);
	}
	
	frames = atoi(argv[1]);
	setup();
	
	while (1) { // Process pages
	
		scanf(" %c %li", &rw, &pg);
		clock++;
		
		if (rw=='R') {
			reads++;
			for (i=0;i<frames;i++)
				if (frame[i]==pg) {
					when[i] = clock;
					i=frames+10;
				}
			if (i==frames)  {
				diskReads++;
				ll=lru();  // Where read
			
				if (dirty[ll]==1) 
					diskWrites++;
				
				dirty[ll]=0;
				frame[ll]=pg;
				when[ll]=clock;
			}
		}
		else if (rw=='W') {
			writes++;
			for (i=0;i<frames;i++)
				if (frame[i]==pg) {
					when[i] = clock;
					dirty[i]=1;
					i=frames+10;
				}
			if (i==frames) {//page did not exist
				diskReads++;
				ll=lru();  // Where read
			
				if (dirty[ll]==1) 
					diskWrites++;
				
				dirty[ll]=1;
				frame[ll]=pg;
				when[ll]=clock;
			}
		}
		else {break;}
	}
	
	printf("Stats\nRead accesses %15li\nWrite accesses %15li\n",reads,writes);
	printf("Reads from the disk %15li\nWrites to disk %15li\n", 
		diskReads,diskWrites);
	exit(0);
}
			
				
				
		
