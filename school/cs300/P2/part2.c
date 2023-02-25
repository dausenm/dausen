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
	
	if(argc == 3){
		printf("%s\n", argv[2]);
		//if(isdigit(atoi(argv[2]))){
			//printf("\tD: here\n");
			int sz;
			char *ptr = argv[2];
			sz = atoi(ptr);
			//printf("D:%d\n", sz);
			MEM_SIZE = sz;
			//printf("D:HERE\n");
		//}
		//else printf("argv[2] not a digit, MEM_SIZE set to 256\n");
	}

	fp = fopen(argv[1], "r");

	if(fp == NULL){
		printf("Error: File not found: \"%s\"\n", argv[1]);
		return 1;
	}

	char value[256];

	long long pageNum;
	long long offset;
	long long TLBHits = 0;
	long long pageFaults = 0;
	long long pages = 0;

	char physMem[MEM_SIZE][MEM_SIZE];
	
	int physAddr = 0, frame, logAddr;
	
	int tlb[TLB_SIZE][2];
	int pageTable[MEM_SIZE];

	memset(tlb, -1, TLB_SIZE * 2 * sizeof(tlb[0][0]));
	memset(pageTable, -1, sizeof(pageTable));
	
	int mask = 255;
	int i;
	int hit;
	int data;
	int clock = 0;
	int lru[TLB_SIZE];
	int ptLru[PAGE_SIZE];
	
	while(fgets(value, 64, fp)){
		clock++;	//clock will be used to implement lru replacement
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
				lru[i] = clock;
				frame = tlb[i][1];
				data = physMem[tlb[i][1]][offset];
				break;
			}
		}
		if(hit) TLBHits++;

		//If not found in TLB, search in page table
		else if(hit != 1){
			int freeFrame = 0;
			int found = 0;
			for(i = 0; i < MEM_SIZE; i++){
				if(pageTable[i] == pageNum){
					frame = i;
					ptLru[i] = clock;
					found = 1;
					break;
				}
				if(pageTable[i]==-1){
					freeFrame = 1;
					pageFaults++;
					break;
				}
			}
			if(freeFrame == 1){
				pageTable[i] = pageNum;
				frame = i;
				ptLru[i] = clock;
			}

			if(found == 1){
				//replace in tlb using lru
				//find lru
				int min = findMin(lru, 16);

				tlb[min][0] = pageNum;
				tlb[min][1] = frame;
			}

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
				
				for(int j = 0; j < MEM_SIZE; j++){
					physMem[frame][j] = buffer[j];
				}

				int min = findMin(lru, 16);

				tlb[min][0] = pageNum;
				tlb[min][1] = frame;
			}
			else{
				pageFaults++;

				int min = findMin(ptLru, PAGE_SIZE);

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

				for(int j = 0; j < MEM_SIZE; j++){
					physMem[min][j] = buffer[j];
				}

				frame = min;

				//update tlb
				min = findMin(lru, 16);

				tlb[min][0] = pageNum;
				tlb[min][1] = frame;
			}

			data = physMem[frame][offset];
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

int findMin(int array[], int size){
	int rt = array[0];

	for(int i = 0; i < size; i++){
		if(array[i] < rt) rt = array[i];
	}

	return rt;
}