#include <stdio.h>

//bs to find the transition point from 0 to 1
int find_partition(int A[], int n) {
    int low = 0, high = n - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (A[mid] == 1) {
            ans = mid;     //check left
            high = mid - 1;
        } else {
            low = mid + 1; //check right, otherwise
        }
    }
    return ans; 
}

int main() {
    int A[] = {0, 0, 0, 0, 1, 1, 1};
    int n = sizeof(A) / sizeof(A[0]);
    
    int index = find_partition(A, n);
    printf("Partition point (first 1) is at index: %d\n", index);
    return 0;
}
