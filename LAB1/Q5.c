#include <stdio.h>
//BS to find the index of the first occurrence of 1  in a sorted binary array containing a run of 0s followed by 1s.
int part(int A[], int n) {
    int low = 0;
    int high = n - 1;
    int idx = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (A[mid] == 1) {
            //potential partition point found search left half for an earlier '1'
            idx = mid;
            high = mid - 1;
        } else {
            // A[mid] == 0 means go to search right half
            low = mid + 1;
        }
    }

    return idx;
}

int main() {
    //array where 0s followed by 1s
    int A[] = {0, 0, 0, 0, 0, 1, 1, 1, 1};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    int index = part(A, n);

    if (index != -1) {
        printf("Partition point found at Index: %d\n", index);
        if (index > 0) {
            printf("Elements: A[%d] = %d -> A[%d] = %d\n", index - 1, A[index - 1], index, A[index]);
        } else {
            printf("The array consists of only 1's.\n");
        }
    } else {
        printf("no 1's found in the array\n");
    }

    return 0;
}
