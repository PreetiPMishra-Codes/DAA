#include <stdio.h>
#include <stdlib.h>

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

int kthSmallest(int arr[], int low, int high, int k) {
    if (k > 0 && k <= high - low + 1) {
        int pos = partition(arr, low, high);
        
        if (pos - low == k - 1)
            return arr[pos];
        if (pos - low > k - 1)
            return kthSmallest(arr, low, pos - 1, k);
        
        return kthSmallest(arr, pos + 1, high, k - pos + low - 1);
    }
    return -1;
}

int main() {
    int arr[] = {7, 10, 4, 3, 20, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    printf("K'th smallest (k=%d): %d\n", k, kthSmallest(arr, 0, n - 1, k));
    return 0;
}
