#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

//uniqueness check
bool dupes(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare);
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == arr[i + 1]) return true;
    }
    return false;
}

int main() {
    int arr[] = {7, 2, 9, 1, 5, 2, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (dupes(arr, n)) {
        printf("Duplicates found!\n");
    } else {
        printf("All elements are unique.\n");
    }

    return 0;
}
