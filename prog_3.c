// Program 3: Reverse traversal in a singly linked list

#include <stdio.h>
#include <stdlib.h>

// Node definition for singly linked list
typedef struct Node {
    int data;
    struct Node *next;
} Node;

int main(void) {
    return 0;
}
// ... includes and Node as above ...

Node *createNode(int data) { /* as in final code */ }
void insertAtEnd(Node **head, int data) { /* as in final code */ }
void printList(Node *head) { /* as in final code */ }
void freeList(Node *head) { /* as in final code */ }

int main(void) {
    Node *head = NULL;

    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    insertAtEnd(&head, 40);

    printList(head);   // Forward only

    freeList(head);
    return 0;
}