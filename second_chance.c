#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int findAndUpdate(int x, int arr[], int second_chance[], int frames) 
{
    int i;
    for (i = 0; i < frames; i++) 
    { 
        if (arr[i] == x) 
        { 
            second_chance[i] = 1; 
            return 1; 
        } 
    } 
    return 0; 
} 

static int replaceAndUpdate(int x, int arr[], int second_chance[], int frames, int pointer) 
{ 
    while (1) 
    { 
        if (!second_chance[pointer]) 
        { 
            arr[pointer] = x; 
            return (pointer + 1) % frames; 
        } 
        second_chance[pointer] = 0; 
        pointer = (pointer + 1) % frames; 
    } 
} 

static void printHitsAndFaults(char *reference_string, int frames) 
{ 
    int pointer = 0, i, l = 0, x, pf = 0;
    int arr[frames];
    int second_chance[frames];
    char *token;
    
    memset(arr, -1, sizeof(arr)); 
    memset(second_chance, 0, sizeof(second_chance)); 
    
    token = strtok(reference_string, " ");
    while (token != NULL) 
    {
        x = atoi(token);
        if (!findAndUpdate(x, arr, second_chance, frames)) 
        { 
            pointer = replaceAndUpdate(x, arr, second_chance, frames, pointer); 
            pf++; 
        }
        token = strtok(NULL, " ");
    }
    printf("Total page faults were %d\n", pf);
}

int main()
{ 
    char reference_string[100];
    int frames; 

    // Test 1: 
    strcpy(reference_string, "0 4 1 4 2 4 3 4 2 4 0 4 1 4 2 4 3 4"); 
    frames = 3; 
    printHitsAndFaults(reference_string, frames); 
    
    // Test 2: 
    strcpy(reference_string, "2 5 10 1 2 2 6 9 1 2 10 2 6 1 2 1 6 9 5 1"); 
    frames = 4; 
    printHitsAndFaults(reference_string, frames); 

    return 0; 
}
