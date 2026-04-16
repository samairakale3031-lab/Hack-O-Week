#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

// Structure for a print job
typedef struct {
    int jobId;
    char fileName[50];
} Job;

Job queue[MAX];
int front = -1, rear = -1;

// Enqueue operation
void enqueue(int id, char name[]) {
    if (rear == MAX - 1) {
        printf("Queue Overflow! Printer queue is full.\n");
        return;
    }

    if (front == -1) front = 0;

    rear++;
    queue[rear].jobId = id;
    strcpy(queue[rear].fileName, name);

    printf("Job %d (%s) added to queue.\n", id, name);
}

// Dequeue operation
void dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue Underflow! No jobs to process.\n");
        return;
    }

    printf("Printing Job %d (%s)... Done!\n",
           queue[front].jobId,
           queue[front].fileName);

    front++;

    // Reset queue if empty
    if (front > rear) {
        front = rear = -1;
    }
}

// Display queue
void display() {
    if (front == -1 || front > rear) {
        printf("Queue is empty.\n");
        return;
    }

    printf("\nCurrent Printer Queue:\n");
    for (int i = front; i <= rear; i++) {
        printf("Job ID: %d, File: %s\n",
               queue[i].jobId,
               queue[i].fileName);
    }
}

// Main function
int main() {
    int choice, id;
    char name[50];

    while (1) {
        printf("\n--- Printer Queue Menu ---\n");
        printf("1. Add Print Job\n");
        printf("2. Process Print Job\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Job ID: ");
                scanf("%d", &id);
                printf("Enter File Name: ");
                scanf("%s", name);
                enqueue(id, name);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
