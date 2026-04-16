#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Stack structure for browser history
typedef struct {
    char urls[MAX][100];
    int top;
} Stack;

// Initialize stack
void init(Stack *s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Check if stack is full
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Push URL onto stack
void push(Stack *s, char url[]) {
    if (isFull(s)) {
        printf("Stack Overflow! Cannot store more history.\n");
        return;
    }
    s->top++;
    strcpy(s->urls[s->top], url);
}

// Pop URL from stack
void pop(Stack *s, char result[]) {
    if (isEmpty(s)) {
        printf("Stack Underflow! No history available.\n");
        strcpy(result, "");
        return;
    }
    strcpy(result, s->urls[s->top]);
    s->top--;
}

// Peek current page
void peek(Stack *s, char result[]) {
    if (isEmpty(s)) {
        strcpy(result, "No page");
        return;
    }
    strcpy(result, s->urls[s->top]);
}

// Display stack
void display(Stack *s) {
    if (isEmpty(s)) {
        printf("No history available.\n");
        return;
    }

    printf("\n--- Browser History Stack ---\n");
    for (int i = s->top; i >= 0; i--) {
        printf("%s\n", s->urls[i]);
    }
}

int main() {
    Stack backStack, forwardStack;
    char current[100] = "Home";
    char url[100], temp[100];
    int choice;

    init(&backStack);
    init(&forwardStack);

    while (1) {
        printf("\n===== Browser History Menu =====\n");
        printf("Current Page: %s\n", current);
        printf("1. Visit New Page\n");
        printf("2. Go Back\n");
        printf("3. Go Forward\n");
        printf("4. Show Back History\n");
        printf("5. Show Forward History\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);

                // Push current page to back stack
                push(&backStack, current);

                // Clear forward stack
                init(&forwardStack);

                // Update current page
                strcpy(current, url);

                printf("Visited: %s\n", current);
                break;

            case 2:
                if (isEmpty(&backStack)) {
                    printf("No pages in back history!\n");
                } else {
                    // Push current page to forward stack
                    push(&forwardStack, current);

                    // Pop from back stack
                    pop(&backStack, temp);
                    strcpy(current, temp);

                    printf("Went Back to: %s\n", current);
                }
                break;

            case 3:
                if (isEmpty(&forwardStack)) {
                    printf("No pages in forward history!\n");
                } else {
                    // Push current page to back stack
                    push(&backStack, current);

                    // Pop from forward stack
                    pop(&forwardStack, temp);
                    strcpy(current, temp);

                    printf("Went Forward to: %s\n", current);
                }
                break;

            case 4:
                printf("\nBack History:\n");
                display(&backStack);
                break;

            case 5:
                printf("\nForward History:\n");
                display(&forwardStack);
                break;

            case 6:
                printf("Exiting Browser Simulation...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
