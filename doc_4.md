## Program 4 – Doubly Linked List with Insert-After and Delete Operations

This program implements a **doubly linked list** using structures in C and demonstrates:

- Insertion of a new node **after a given node**.
- Deletion of a **given node** from the list.
- Forward and backward traversal to verify both `next` and `prev` links.

---

### (a) Explanation of Data Structures

The doubly linked list node is defined as:

```c
typedef struct DNode {
    int data;
    struct DNode *prev;
    struct DNode *next;
} DNode;
```

- **`data`**: Stores the integer value of the node.
- **`prev`**: Pointer to the **previous** node in the list (or `NULL` for the first node).
- **`next`**: Pointer to the **next** node in the list (or `NULL` for the last node).

The list itself is represented by a pointer to the **head** node:

- `DNode *head;`
  - `head == NULL` means the list is empty.
  - Otherwise, `head` points to the first node, and the list can be traversed using `next`.

---

### (b) Description of Functions Implemented

1. **`DNode *createNode(int data)`**
   - Dynamically allocates memory for a new doubly linked list node.
   - Initializes:
     - `newNode->data = data`
     - `newNode->prev = NULL`
     - `newNode->next = NULL`
   - If memory allocation fails, prints an error message and terminates the program.
   - Returns a pointer to the new node.

2. **`void insertAtEnd(DNode **head, int data)`**
   - Helper function to build the initial list.
   - Steps:
     - Creates a new node with the given `data`.
     - If the list is empty (`*head == NULL`), sets `*head = newNode`.
     - Otherwise, traverses to the last node using `next`.
     - Links the new node at the end:
       - `last->next = newNode`
       - `newNode->prev = last`

3. **`void insertAfter(DNode *givenNode, int data)`**
   - Inserts a new node **after** a specified `givenNode` in the list.
   - If `givenNode` is `NULL`, prints an error and returns.
   - Steps:
     - Creates a new node with the given data.
     - Adjusts pointers:
       - `newNode->next = givenNode->next`
       - `newNode->prev = givenNode`
       - `givenNode->next = newNode`
       - If `newNode->next` is not `NULL`, updates `newNode->next->prev = newNode`.
   - This keeps all `prev` and `next` links consistent.

4. **`void deleteNode(DNode **head, DNode *delNode)`**
   - Deletes the node pointed to by `delNode` from the doubly linked list.
   - If the list is empty or `delNode` is `NULL`, it returns without doing anything.
   - Handles three main cases:
     - **Deleting the head**:
       - If `*head == delNode`, moves `*head` to `delNode->next`.
     - **Disconnecting from next node**:
       - If `delNode->next != NULL`, sets `delNode->next->prev = delNode->prev`.
     - **Disconnecting from previous node**:
       - If `delNode->prev != NULL`, sets `delNode->prev->next = delNode->next`.
   - Finally, frees the memory of `delNode`.

5. **`void printForward(DNode *head)`**
   - Traverses the list from **head to tail** using `next` pointers.
   - Prints all node values in forward order:
     - Example output: `Forward: 10 20 30`

6. **`void printBackward(DNode *head)`**
   - First moves to the **last** node by following `next`.
   - Then traverses backward using `prev` pointers.
   - Prints node values in reverse order:
     - Example output: `Backward: 30 20 10`
   - Also used to verify that `prev` links are correctly maintained after insertions and deletions.

7. **`void freeList(DNode *head)`**
   - Frees all nodes in the list to avoid memory leaks.
   - Iterates from head using `next`, freeing each node.

---

### (c) Organization of `main()` Function

```c
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
```

The `main()` function demonstrates the use of the operations in a clear sequence:

1. **Initialization**:
   - Sets `head = NULL` (empty list).
2. **Create initial list**:
   - Calls `insertAtEnd` three times to create: `10 <-> 20 <-> 30`.
   - Prints the list forward and backward.
3. **Insert-after operation**:
   - Traverses to find the node with value `20`.
   - Calls `insertAfter(temp, 25)` to get: `10 <-> 20 <-> 25 <-> 30`.
   - Prints forward and backward again.
4. **Delete node (25)**:
   - Finds the node with value `25` and calls `deleteNode(&head, temp)`.
   - List becomes: `10 <-> 20 <-> 30`.
   - Prints the current state.
5. **Delete head node (10)**:
   - Calls `deleteNode(&head, head)` to remove the first node.
   - Head now points to `20`. List becomes: `20 <-> 30`.
   - Prints forward and backward again.
6. **Cleanup**:
   - Calls `freeList(head)` to free all remaining nodes.

---

### (d) Sample Output of a Complete Run

An example run of the program produces output similar to:

```text
Initial list:
Forward: 10 20 30
Backward: 30 20 10

After inserting 25 after 20:
Forward: 10 20 25 30
Backward: 30 25 20 10

After deleting 25:
Forward: 10 20 30
Backward: 30 20 10

After deleting head (10):
Forward: 20 30
Backward: 30 20
```

This output shows:

- The initial construction of a doubly linked list.
- Successful **insertion after a given node** (`25` after `20`).
- Successful **deletion of a specific node** (`25`).
- Correct maintenance of both `next` and `prev` pointers, verified by forward and backward traversal.

