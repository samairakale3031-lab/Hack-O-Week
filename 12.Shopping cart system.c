/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Product Node Structure
struct Product {
    int id;
    char name[30];
    float price;
    int quantity;
    struct Product* next;
};

// Cart Structure
struct Cart {
    struct Product* head;
    int totalItems;
    float totalBill;
};

// Function Declarations
struct Cart* createCart();
void addAtHead(struct Cart* cart);
void addAtTail(struct Cart* cart);
void removeItem(struct Cart* cart);
void displayCart(struct Cart* cart);
void freeCart(struct Cart* cart);
int findItem(struct Cart* cart, int id);

// Create empty cart
struct Cart* createCart() {
    struct Cart* cart = (struct Cart*)malloc(sizeof(struct Cart));
    cart->head = NULL;
    cart->totalItems = 0;
    cart->totalBill = 0.0;
    return cart;
}

// Add item at HEAD
void addAtHead(struct Cart* cart) {
    struct Product* newItem = (struct Product*)malloc(sizeof(struct Product));
    
    printf("Enter Product ID: ");
    scanf("%d", &newItem->id);
    
    printf("Enter Product Name: ");
    scanf(" %s", newItem->name);
    
    printf("Enter Price: ");
    scanf("%f", &newItem->price);
    
    printf("Enter Quantity: ");
    scanf("%d", &newItem->quantity);
    
    // Check if ID already exists
    if (findItem(cart, newItem->id)) {
        printf("ID already exists!\n");
        free(newItem);
        return;
    }
    
    newItem->next = cart->head;
    cart->head = newItem;
    
    cart->totalItems++;
    cart->totalBill += (newItem->price * newItem->quantity);
    
    printf("✅ Added at HEAD!\n");
}

// Add item at TAIL
void addAtTail(struct Cart* cart) {
    struct Product* newItem = (struct Product*)malloc(sizeof(struct Product));
    
    printf("Enter Product ID: ");
    scanf("%d", &newItem->id);
    
    printf("Enter Product Name: ");
    scanf(" %s", newItem->name);
    
    printf("Enter Price: ");
    scanf("%f", &newItem->price);
    
    printf("Enter Quantity: ");
    scanf("%d", &newItem->quantity);
    
    // Check if ID already exists
    if (findItem(cart, newItem->id)) {
        printf("ID already exists!\n");
        free(newItem);
        return;
    }
    
    newItem->next = NULL;
    
    if (cart->head == NULL) {
        cart->head = newItem;
    } else {
        struct Product* temp = cart->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newItem;
    }
    
    cart->totalItems++;
    cart->totalBill += (newItem->price * newItem->quantity);
    
    printf("✅ Added at TAIL!\n");
}

// Remove item by ID
void removeItem(struct Cart* cart) {
    if (cart->head == NULL) {
        printf("Cart is empty!\n");
        return;
    }
    
    int id;
    printf("Enter ID to remove: ");
    scanf("%d", &id);
    
    struct Product* temp = cart->head;
    struct Product* prev = NULL;
    
    // Find item
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Item not found!\n");
        return;
    }
    
    // Remove from cart
    if (prev == NULL) {
        // First item
        cart->head = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    cart->totalItems--;
    cart->totalBill -= (temp->price * temp->quantity);
    
    free(temp);
    printf("✅ Item removed!\n");
}

// Display cart
void displayCart(struct Cart* cart) {
    if (cart->head == NULL) {
        printf("\n🛒 Cart is EMPTY!\n");
        return;
    }
    
    printf("\n🛒 SHOPPING CART (%d items):\n", cart->totalItems);
    printf("=====================================\n");
    printf("ID  | Name             | Price | Qty | Total\n");
    printf("----+--------------------+-------+-----+------\n");
    
    struct Product* temp = cart->head;
    while (temp != NULL) {
        float itemTotal = temp->price * temp->quantity;
        printf("%-3d| %-18s| $%.2f|  %2d | $%.2f\n",
               temp->id, temp->name, temp->price, 
               temp->quantity, itemTotal);
        temp = temp->next;
    }
    
    printf("=====================================\n");
    printf("TOTAL BILL: $%.2f\n", cart->totalBill);
}

// Find item by ID (returns 1 if found)
int findItem(struct Cart* cart, int id) {
    struct Product* temp = cart->head;
    while (temp != NULL) {
        if (temp->id == id) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// Free all memory
void freeCart(struct Cart* cart) {
    struct Product* temp;
    while (cart->head != NULL) {
        temp = cart->head;
        cart->head = cart->head->next;
        free(temp);
    }
    free(cart);
}

// Main function
int main() {
    struct Cart* cart = createCart();
    int choice;
    
    printf("🛒 === SHOPPING CART SYSTEM ===\n");
    printf("Dynamic Linked List Implementation\n\n");
    
    while (1) {
        printf("\n1. Add at HEAD\n");
        printf("2. Add at TAIL\n");
        printf("3. Remove by ID\n");
        printf("4. Display Cart\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addAtHead(cart);
                break;
            case 2:
                addAtTail(cart);
                break;
            case 3:
                removeItem(cart);
                break;
            case 4:
                displayCart(cart);
                break;
            case 0:
                printf("\n💰 Final Bill: $%.2f\n", cart->totalBill);
                printf("Thank you for shopping!\n");
                freeCart(cart);
                return 0;
            default:
                printf("Invalid choice!\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
    
    return 0;
}
