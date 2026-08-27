#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void generateRandomFile(const char *filename, int n) {
    FILE *fp = fopen(filename, "w");
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        fprintf(fp, "%d ", rand() % 1000);
    fclose(fp);
}

int* readFromFile(const char *filename, int *n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return NULL;
    
    int *arr = (int*)malloc(1000 * sizeof(int));
    *n = 0;
    while (fscanf(fp, "%d", &arr[*n]) != EOF)
        (*n)++;
    fclose(fp);
    return arr;
}

void writeToFile(const char *filename, int arr[], int n) {
    FILE *fp = fopen(filename, "w");
    for (int i = 0; i < n; i++)
        fprintf(fp, "%d ", arr[i]);
    fclose(fp);
}

int main() {
    int n = 20;
    generateRandomFile("heap_input.txt", n);
    
    int size;
    int *arr = readFromFile("heap_input.txt", &size);
    
    printf("Before sorting:\n");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    heapSort(arr, size);
    writeToFile("heap_output.txt", arr, size);
    
    printf("After sorting:\n");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    free(arr);
    return 0;
}
