#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int VM_SIZE=256;
const int PAGE_SIZE=256;
const int TLB_SIZE=16;
const int MM_SIZE=256;

int main(int argc, char* argv[])
{
	FILE *fp;
	
	if(argc<2){
		printf("Error: Use ./a.out filename.txt\n");
		return 0;
	}

	fp = fopen(argv[1], "r");

	if(fp==NULL){
		printf("Error: File not found: \"%s\"\n", argv[1]);
		return 0;
	}

	char *value = NULL;

	size_t len = 0;
	size_t read;

	long long pageNum;
	long long offset;
	long long pageTable;
	long long TLBHits = 0;
	long long pageFaults = 0;
	long long pages = 0;
	
	int q = 0;	//to maintain the fifo replacement queue position
	int physAddr = 0, frame, logAddr;
	
	int tlb[TLB_SIZE][2];
	int pagetable[PAGE_SIZE];

	memset(tlb,-1,TLB_SIZE*2*sizeof(tlb[0][0]));
	memset(pagetable, -1, sizeof(pagetable));
	
	int mask = 255;
	int mask1 = 62580;
	int i;
	int hit;
	
	while((read = getline(&value, &len, fp)) != -1){
		pages++;		//increment pages at the top of the loop, keep track of how many pages we have looped through
		//get page number and offset from logical address
		pageNum = atoi(value);
		pageNum = pageNum >> 8;
		pageNum = pageNum & mask;
		
		offset = atoi(value);
		offset = offset & mask;
		
		logAddr = atoi(value);
		//printf("%lld %lld\n",pageNum,offset);
		frame = 0, physAddr = 0;
		
		hit = 0;			//This will be set to 1 if it is found in TLB
		
		//Check in TLB for page
		
		for(i = 0; i < TLB_SIZE; i++){
			if(tlb[i][0] == pageNum){
				hit=1;
				TLBHits++;
				frame = tlb[i][1];
				break;
			}
		}
		//If not found in TLB, search in page table
		if(hit != 1){
			int f = 0;
			for(i = 0; i < PAGE_SIZE; i++){
				if(pagetable[i] == pageNum){
					frame = i;
					break;
				}
				if(pagetable[i]==-1){
					f=1;
					pageFaults++;
					break;
				}
			}
			if(f==1){
				pagetable[i] = pageNum;
				frame = i;
			}
			//replace in tlb using fifo
			tlb[q][0] = pageNum;
			tlb[q][1] = i;
			q++;
			q = q % 15;		
		}

		physAddr = frame * PAGE_SIZE + offset;
		printf("Virtual address: %d \t\tPhysical address: %d Value: %d\n", logAddr, physAddr, 0);
	}
	double hitrate = ((double)TLBHits / (double)pages);
	double faultrate = ((double)pageFaults / (double)pages);

    printf("Number of Translated Addresses = %d\n", (int)pages);
    printf("Page Faults = %d\n", (int)pageFaults);
    printf("Page pageFaults Rate = %.3lf\n", faultrate);
    printf("TLB Hits = %d\n", (int)TLBHits);
    printf("TLB Hit Rate = %.3lf\n", hitrate);
}