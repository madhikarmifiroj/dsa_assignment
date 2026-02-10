## Program 3 – Reverse Traversal in a Singly Linked List

This program creates a **singly linked list** of integers and demonstrates **reverse traversal** of the list using a **recursive function**, without changing the actual links in the list.

---

### (a) Explanation of Data Structures

The program uses a standard singly linked list node:

```c
typedef struct Node {
    int data;
    struct Node *next;
} Node;
```

- **`data`**: Stores the integer value for each node in the list.
- **`next`**: A pointer to the next `Node` in the list.
  - If `next` is `NULL`, the node is the **last** node (tail) of the list.

The list is represented by a pointer to the **head** node (`Node *head`), which points to the first element in the list (or `NULL` if the list is empty).

---

### (b) Description of Functions Implemented

1. **`Node *createNode(int data)`**
   - Dynamically allocates memory for a new node.
   - Initializes:
     - `newNode->data = data`
     - `newNode->next = NULL`
   - If memory allocation fails, it prints an error message and exits the program.
   - Returns a pointer to the newly created node.

2. **`void insertAtEnd(Node **head, int data)`**
   - Inserts a new node with the given `data` at the **end** (tail) of the linked list.
   - If the list is empty (`*head == NULL`), the new node becomes the **head**.
   - Otherwise, it traverses the list until it reaches the last node and links the new node there.
   - This function helps build the sample list used in `main()`.

3. **`void printList(Node *head)`**
   - Performs a **forward traversal** of the list.
   - Starts from `head` and moves through each node using the `next` pointer.
   - Prints all node values from **head to tail** in order.
   - Output format:  
     `Forward traversal: 10 20 30 40`

4. **`void printListReverse(Node *head)`**
   - Implements **reverse traversal** using **recursion**.
   - Logic:
     - Base case: If `head == NULL`, return (end of list).
     - Recursive step: First call `printListReverse(head->next)` to go to the end of the list.
     - After returning from recursion (on the way back), print `head->data`.
   - Effect:
     - Nodes are printed from **tail back to head**.
     - The **linked list itself is not modified**; only the order of printing is reversed.

5. **`void freeList(Node *head)`**
   - Frees all nodes in the list to avoid memory leaks.
   - Iteratively moves through the list:
     - Stores the current node in `temp`.
     - Moves `head` to the next node.
     - Frees `temp`.
   - Stops when `head` becomes `NULL`.

---

### (c) Organization of `main()` Function

```c
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
```

The `main()` function is organized as follows:

1. **Initialization**:
   - Sets `head` to `NULL` to represent an empty list.
2. **List construction**:
   - Calls `insertAtEnd` four times to build the list:  
     `10 -> 20 -> 30 -> 40`.
3. **Forward traversal demo**:
   - Calls `printList(head)` to display the list from head to tail.
4. **Reverse traversal demo**:
   - Prints the label `"Reverse traversal: "`.
   - Calls `printListReverse(head)` to print the list from tail back to head using recursion.
5. **Cleanup**:
   - Calls `freeList(head)` to release dynamically allocated memory.
6. **Program termination**:
   - Returns `0` to indicate successful execution.

---

### (d) Sample Output of a Complete Run

When the program is compiled and run, the output will be similar to:

```text
Forward traversal: 10 20 30 40
Reverse traversal: 40 30 20 10
```

Explanation:
- **Forward traversal**:
  - Starts from the head (`10`) and follows `next` pointers: `10 → 20 → 30 → 40`.
- **Reverse traversal**:
  - The recursive function goes to the end of the list first, then prints on the way back:
    - Prints `40`, then `30`, then `20`, then `10`.

This demonstrates that the reverse traversal algorithm correctly visits all nodes of the singly linked list in reverse order **without changing** the original structure of the list.

