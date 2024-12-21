#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10
#define BLOCK_SIZE 1
int i,j;
typedef struct {
    int block_indices[MAX_BLOCKS]; 
    int num_blocks; 
    int size; 
} Inode;

typedef struct {
    Inode inodes[MAX_FILES];
    int num_inodes;
    int free_blocks[MAX_BLOCKS]; 
    int num_free_blocks;
} FileSystem;

void initializeFileSystem(FileSystem *fs, int num_blocks) {
    fs->num_inodes = 0;
    fs->num_free_blocks = num_blocks;
 
    for ( i = 0; i < num_blocks; i++) {
        fs->free_blocks[i] = 0; 
    }
}

int allocateBlocks(FileSystem *fs, int num_blocks, int allocated_blocks[]) {
    int count = 0;
    for ( i = 0; i < MAX_BLOCKS && count < num_blocks; i++) {
        if (fs->free_blocks[i] == 0) {
            allocated_blocks[count++] = i;
            fs->free_blocks[i] = 1;
        }
    }
    return count; 
}

void createFile(FileSystem *fs, int size, int *file_index) {
    if (fs->num_inodes >= MAX_FILES) {
        printf("No more files can be created.\n");
        return;
    }

    int allocated_blocks[MAX_BLOCKS];
    int num_allocated = allocateBlocks(fs, size, allocated_blocks);

    if (num_allocated < size) {
        printf("Not enough free blocks to allocate the file.\n");
        return;
    }

    Inode *inode = &fs->inodes[fs->num_inodes];
    inode->num_blocks = num_allocated;
    inode->size = size;
    for ( i = 0; i < num_allocated; i++) {
        inode->block_indices[i] = allocated_blocks[i];
    }
    *file_index = fs->num_inodes;
    fs->num_inodes++;
    printf("File created with inode %d\n", *file_index);
}

void printFileSystem(FileSystem *fs) {
    printf("File System Status:\n");
    for ( i = 0; i < fs->num_inodes; i++) {
        Inode *inode = &fs->inodes[i];
        printf("Inode %d: Size %d, Blocks: ", i, inode->size);
        for ( j = 0; j < inode->num_blocks; j++) {
            printf("%d ", inode->block_indices[j]);
        }
        printf("\n");
    }
    printf("Free Blocks: ");
    for ( i = 0; i < MAX_BLOCKS; i++) {
        if (fs->free_blocks[i] == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    FileSystem fs;
    initializeFileSystem(&fs, MAX_BLOCKS);

    int file_index;

    createFile(&fs, 10, &file_index); 
    createFile(&fs, 15, &file_index); 
    createFile(&fs, 5, &file_index);  
    printFileSystem(&fs);

    return 0;
}
