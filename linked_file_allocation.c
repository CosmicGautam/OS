#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10

typedef struct Node {
    int block;
    struct Node* next;
} Node;

void allocateFiles(int file_sizes[], int num_files, int disk_size) 
{
    int i, j;
    int disk[MAX_BLOCKS];
    Node* file_blocks[MAX_FILES] = {NULL};
    
    for (i = 0; i < disk_size; i++)
        disk[i] = -1;  

    for (i = 0; i < num_files; i++) 
    {
        int size = file_sizes[i];
        int start_block = -1;
        int current_block = -1;

        for (j = 0; j < disk_size; j++) 
        {
            if (disk[j] == -1) 
            {
                if (start_block == -1)
                    start_block = j;
                current_block = j;

                size--;
                if (size == 0)
                    break;
            } 
            else 
            {
                start_block = -1;
                size = file_sizes[i];
            }
        }

        if (size > 0) 
        {
            printf("File %d could not be allocated\n", i + 1);
            continue;
        }

        Node* head = NULL;
        Node* tail = NULL;

        for (j = start_block; j <= current_block; j++) 
        {
            disk[j] = i + 1;
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->block = j;
            new_node->next = NULL;

            if (head == NULL) 
            {
                head = new_node;
                tail = head;
            } 
            else 
            {
                tail->next = new_node;
                tail = new_node;
            }
        }
        file_blocks[i] = head;
        printf("File %d allocated from block %d to block %d\n", i + 1, start_block, current_block);
    }

    printf("\nDisk allocation:\n");
    for (i = 0; i < disk_size; i++)
        printf("%d ", disk[i]);
    printf("\n");

    for (i = 0; i < num_files; i++) 
    {
        Node* current = file_blocks[i];
        printf("File %d blocks: ", i + 1);
        while (current != NULL) 
        {
            printf("%d ", current->block);
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        printf("\n");
    }
}

int main() 
{
    int file_sizes[MAX_FILES] = {10, 20, 30, 40, 50};
    int num_files = 5;
    int disk_size = 100;
    
    allocateFiles(file_sizes, num_files, disk_size);
    
    return 0;
}