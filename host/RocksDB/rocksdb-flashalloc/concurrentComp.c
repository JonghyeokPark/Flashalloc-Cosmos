/*
 This file tracks comcurrently running compaction threads.
  > log file name (how to get log file? `grep "compaction_finished\|compaction_started" [RocksDB log file]` )
 */

#include <stdio.h>
#include <string.h>

// Level n --> SST files in level n+1 

int main (int argc, char * argv[]) {
	
	char buf[1024], *ptr, *ptr2;
	FILE *file ; 

	int i;
	long tempTime;
	int hour, min, sec;
	int year, month, date;
	int runningCompaction = 0 ;


	file = fopen(argv[1], "r");

	int bef=0; 
	int total =0 ;	
	int temp;
	
	while (1) {
		fgets (buf, sizeof(buf), file);

		if(feof(file))	break;

		ptr = strstr(buf, "-");
		sscanf(buf, "%d/%d/%d", &year, &month, &date);
		tempTime = month * (3600 * 24 * 30) + date * (3600 * 24);

		ptr++;
		sscanf(ptr, "%d:%d:%d", &hour, &min, &sec);
		tempTime += hour*3600 + min*60 + sec;

		if (strstr(buf, "compaction_started")) {	
//			printf("(Compaction started) %ld\n", tempTime);
			runningCompaction ++;
		} else if (strstr(buf, "compaction_finished")) { 
//			printf("(Compaction finished) %ld\n", tempTime);
			runningCompaction --;
		} else if (strstr(buf, "flush_started")) {
//			printf("(Flush started) %ld\n", tempTime);
			runningCompaction ++;
			bef = tempTime; 
		} else if (strstr(buf, "flush_finished")) {
//			printf("(Flush ended) %ld\n", tempTime);
			runningCompaction --;
			total += tempTime - bef;
		}

		printf("%ld %d\n", tempTime, runningCompaction);	
	}

	printf("%d\n", total);
	fclose(file);
	return 0;
}
