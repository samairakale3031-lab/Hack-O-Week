#include <stdio.h>
#include <string.h>

#define MAX 100

// Structure for Contact
struct Contact {
    char name[50];
    char phone[15];
};

// Function to swap contacts
void swap(struct Contact *a, struct Contact *b) {
    struct Contact temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble Sort (Alphabetical order)
void sortContacts(struct Contact contacts[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(contacts[j].name, contacts[j + 1].name) > 0) {
                swap(&contacts[j], &contacts[j + 1]);
            }
        }
    }
}

// Binary Search
int binarySearch(struct Contact contacts[], int n, char target[]) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(contacts[mid].name, target);

        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // Not found
}

// Display contacts
void display(struct Contact contacts[], int n) {
    printf("\nContact List:\n");
    for (int i = 0; i < n; i++) {
        printf("%s - %s\n", contacts[i].name, contacts[i].phone);
    }
}

int main() {
    struct Contact contacts[MAX];
    int n;

    printf("Enter number of contacts: ");
    scanf("%d", &n);

    // Input contacts
    for (int i = 0; i < n; i++) {
        printf("\nEnter name: ");
        scanf("%s", contacts[i].name);
        printf("Enter phone: ");
        scanf("%s", contacts[i].phone);
    }

    // Sort contacts
    sortContacts(contacts, n);

    // Display sorted contacts
    display(contacts, n);

    // Search contact
    char searchName[50];
    printf("\nEnter name to search: ");
    scanf("%s", searchName);

    int index = binarySearch(contacts, n, searchName);

    if (index != -1) {
        printf("Contact Found: %s - %s\n",
               contacts[index].name,
               contacts[index].phone);
    } else {
        printf("Contact not found\n");
    }

    return 0;
}
