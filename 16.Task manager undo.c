/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Task structure
typedef struct Task {
    int id;
    char name[50];
    char status[20];  // "TODO", "IN-PROGRESS", "DONE"
    struct Task* next;
} Task;

// Stack Node for UNDO operations
typedef struct UndoAction {
    int actionType;  // 1=Add, 2=Edit, 3=Delete
    int taskId;
    char oldName[50];
    char oldStatus[20];
    struct UndoAction* next;
} UndoAction;

// Task Manager structure
typedef struct TaskManager {
    Task* head;
    int taskCount;
    UndoAction* undoStack;
    int undoCount;
} TaskManager;

// Function prototypes
TaskManager* createTaskManager();
void addTask(TaskManager* tm);
void editTask(TaskManager* tm);
void deleteTask(TaskManager* tm);
void undoLastAction(TaskManager* tm);
void displayTasks(TaskManager* tm);
Task* findTaskById(TaskManager* tm, int id);
void pushUndo(TaskManager* tm, int type, int id, char* name, char* status);
void displayMenu();
int getValidInt();
void getValidString(char* str, int maxLen);

// Initialize Task Manager
TaskManager* createTaskManager() {
    TaskManager* tm = (TaskManager*)malloc(sizeof(TaskManager));
    tm->head = NULL;
    tm->taskCount = 0;
    tm->undoStack = NULL;
    tm->undoCount = 0;
    return tm;
}

// Add new task
void addTask(TaskManager* tm) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    
    printf("Enter Task ID: ");
    newTask->id = getValidInt();
    
    printf("Enter Task Name: ");
    getValidString(newTask->name, 50);
    
    printf("Enter Status (TODO/IN-PROGRESS/DONE): ");
    getValidString(newTask->status, 20);
    
    // Check if ID exists
    if (findTaskById(tm, newTask->id)) {
        printf("❌ Task ID already exists!\n");
        free(newTask);
        return;
    }
    
    // Add to end of list
    newTask->next = tm->head;
    tm->head = newTask;
    tm->taskCount++;
    
    // Push ADD action to undo stack
    pushUndo(tm, 1, newTask->id, "", "");
    
    printf("✅ Task '%s' added! (Undo available)\n", newTask->name);
}

// Edit task
void editTask(TaskManager* tm) {
    if (tm->head == NULL) {
        printf("📝 No tasks to edit!\n");
        return;
    }
    
    int id;
    printf("Enter Task ID to edit: ");
    id = getValidInt();
    
    Task* task = findTaskById(tm, id);
    if (task == NULL) {
        printf("❌ Task not found!\n");
        return;
    }
    
    // Save old values for undo
    char oldName[50], oldStatus[20];
    strcpy(oldName, task->name);
    strcpy(oldStatus, task->status);
    
    printf("Current: %s (%s)\n", task->name, task->status);
    printf("New Name: ");
    getValidString(task->name, 50);
    printf("New Status (TODO/IN-PROGRESS/DONE): ");
    getValidString(task->status, 20);
    
    // Push EDIT action to undo stack
    pushUndo(tm, 2, id, oldName, oldStatus);
    
    printf("✅ Task '%s' updated! (Undo available)\n", task->name);
}

// Delete task
void deleteTask(TaskManager* tm) {
    if (tm->head == NULL) {
        printf("🗑️ No tasks to delete!\n");
        return;
    }
    
    int id;
    printf("Enter Task ID to delete: ");
    id = getValidInt();
    
    Task* task = findTaskById(tm, id);
    if (task == NULL) {
        printf("❌ Task not found!\n");
        return;
    }
    
    // Save for undo
    char taskName[50], taskStatus[20];
    strcpy(taskName, task->name);
    strcpy(taskStatus, task->status);
    
    // Remove from list
    Task* current = tm->head;
    Task* prev = NULL;
    
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }
    
    if (prev == NULL) {
        tm->head = current->next;
    } else {
        prev->next = current->next;
    }
    
    tm->taskCount--;
    
    // Push DELETE action to undo stack
    pushUndo(tm, 3, id, taskName, taskStatus);
    
    free(current);
    printf("✅ Task '%s' deleted! (Undo available)\n", taskName);
}

// UNDO - Pop last action from stack
void undoLastAction(TaskManager* tm) {
    if (tm->undoStack == NULL) {
        printf("❌ No actions to undo!\n");
        return;
    }
    
    UndoAction* lastAction = tm->undoStack;
    
    printf("🔄 Undoing: ");
    switch (lastAction->actionType) {
        case 1: // Undo ADD
            printf("ADD Task ID %d\n", lastAction->taskId);
            // Remove task that was added
            deleteTask(tm);  // Simple remove by ID
            break;
            
        case 2: // Undo EDIT - Restore old values
            printf("EDIT Task ID %d\n", lastAction->taskId);
            {
                Task* task = findTaskById(tm, lastAction->taskId);
                if (task) {
                    strcpy(task->name, lastAction->oldName);
                    strcpy(task->status, lastAction->oldStatus);
                    printf("✅ Restored: %s (%s)\n", task->name, task->status);
                }
            }
            break;
            
        case 3: // Undo DELETE - Restore task
            printf("DELETE Task ID %d\n", lastAction->taskId);
            {
                Task* restoredTask = (Task*)malloc(sizeof(Task));
                restoredTask->id = lastAction->taskId;
                strcpy(restoredTask->name, lastAction->oldName);
                strcpy(restoredTask->status, lastAction->oldStatus);
                restoredTask->next = tm->head;
                tm->head = restoredTask;
                tm->taskCount++;
                printf("✅ Restored: %s (%s)\n", restoredTask->name, restoredTask->status);
            }
            break;
    }
    
    // Pop from stack
    tm->undoStack = lastAction->next;
    free(lastAction);
    tm->undoCount--;
}

// Find task by ID
Task* findTaskById(TaskManager* tm, int id) {
    Task* current = tm->head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Push action to undo stack
void pushUndo(TaskManager* tm, int type, int id, char* name, char* status) {
    UndoAction* newAction = (UndoAction*)malloc(sizeof(UndoAction));
    newAction->actionType = type;
    newAction->taskId = id;
    strcpy(newAction->oldName, name);
    strcpy(newAction->oldStatus, status);
    newAction->next = tm->undoStack;
    tm->undoStack = newAction;
    tm->undoCount++;
}

// Display all tasks
void displayTasks(TaskManager* tm) {
    if (tm->head == NULL) {
        printf("\n📋 No tasks in manager!\n");
        return;
    }
    
    printf("\n📋 TASK MANAGER (%d tasks, %d undo actions available)\n", tm->taskCount, tm->undoCount);
    printf("============================================================\n");
    printf("ID | Name                    | Status\n");
    printf("---+-----+---------------------+--------\n");
    
    Task* current = tm->head;
    while (current != NULL) {
        printf("%-2d | %-22s| %s\n", 
               current->id, current->name, current->status);
        current = current->next;
    }
    printf("============================================================\n");
}

// Input validation
int getValidInt() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid input! Enter number: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return num;
}

void getValidString(char* str, int maxLen) {
    fgets(str, maxLen, stdin);
    str[strcspn(str, "\n")] = 0;  // Remove newline
    if (strlen(str) == 0) {
        strcpy(str, "Unnamed");
    }
}

// Display menu
void displayMenu() {
    printf("\n" "%s\n", "═══════════════════════════════════════════════════════════════════════");
    printf("📋 TASK MANAGER with UNDO STACK\n");
    printf("%s\n", "═══════════════════════════════════════════════════════════════════════");
    printf("1️⃣  ➕ Add Task\n");
    printf("2️⃣  ✏️  Edit Task\n");
    printf("3️⃣  🗑️  Delete Task\n");
    printf("4️⃣  🔄 Undo Last Action\n");
    printf("5️⃣  📋 Display Tasks\n");
    printf("0️⃣  ❌ Exit\n");
    printf("%s\n", "═══════════════════════════════════════════════════════════════════════");
    printf("Enter choice: ");
}

// Main function
int main() {
    printf("🚀 Task Manager with Undo Stack Started!\n");
    
    TaskManager* tm = createTaskManager();
    int choice;
    
    while (1) {
        displayMenu();
        choice = getValidInt();
        
        switch (choice) {
            case 1:
                addTask(tm);
                break;
            case 2:
                editTask(tm);
                break;
            case 3:
                deleteTask(tm);
                break;
            case 4:
                undoLastAction(tm);
                break;
            case 5:
                displayTasks(tm);
                break;
            case 0:
                printf("\n👋 Goodbye! All tasks saved in memory.\n");
                // Free memory (simplified)
                free(tm);
                return 0;
            default:
                printf("❌ Invalid choice!\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
    }
    
    return 0;
}
