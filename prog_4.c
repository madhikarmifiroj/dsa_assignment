// Program 4: Doubly linked list with insert-after and delete operations

#include <stdio.h>
#include <stdlib.h>

// Node definition for doubly linked list
typedef struct DNode {
    int data;
    struct DNode *prev;
    struct DNode *next;
} DNode;

// Create a new doubly linked list node
DNode *createNode(int data) {
    DNode *newNode = (DNode *)malloc(sizeof(DNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Insert a node at the end (helper to build initial list)
void insertAtEnd(DNode **head, int data) {
    DNode *newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    DNode *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

// Insert a new node with given data AFTER a given node
void insertAfter(DNode *givenNode, int data) {
    if (givenNode == NULL) {
        printf("Given node cannot be NULL\n");
        return;
    }

    DNode *newNode = createNode(data);

    newNode->next = givenNode->next;
    newNode->prev = givenNode;
    givenNode->next = newNode;

    if (newNode->next != NULL) {
        newNode->next->prev = newNode;
    }
}

// Delete a given node from the doubly linked list
void deleteNode(DNode **head, DNode *delNode) {
    if (*head == NULL || delNode == NULL) {
        return;
    }

    // If node to be deleted is head
    if (*head == delNode) {
        *head = delNode->next;
    }

    // Change next only if node to be deleted is NOT the last node
    if (delNode->next != NULL) {
        delNode->next->prev = delNode->prev;
    }

    // Change prev only if node to be deleted is NOT the first node
    if (delNode->prev != NULL) {
        delNode->prev->next = delNode->next;
    }

    free(delNode);
}

// Print list from head to tail
void printForward(DNode *head) {
    DNode *temp = head;
    printf("Forward: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Print list from tail to head (to verify prev links)
void printBackward(DNode *head) {
    if (head == NULL) {
        printf("Backward: (empty)\n");
        return;
    }

    // Go to last node
    DNode *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Traverse backwards using prev pointers
    printf("Backward: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

// Free all nodes
void freeList(DNode *head) {
    DNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    DNode *head = NULL;

    // Build initial list: 10 <-> 20 <-> 30
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);

    printf("Initial list:\n");
    printForward(head);
    printBackward(head);

    // Insert 25 after node with data 20
    DNode *temp = head;
    while (temp != NULL && temp->data != 20) {
        temp = temp->next;
    }
    if (temp != NULL) {
        insertAfter(temp, 25);
    }

    printf("\nAfter inserting 25 after 20:\n");
    printForward(head);
    printBackward(head);

    // Delete node with data 25
    temp = head;
    while (temp != NULL && temp->data != 25) {
        temp = temp->next;
    }
    if (temp != NULL) {
        deleteNode(&head, temp);
    }

    printf("\nAfter deleting 25:\n");
    printForward(head);
    printBackward(head);

    // Delete head node (10) to show head update
    if (head != NULL) {
        deleteNode(&head, head);
    }

    printf("\nAfter deleting head (10):\n");
    printForward(head);
    printBackward(head);

    // Clean up remaining nodes
    freeList(head);

    return 0;
}

