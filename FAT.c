#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10
#define CLUSTER_SIZE 1 
typedef struct {
    int next; 
    int is_allocated; 
} FATEntry;

void allocateFiles(int file_sizes[], int num_files, FATEntry fat[], int disk_size) 
{
    int i, j;
    
    for (i = 0; i < disk_size; i++) {
        fat[i].next = -1;
        fat[i].is_allocated = 0;
    }

    for (i = 0; i < num_files; i++) {
        int size = file_sizes[i];
        int start_block = -1;
        int current_block = -1;
        int last_block = -1;

        
        for (j = 0; j < disk_size; j++) {
            if (fat[j].is_allocated == 0) {
                if (start_block == -1) {
                    start_block = j;
                }
                current_block = j;
                size--;
                if (size == 0) {
                    break;
                }
            } else {
                start_block = -1;
                size = file_sizes[i];
            }
        }

        if (size > 0) {
            printf("File %d could not be allocated\n", i + 1);
            continue;
        }

        
        for (j = start_block; j <= current_block; j++) {
            fat[j].is_allocated = 1;
            fat[j].next = (j == current_block) ? -1 : j + 1;
        }
        printf("File %d allocated from block %d to block %d\n", i + 1, start_block, current_block);
    }

    printf("\nFAT Table:\n");
    for (i = 0; i < disk_size; i++) {
        if (fat[i].is_allocated) {
            printf("Block %d: Next %d\n", i, fat[i].next);
        }
    }
}

int main() 
{
    int file_sizes[MAX_FILES] = {10, 20, 30, 40, 50};
    int num_files = 5;
    int disk_size = 10;
    FATEntry fat[MAX_BLOCKS];

    allocateFiles(file_sizes, num_files, fat, disk_size);
    
    return 0;
}
