/*
	Written by: Vishv Malhotra
	For:	KXA254 Operating System
	Date:	August 2001
	
	The filter NRU takes two command line arguments indicating 
	(1) the number of available page frames
	(2) Indictive extend of not recently used. The measures are:
	shortDisuse, midDisuse, longDisuse.
	[BTW: NRU = Not recently used.]
	
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

long frame[PAGES], used[PAGES], dirty[PAGES], 
	frames, ahead, where;

void setup() {
	int i;
	
	where =0;
	for (i=0;i<frames;i++) {
		frame[i]=-1;
		used[i]=-1;
		dirty[i]=0;
	}
	ungetc(' ',stdin);
}

int nru() {
	int i;
	 for (i=0;i<frames;i++) 
	 	if (frame[i]==-1)
			return i;
	
	while (used[where]!=0) {
		used[(ahead+where)%frames]=0;
		where=(where+1)%frames;
	}
	used[(ahead+where)%frames]=0;
	return where;		
}
	
	

int main(int argc, char *argv[]) {
	long reads=0, writes=0, diskReads=0, diskWrites=0;
	int ll, i;
	long pg;
	char rw;
	
	if (argc==2) {
		fprintf(stderr,"Usage: NRU FrameCount shortDisuse|midDisuse|longDisuse\n");
		fprintf(stderr,"Frame count not to be over 128\n");
	} else if (argc!=3) {
		fprintf(stderr,"Usage: NRU FrameCount shortDisuse|midDisuse|longDisuse\n");
		fprintf(stderr,"Frame count not to be over 128\n");
		exit(1);
	}
	
	frames = atoi(argv[1]);
	
	if (frames<1 || frames>1000) {
		fprintf(stderr,"Usage: NRU FrameCount shortDisuse|midDisuse|longDisuse\n");
		fprintf(stderr,"Frame count not to be over 1000\n");
		exit(1);
	}
	
	if (argc ==2)
		ahead = frames/4;
	else {
		switch (argv[2][0]) {
		case 's':
		case 'S':
			ahead = frames/8;
			break;
		case 'l':
		case 'L':
			ahead=frames/2;
			break;
		default: 
			ahead=frames/4;
		}
	}
	
	setup();
	
	while (1) { // Process pages
	
		scanf(" %c %li", &rw, &pg);		
		if (rw=='R') {
			reads++;
			for (i=0;i<frames;i++)
				if (frame[i]==pg) {
					used[i] = 1;
					i=frames+10;
				}
			if (i==frames)  {
				diskReads++;
				ll=nru();  // Where read
			
				if (dirty[ll]==1) 
					diskWrites++;
				
				dirty[ll]=0;
				frame[ll]=pg;
				used[ll]=1;
			}
		}
		else if (rw=='W') {
			writes++;
			for (i=0;i<frames;i++)
				if (frame[i]==pg) {
					used[i] = 1;
					dirty[i]=1;
					i=frames+10;
				}
			if (i==frames) {//page did not exist
				diskReads++;
				ll=nru();  // Where read
			
				if (dirty[ll]==1) 
					diskWrites++;
				
				dirty[ll]=1;
				frame[ll]=pg;
				used[ll]=1;
			}
		}
		else {break;}
	}
	
	printf("Stats\nRead accesses %15li\nWrite accesses %15li\n",reads,writes);
	printf("Reads from the disk %15li\nWrites to disk %15li\n", 
		diskReads,diskWrites);
	exit(0);
}
			
				
				
		
