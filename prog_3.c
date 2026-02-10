// Program 3: Reverse traversal in a singly linked list

#include <stdio.h>
#include <stdlib.h>

// Node definition for singly linked list
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Create a new node with given data
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Insert a new node at the end of the list
void insertAtEnd(Node **head, int data) {
    Node *newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Forward traversal: print list from head to tail
void printList(Node *head) {
    Node *temp = head;
    printf("Forward traversal: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Reverse traversal using recursion:
// visits nodes from tail back to head without changing links
void printListReverse(Node *head) {
    if (head == NULL) {
        return;
    }
    // First go to the end of the list
    printListReverse(head->next);
    // Then print on the way back (reverse order)
    printf("%d ", head->data);
}

// Free all nodes in the list
void freeList(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node *head = NULL;

    // Build a simple list: 10 -> 20 -> 30 -> 40
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    insertAtEnd(&head, 40);

    // Show normal (forward) traversal
    printList(head);

    // Show reverse traversal (without modifying the list)
    printf("Reverse traversal: ");
    printListReverse(head);
    printf("\n");

    // Clean up memory
    freeList(head);

    return 0;
}
