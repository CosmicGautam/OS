#include <stdio.h>
#include <stdlib.h>

#define MAX_FILES 10

void allocateFiles(int file_sizes[], int num_files, int disk_size) 
{
    int i, j, allocated;
    int disk[disk_size];
    int start = 0;
    
    for (i = 0; i < disk_size; i++)
        disk[i] = 0;
    
    for (i = 0; i < num_files; i++) 
    {
        allocated = 0;
        for (j = 0; j <= disk_size - file_sizes[i]; j++) 
        {
            int k;
            for (k = j; k < j + file_sizes[i]; k++) 
            {
                if (disk[k] != 0) 
                    break;
            }
            if (k == j + file_sizes[i]) 
            {
                for (k = j; k < j + file_sizes[i]; k++)
                    disk[k] = i + 1;
                allocated = 1;
                break;
            }
        }
        if (allocated)
            printf("File %d allocated from %d to %d\n", i + 1, j, j + file_sizes[i] - 1);
        else
            printf("File %d could not be allocated\n", i + 1);
    }
    
    printf("\nDisk allocation:\n");
    for (i = 0; i < disk_size; i++)
        printf("%d ", disk[i]);
    printf("\n");
}

int main() 
{
    int file_sizes[MAX_FILES] = {10, 20, 30, 40, 50};
    int num_files = 5;
    int disk_size = 100;
    
    allocateFiles(file_sizes, num_files, disk_size);
    
    return 0;
}
