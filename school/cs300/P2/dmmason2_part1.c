#include <stdio.h>
#include <stdlib.h>

#define TLB_SIZE 16
#define PAGE_SIZE 256
#define PAGE_TABLE_SIZE 256

int tlb[TLB_SIZE][2]; // TLB with 16 slots
int page_table[PAGE_TABLE_SIZE]; // Page table with 256 entries

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./program filename.txt\n");
        return 1;
    }

    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Unable to open file: %s\n", filename);
        return 1;
    }

    int num_hits = 0;
    int num_misses = 0;

    int i, j;
    for (i = 0; i < TLB_SIZE; i++) {
        tlb[i][0] = -1; // Initialize TLB entries to invalid page number
    }

    for (i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i] = -1; // Initialize page table entries to invalid frame number
    }

    char logical_address_str[10];
    int logical_address;
    int physical_address;
    int page_number;
    int page_offset;
    int frame_number;
    int signed_byte;
    while (fgets(logical_address_str, 10, fp)) {
        logical_address = atoi(logical_address_str);

        // Take logical address and extract page number and offset
        page_number = (logical_address >> 8) & 0xff;
        page_offset = logical_address & 0xff;

        printf("page number: %d, page offset: %d\n", page_number, page_offset);

        // Check if page number is in tlb
        int tlb_hit = 0;
        for (i = 0; i < TLB_SIZE; i++) {
            if (tlb[i][0] == page_number) {
            tlb_hit = 1;
            frame_number = tlb[i][1];
            num_hits++;
            break;
            }
        }

        // If not in tlb, check page table
        if (!tlb_hit) {
            if (page_table[page_number] == -1) {
                // Page fault, we must read page from backing store into physical memory
                char *filename = "BACKING_STORE.bin";
                FILE *fp_backing_store = fopen(filename, "rb");
                if (fp_backing_store == NULL) {
                    printf("Unable to open file: %s\n", filename);
                    return 1;  
                }
    
                fseek(fp_backing_store, page_number * PAGE_SIZE, SEEK_SET);
                char page_buffer[PAGE_SIZE];
                fread(page_buffer, 1, PAGE_SIZE, fp_backing_store);
                fclose(fp_backing_store);

                // Locate free frame
                int free_frame_number = -1;
                for (i = 0; i < PAGE_TABLE_SIZE; i++) {
                    if (page_table[i] == -1) {
                    free_frame_number = i;
                    break; 
                    }
                }

                // If no free frame, evict page from physical memory using FIFO policy
                if (free_frame_number == -1) {
                    free_frame_number = num_misses % PAGE_TABLE_SIZE;
                    int evicted_page_number = -1;
                    for (j = 0; j < PAGE_TABLE_SIZE; j++) {
                        if (page_table[j] == free_frame_number) {
                            evicted_page_number = j;
                            break;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
        