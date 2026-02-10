// Program 8: Random numbers, user-chosen sorting algorithm, and operation counts

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Swap utility and swap counter update
void swap(int *a, int *b, long *swaps) {
    int temp = *a;
    *a = *b;
    *b = temp;
    if (swaps != NULL) {
        (*swaps)++;
    }
}

// Bubble Sort
void bubbleSort(int arr[], int n, long *comparisons, long *swaps) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1], swaps);
            }
        }
    }
}

// Selection Sort
void selectionSort(int arr[], int n, long *comparisons, long *swaps) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(&arr[i], &arr[minIndex], swaps);
        }
    }
}

// Insertion Sort
void insertionSort(int arr[], int n, long *comparisons, long *swaps) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // First comparison to enter the loop (if any)
        while (j >= 0) {
            (*comparisons)++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
                // Treat this as a "move", not a swap of two existing elements,
                // so we do not increment swaps here.
            } else {
                break;
            }
        }
        arr[j + 1] = key;
        // No classic swaps counted for insertion sort in this implementation.
    }
}

// Merge function for Merge Sort
void merge(int arr[], int left, int mid, int right, long *comparisons) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        printf("Memory allocation failed in merge.\n");
        exit(1);
    }

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

void mergeSortRecursive(int arr[], int left, int right, long *comparisons) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortRecursive(arr, left, mid, comparisons);
        mergeSortRecursive(arr, mid + 1, right, comparisons);
        merge(arr, left, mid, right, comparisons);
    }
}

void mergeSort(int arr[], int n, long *comparisons, long *swaps) {
    (void)swaps; // swaps not applicable for merge sort in this implementation
    mergeSortRecursive(arr, 0, n - 1, comparisons);
}

// Utility to print array
void printArray(const char *label, int arr[], int n) {
    printf("%s", label);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Menu to choose sorting algorithm
int chooseAlgorithm(void) {
    int choice;
    printf("Choose a sorting algorithm:\n");
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Insertion Sort\n");
    printf("4. Merge Sort\n");
    printf("Enter your choice (1-4): ");
    if (scanf("%d", &choice) != 1) {
        return -1;
    }
    return choice;
}

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

    // Copy array so we can sort on the copy (optional; here we sort in-place)
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
            // Already validated, should not reach here
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

