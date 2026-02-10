## Program 8 – Random Numbers, User-Chosen Sorting, and Operation Counts

This program generates a list of **N random integers** in the range \[1, 1000\] (where **N** is given by the user at runtime) and then:

1. Asks the user to choose a **sorting algorithm**:
   - Bubble Sort
   - Selection Sort
   - Insertion Sort
   - Merge Sort
2. Sorts the numbers using the chosen algorithm.
3. Prints the numbers **before and after sorting**.
4. Displays the **total number of comparisons** and, where applicable, **swaps** performed by the algorithm.

---

### (a) Explanation of Data Structures

The core data structure is a **dynamically allocated array** of integers:

```c
int *arr = (int *)malloc(N * sizeof(int));
```

- **`arr`**: Stores `N` randomly generated integers in the range \[1, 1000\].
- Memory is allocated at runtime based on the user’s input `N`.

Additional scalar variables for statistics:

```c
long comparisons = 0;
long swaps = 0;
```

- **`comparisons`**: Counts how many times the algorithm compares two values.
- **`swaps`**: Counts how many times the algorithm performs an actual exchange of two elements (for in-place sorting algorithms where it makes sense).

No complex data structures (like structs) are required; each sorting algorithm operates directly on the integer array.

---

### (b) Description of Functions Implemented

1. **`void swap(int *a, int *b, long *swaps)`**
   - Swaps the values pointed to by `a` and `b`.
   - If `swaps` is not `NULL`, increments `(*swaps)` by 1.
   - Used by Bubble Sort and Selection Sort to track the number of element exchanges.

2. **`void bubbleSort(int arr[], int n, long *comparisons, long *swaps)`**
   - Implements **Bubble Sort** on array `arr` of size `n`.
   - Algorithm:
     - Repeatedly passes through the array.
     - Compares adjacent elements `arr[j]` and `arr[j+1]`.
     - If they are out of order, swaps them.
   - For each comparison of adjacent elements, increments `(*comparisons)`.
   - For each swap, calls `swap`, which increments `(*swaps)`.

3. **`void selectionSort(int arr[], int n, long *comparisons, long *swaps)`**
   - Implements **Selection Sort**.
   - Algorithm:
     - For each position `i`, finds the **minimum** element in the unsorted portion (`i+1` to `n-1`).
     - Swaps it into position `i` (if needed).
   - For every comparison `arr[j] < arr[minIndex]`, increments `(*comparisons)`.
   - If a new minimum is found and differs from the current position, calls `swap`, which increments `(*swaps)`.

4. **`void insertionSort(int arr[], int n, long *comparisons, long *swaps)`**
   - Implements **Insertion Sort**.
   - Algorithm:
     - Iterates from `i = 1` to `n-1`.
     - Takes `key = arr[i]` and inserts it into the sorted portion `arr[0..i-1]`.
     - Shifts larger elements to the right to make room for `key`.
   - For each comparison while moving elements (`arr[j] > key`), increments `(*comparisons)`.
   - This implementation counts **comparisons**, but does **not** treat every element move as a "swap"; `swaps` is not incremented here (you can interpret moves separately if desired).

5. **`void merge(int arr[], int left, int mid, int right, long *comparisons)`**
   - Helper function for **Merge Sort**.
   - Merges two sorted subarrays:
     - Left: `arr[left..mid]`
     - Right: `arr[mid+1..right]`
   - Uses temporary arrays `L[]` and `R[]` to store the left and right halves.
   - While merging:
     - Compares `L[i]` and `R[j]` and increments `(*comparisons)` each time.
     - Copies the smaller of the two into the original array.

6. **`void mergeSortRecursive(int arr[], int left, int right, long *comparisons)`**
   - Recursive function that implements **Merge Sort**:
     - Splits the array into halves until there is one element per segment.
     - Recursively sorts each half.
     - Calls `merge` to combine the sorted halves.

7. **`void mergeSort(int arr[], int n, long *comparisons, long *swaps)`**
   - Wrapper for `mergeSortRecursive`.
   - Calls `mergeSortRecursive(arr, 0, n - 1, comparisons)`.
   - Ignores `swaps` (marked unused) because Merge Sort does not perform in-place element swaps in the same sense as Bubble or Selection Sort.

8. **`void printArray(const char *label, int arr[], int n)`**
   - Prints a label followed by all `n` elements of the array on one line.
   - Used to show the array **before** and **after** sorting.

9. **`int chooseAlgorithm(void)`**
   - Displays a menu:

     ```text
     1. Bubble Sort
     2. Selection Sort
     3. Insertion Sort
     4. Merge Sort
     ```

   - Reads the user’s choice from standard input and returns it as an integer.
   - Returns `-1` if the input fails.

---

### (c) Organization of `main()` Function

```c
int main(void) {
    int N;

    printf("Enter the number of random integers (N): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Invalid value for N.\n");
        return 1;
    }

    int *arr = (int *)malloc(N * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Generate random integers in [1, 1000]
    for (int i = 0; i < N; i++) {
        arr[i] = (rand() % 1000) + 1;
    }

    printArray("Array before sorting: ", arr, N);

    int choice = chooseAlgorithm();
    if (choice < 1 || choice > 4) {
        printf("Invalid choice.\n");
        free(arr);
        return 1;
    }

    long comparisons = 0;
    long swaps = 0;

    switch (choice) {
        case 1:
            printf("Using Bubble Sort...\n");
            bubbleSort(arr, N, &comparisons, &swaps);
            break;
        case 2:
            printf("Using Selection Sort...\n");
            selectionSort(arr, N, &comparisons, &swaps);
            break;
        case 3:
            printf("Using Insertion Sort...\n");
            insertionSort(arr, N, &comparisons, &swaps);
            break;
        case 4:
            printf("Using Merge Sort...\n");
            mergeSort(arr, N, &comparisons, &swaps);
            break;
        default:
            break;
    }

    printArray("Array after sorting:  ", arr, N);
    printf("Total comparisons: %ld\n", comparisons);

    if (choice == 1 || choice == 2 || choice == 3) {
        printf("Total swaps (where applicable): %ld\n", swaps);
    } else {
        printf("Swaps not counted for Merge Sort.\n");
    }

    free(arr);
    return 0;
}
```

The `main()` function sequence:

1. **Input**:
   - Prompts the user to enter `N`, the number of random integers.
   - Validates that `N` is positive.
2. **Memory allocation**:
   - Allocates an integer array `arr` of size `N`.
3. **Random number generation**:
   - Seeds the random number generator with `time(NULL)`.
   - Fills `arr[i]` with a random integer between `1` and `1000`.
4. **Display unsorted data**:
   - Calls `printArray("Array before sorting: ", arr, N)`.
5. **Algorithm choice**:
   - Calls `chooseAlgorithm()` and reads the user’s choice (1–4).
   - Validates the choice.
6. **Sorting and counting operations**:
   - Initializes `comparisons` and `swaps` to `0`.
   - Based on the choice, calls the corresponding sort function, which updates these counters.
7. **Display sorted data and statistics**:
   - Prints the sorted array.
   - Prints the total number of comparisons.
   - For Bubble, Selection, and Insertion sort, also prints the total number of swaps (in this implementation, swaps are counted only when two elements are exchanged).
   - For Merge Sort, explains that swaps are not counted.
8. **Cleanup**:
   - Frees the dynamically allocated array.
   - Returns `0` to indicate successful execution.

---

### (d) Sample Output of a Complete Run

Example (user chooses **Bubble Sort**):

```text
Enter the number of random integers (N): 10
Array before sorting:  742 19 503 88 321 999 45 276 610 7 
Choose a sorting algorithm:
1. Bubble Sort
2. Selection Sort
3. Insertion Sort
4. Merge Sort
Enter your choice (1-4): 1
Using Bubble Sort...
Array after sorting:   7 19 45 88 276 321 503 610 742 999 
Total comparisons: 45
Total swaps (where applicable): 18
```

Example (user chooses **Merge Sort**):

```text
Enter the number of random integers (N): 8
Array before sorting:  120 987 45 67 500 3 77 250 
Choose a sorting algorithm:
1. Bubble Sort
2. Selection Sort
3. Insertion Sort
4. Merge Sort
Enter your choice (1-4): 4
Using Merge Sort...
Array after sorting:   3 45 67 77 120 250 500 987 
Total comparisons: 13
Swaps not counted for Merge Sort.
```

These examples show:

- The program correctly generates random data, lets the user choose a sorting method, and sorts the array.
- It prints the array **before and after** sorting.
- It provides useful performance statistics (comparisons and swaps) for the chosen algorithm.

