#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}
int quickselect(int arr[], int low, int high, int k) {
    if (low == high)
        return arr[low];
    
    int pivotIndex = partition(arr, low, high);
    
    if (k == pivotIndex)
        return arr[k];
    else if (k < pivotIndex)
        return quickselect(arr, low, pivotIndex - 1, k);
    else
        return quickselect(arr, pivotIndex + 1, high, k);
}

float findMedian(int arr[], int n) {
    int *temp = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        temp[i] = arr[i];
    
    if (n % 2 == 1) {
        int median = quickselect(temp, 0, n - 1, n / 2);
        free(temp);
        return median;
    } else {
        int left = quickselect(temp, 0, n - 1, n / 2 - 1);
        int right = quickselect(temp, 0, n - 1, n / 2);
        free(temp);
        return (left + right) / 2.0;
    }
}

int main() {
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Median: %.2f\n", findMedian(arr, n));
    return 0;
}
