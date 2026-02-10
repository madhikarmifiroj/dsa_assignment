## Program 6 – Building Min-Heap and Max-Heap from an Unsorted Array

This program takes an **unsorted array of integers** and builds both a **min-heap** and a **max-heap** in-place using the bottom-up heap construction algorithm.

---

### (a) Explanation of Data Structures

The program uses simple **arrays** to represent heaps:

```c
int arr[] = {20, 5, 15, 22, 9, 1, 30};
int n = sizeof(arr) / sizeof(arr[0]);

int minHeapArr[sizeof(arr) / sizeof(arr[0])];
int maxHeapArr[sizeof(arr) / sizeof(arr[0])];
```

- **`arr`**: Original unsorted input array.
- **`minHeapArr`**: Copy of `arr` that will be transformed into a **min-heap**.
- **`maxHeapArr`**: Copy of `arr` that will be transformed into a **max-heap**.

The heap is stored in the array using **0-based indexing**:

- For a node at index `i`:
  - Left child index: `2 * i + 1`
  - Right child index: `2 * i + 2`

This structure is used by both min-heap and max-heap operations.

---

### (b) Description of Functions Implemented

1. **`void swap(int *a, int *b)`**
   - Utility function to swap two integers by pointer.
   - Used inside heapify functions when elements need to be reordered.

2. **`void maxHeapify(int arr[], int n, int i)`**
   - Maintains the **max-heap property** for the subtree rooted at index `i` in an array of size `n`.
   - Steps:
     - Assume `i` is the largest.
     - Compute left and right child indices: `left = 2*i + 1`, `right = 2*i + 2`.
     - If either child exists and has a value greater than `arr[largest]`, update `largest`.
     - If `largest` is not `i`, swap `arr[i]` with `arr[largest]` and recursively call `maxHeapify` on the affected child index.
   - After completion, the subtree rooted at `i` satisfies the max-heap property.

3. **`void minHeapify(int arr[], int n, int i)`**
   - Maintains the **min-heap property** for the subtree rooted at index `i`.
   - Similar to `maxHeapify`, but:
     - Tracks the **smallest** value instead of the largest.
     - Swaps with the smallest child when necessary.
   - Ensures the smallest element in the subtree moves towards the root of that subtree.

4. **`void buildMaxHeap(int arr[], int n)`**
   - Converts an entire array into a **max-heap** using bottom-up heap construction.
   - Starts from the **last internal node** `(n / 2) - 1` down to index `0`.
   - For each index `i`, calls `maxHeapify(arr, n, i)`.
   - After the loop, the entire array satisfies the max-heap property (root contains the maximum element).

5. **`void buildMinHeap(int arr[], int n)`**
   - Converts an entire array into a **min-heap**, using the same bottom-up approach.
   - Loops from `(n / 2) - 1` down to `0` and calls `minHeapify(arr, n, i)` for each index.
   - After completion, the root of the array contains the minimum element and the min-heap property holds.

6. **`void printArray(const char *label, int arr[], int n)`**
   - Utility function to print a label followed by all elements of an array on one line.
   - Used to show the original array, the min-heap, and the max-heap.

---

### (c) Organization of `main()` Function

```c
int main(void) {
    // Example unsorted array
    int arr[] = {20, 5, 15, 22, 9, 1, 30};
    int n = sizeof(arr) / sizeof(arr[0]);

    int minHeapArr[sizeof(arr) / sizeof(arr[0])];
    int maxHeapArr[sizeof(arr) / sizeof(arr[0])];

    // Copy original data to separate arrays for min and max heap
    for (int i = 0; i < n; i++) {
        minHeapArr[i] = arr[i];
        maxHeapArr[i] = arr[i];
    }

    printArray("Original array: ", arr, n);

    // Build and print min-heap
    buildMinHeap(minHeapArr, n);
    printArray("Min-heap array: ", minHeapArr, n);

    // Build and print max-heap
    buildMaxHeap(maxHeapArr, n);
    printArray("Max-heap array: ", maxHeapArr, n);

    return 0;
}
```

The `main()` function:

1. Defines an example unsorted array `arr`.
2. Determines its size `n`.
3. Creates two copies: `minHeapArr` and `maxHeapArr` so each heap is built independently from the same data.
4. Prints the original unsorted array.
5. Calls `buildMinHeap` and prints the resulting min-heap.
6. Calls `buildMaxHeap` and prints the resulting max-heap.
7. Exits with return value `0`.

---

### (d) Sample Output of a Complete Run

For the input array `{20, 5, 15, 22, 9, 1, 30}`, a sample run may produce:

```text
Original array: 20 5 15 22 9 1 30 
Min-heap array: 1 5 15 22 9 20 30 
Max-heap array: 30 22 20 5 9 1 15 
```

Explanation:

- **Min-heap array**:
  - The smallest element `1` is at index `0`.
  - For every node, its value is less than or equal to its children.
- **Max-heap array**:
  - The largest element `30` is at index `0`.
  - For every node, its value is greater than or equal to its children.

This confirms that the program correctly builds both min-heap and max-heap structures from the same unsorted input array using bottom-up heap construction.

