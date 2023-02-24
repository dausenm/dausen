#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int VM_SIZE = 256;
const int PAGE_SIZE = 256;
const int TLB_SIZE = 16;
int MEM_SIZE = 256;

int main(int argc, char* argv[])
{
	FILE *fp;
	
	if(argc < 2){
		printf("Error: Use ./a.out filename.txt\n");
		return 1;
	}

    if(argc == 3){
        if(!isdigit(argv[2])){
            printf("Error: usage ./a.out filename.txt PhysicalMemorySize. Continuing with MEM_SIZE =256\n");
        }
        else{
            int buf = atoi(argv[2]);
            MEM_SIZE = buf;
        }
    }

	fp = fopen(argv[1], "r");

	if(fp == NULL){
		printf("Error: File not found: \"%s\"\n", argv[1]);
		return 1;
	}

	char *value = NULL;

	size_t len = 0;
	size_t read;

	long long pageNum;
	long long offset;
	long long TLBHits = 0;
	long long pageFaults = 0;
	long long pages = 0;

	char physMem[MEM_SIZE][MEM_SIZE];
	
	int q = 0;	//to maintain the fifo replacement queue position
	int physAddr = 0, frame, logAddr;
	
	int tlb[TLB_SIZE][2];
	int pageTable[PAGE_SIZE];

	memset(tlb, -1, TLB_SIZE * 2 * sizeof(tlb[0][0]));
	memset(pageTable, -1, sizeof(pageTable));
	
	int mask = 255;
	int i;
	int hit;
	int data;
	
	while((read = getline(&value, &len, fp)) != -1){
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
				TLBHits++;
				frame = tlb[i][1];
				data = physMem[i][offset];
				break;
			}
		}

		//If not found in TLB, search in page table
		if(hit != 1){
			int freeFrame = 0;
			for(i = 0; i < PAGE_SIZE; i++){
				if(pageTable[i] == pageNum){
					frame = i;
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
			}
			//replace in tlb using fifo
			tlb[q][0] = pageNum;
			
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

			tlb[q][1] = i;

			physMem[i][0] = i;
			
			for(int j = 0; j < MEM_SIZE; j++){
				physMem[i][j] = buffer[j];
			}

			q++;
			q = q % 15;
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