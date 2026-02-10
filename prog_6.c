// Program 6: Build min-heap and max-heap from an unsorted array

#include <stdio.h>

// Swap utility
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify for max-heap at index i in array of size n
void maxHeapify(int arr[], int n, int i) {
    int largest = i;           // Initialize largest as root
    int left = 2 * i + 1;      // left child index
    int right = 2 * i + 2;     // right child index

    // If left child exists and is greater than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child exists and is greater than current largest
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root, swap and continue heapifying
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

// Heapify for min-heap at index i in array of size n
void minHeapify(int arr[], int n, int i) {
    int smallest = i;          // Initialize smallest as root
    int left = 2 * i + 1;      // left child index
    int right = 2 * i + 2;     // right child index

    // If left child exists and is smaller than root
    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }

    // If right child exists and is smaller than current smallest
    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }

    // If smallest is not root, swap and continue heapifying
    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

// Build max-heap from given array
void buildMaxHeap(int arr[], int n) {
    // Start from last internal node and heapify downwards
    for (int i = (n / 2) - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

// Build min-heap from given array
void buildMinHeap(int arr[], int n) {
    // Start from last internal node and heapify downwards
    for (int i = (n / 2) - 1; i >= 0; i--) {
        minHeapify(arr, n, i);
    }
}

// Utility to print an array
void printArray(const char *label, int arr[], int n) {
    printf("%s", label);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

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

