#include <stdio.h>
#include <stdlib.h>
#define N 100
#define TRUE 1
typedef struct {
    int items[N];
    int head;   
    int tail;   
} message;

void producer(message *m);
void consumer(message *m);
int produce_item(void);
void consume_item(int item);
void enqueue_item(message *m, int item);
int dequeue_item(message *m);

int main() {  
    message m = {.head = 0, .tail = 0};
    int choice;
    int produced_items = 0;
   printf("\n1. Produce an item\n2. Consume an item\n3. Exit");
    while (TRUE) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (produced_items < N) {
                    producer(&m);
                    produced_items++;
                } else {
                    printf("Buffer is full! Cannot produce more items.\n");
                }
                break;
            case 2:
                if (produced_items > 0) {
                    consumer(&m);
                    produced_items--;
                } else {
                    printf("Buffer is empty! Cannot consume any items.\n");
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}

void producer(message *m) {
    int item = produce_item();
    enqueue_item(m, item);
    printf("Producer sent item %d\n", item);
}
void consumer(message *m) {
    int item = dequeue_item(m);
    printf("Consumer received item %d\n", item);
    consume_item(item);
}
int produce_item(void) {
    static int item = 0;
    printf("Produced item %d\n", item);
    return item++;
}
void consume_item(int item) {
    printf("Consumed item %d\n", item);
}
void enqueue_item(message *m, int item) {
    m->items[m->tail] = item;
    m->tail = (m->tail + 1) % N;
}
int dequeue_item(message *m) {
    int item = m->items[m->head];
    m->head = (m->head + 1) % N;
    return item;
}
