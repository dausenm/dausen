/*
	Written by Dausen Mason		CWID: 11955307
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int PAGE_SIZE = 256;
const int TLB_SIZE = 16;

int findMin(int array[], int size);

int main(int argc, char* argv[]){
	int MEM_SIZE = 256;

	FILE *fp;
	
	if(argc < 2){
		printf("Error: Use ./a.out filename.txt\n");
		return 1;
	}

	fp = fopen(argv[1], "r");

	if(fp == NULL){
		printf("Error: File not found: \"%s\"\n", argv[1]);
		return 1;
	}

	if(argc == 3){
		MEM_SIZE = atoi(argv[2]);
	}

	char value[256];

	long long pageNum;
	long long offset;
	long long TLBHits = 0;
	long long pageFaults = 0;
	long long pages = 0;

	char physMem[MEM_SIZE][PAGE_SIZE];
	
	int q = 0;	//to maintain the fifo replacement queue position for tlb
	int physAddr = 0, frame, logAddr;
	
	int tlb[TLB_SIZE][2];
	int pageTable[MEM_SIZE];

	memset(tlb, -1, TLB_SIZE * 2 * sizeof(tlb[0][0]));
	memset(pageTable, -1, sizeof(pageTable));
	
	int mask = 255;
	int i;
	int hit;
	int data;
	int lru[MEM_SIZE];
	int clock = 0;
	
	while(fgets(value, 64, fp)){
		clock++;
		pages++;		//increment pages at the top of the loop, keep track of how many pages we have looped through
		//get page number and offset from logical address
		pageNum = atoi(value);
		pageNum = pageNum >> 8;
		pageNum = pageNum & mask;
		
		offset = atoi(value);
		offset = offset & mask;
		
		logAddr = atoi(value);

		frame = 0, physAddr = 0;
		
		hit = 0;			//This will be set to 1 if it is found in TLB
		
		//Check in TLB for page
		
		for(i = 0; i < TLB_SIZE; i++){
			if(tlb[i][0] == pageNum){
				hit = 1;
				frame = tlb[i][1];
				data = physMem[tlb[i][1]][offset];
				lru[frame] = clock;
				break;
			}
		}
		if(hit) TLBHits++;

		//If not found in TLB, search in page table
		else if(hit != 1){
			int found = 0;
			int freeFrame = 0;
			for(i = 0; i < MEM_SIZE; i++){
				if(pageTable[i] == pageNum){
					frame = i;
					found = 1;
					lru[i] = clock;
					break;
				}
				if(pageTable[i] == -1){
					freeFrame = 1;
					pageFaults++;
					lru[i] = clock;
					break;
				}
			}
			if(freeFrame == 1){
				pageTable[i] = pageNum;
				frame = i;
			}

			//replace in tlb using fifo
			tlb[q][0] = pageNum;
			if(found || freeFrame)	tlb[q][1] = frame;

			if(freeFrame){
				//find value from BACKING_STORE.bin
				FILE *bs = fopen("BACKING_STORE.bin", "rb");

				if(bs == NULL){
					printf("Error: BACKING_STORE.bin not found.\n");
					return 1;
				}

				char buffer[PAGE_SIZE];

				fseek(bs, pageNum * PAGE_SIZE, SEEK_SET);
				fread(buffer, 256, 1, bs);

				data = (int)buffer[offset];

				fclose(bs);
				
				for(int j = 0; j < PAGE_SIZE; j++){
					physMem[frame][j] = buffer[j];
				}
			}

			if(!found && !freeFrame){
				pageFaults++;
				int min = findMin(lru, MEM_SIZE);

				pageTable[min] = pageNum;

				FILE *bs = fopen("BACKING_STORE.bin", "rb");

				if(bs == NULL){
					printf("Error: BACKING_STORE.bin not found.\n");
					return 1;
				}

				char buffer[PAGE_SIZE];

				fseek(bs, pageNum * PAGE_SIZE, SEEK_SET);
				fread(buffer, 256, 1, bs);

				data = (int)buffer[offset];

				fclose(bs);
				
				for(int j = 0; j < PAGE_SIZE; j++){
					physMem[min][j] = buffer[j];
				}
				
				frame = min;

				lru[min] = clock;

				tlb[q][1] = frame;
			}

			data = (int)physMem[frame][offset];

			q++;
			q = q % 16;
		}

		physAddr = frame * PAGE_SIZE + offset;
		printf("Virtual address: %d \t\tPhysical address: %d Value: %d\n", logAddr, physAddr, data);
	}
	double hitRate = ((double)TLBHits / (double)pages);
	double faultRate = ((double)pageFaults / (double)pages);

    printf("Number of Translated Addresses = %d\n", (int)pages);
    printf("Page Faults = %d\n", (int)pageFaults);
    printf("Page Fault Rate = %.3lf\n", faultRate);
    printf("TLB Hits = %d\n", (int)TLBHits);
    printf("TLB Hit Rate = %.3lf\n", hitRate);
}

int findMin(int array[], int size){		//findMin returns the index of the minimum element in the array that is taken in
	int min = array[0];
	int rt = 0;

	for (int i = 0; i < size; i++){
		if (array[i] < min) rt = i;
	}

	return rt;
}