#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
    generateRandomFile("input.txt", n);
    
    int size;
    int *arr = readFromFile("input.txt", &size);
    
    printf("Before sorting:\n");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    quickSort(arr, 0, size - 1);
    writeToFile("output.txt", arr, size);
    
    printf("After sorting:\n");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    free(arr);
    return 0;
}
