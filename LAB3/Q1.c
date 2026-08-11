#include <stdio.h>

int binCount = 0, terCount = 0;
int binarySearch(int arr[], int lo, int hi, int x) {
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        binCount++;
        if (arr[mid] == x) return mid;
        else if (arr[mid] < x) lo = mid + 1;
        else hi = mid - 1;
    }return -1;}
int ternarySearch(int arr[], int lo, int hi, int x) {
    while (lo <= hi) {
        int m1 = lo + (hi - lo) / 3;
        int m2 = hi - (hi - lo) / 3;
        terCount++;
        if (arr[m1] == x) return m1;
        terCount++;
        if (arr[m2] == x) return m2;
        if (x < arr[m1]) hi = m1 - 1;
        else if (x > arr[m2]) lo = m2 + 1;
        else { lo = m1 + 1; hi = m2 - 1; } }
   return -1;
}
int main() {
    int n;
    printf("Enter size of sorted array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d sorted elements: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    int x;
    printf("Enter element to search: ");
    scanf("%d", &x);
    int bi = binarySearch(arr, 0, n - 1, x);
    int ti = ternarySearch(arr, 0, n - 1, x);
    printf("Binary search found at index %d using %d comparisons\n", bi, binCount);
    printf("Ternary search found at index %d using %d comparisons\n", ti, terCount);
    printf("Binary search is generally better since it needs about log2(n) comparisons\n");
    printf("while ternary search needs about 2*log3(n), and log2(n) < 2*log3(n) for large n.\n");
    return 0;
}
