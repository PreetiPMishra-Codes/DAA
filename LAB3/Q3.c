#include <stdio.h>

int comparisons = 0;

void maxMin(int arr[], int lo, int hi, int *mx, int *mn) {
    if (lo == hi) {
        *mx = *mn = arr[lo];
        return;}
    if (hi - lo == 1) {
        comparisons++;
        if (arr[lo] < arr[hi]) { *mn = arr[lo]; *mx = arr[hi]; }
        else { *mn = arr[hi]; *mx = arr[lo]; }
        return;}
    int mid = (lo + hi) / 2;
    int lmx, lmn, rmx, rmn;
    maxMin(arr, lo, mid, &lmx, &lmn);
    maxMin(arr, mid + 1, hi, &rmx, &rmn);
    comparisons++;
    *mx = (lmx > rmx) ? lmx : rmx;
    comparisons++;
    *mn = (lmn < rmn) ? lmn : rmn;}
int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    int mx, mn;
    maxMin(arr, 0, n - 1, &mx, &mn);
    printf("Maximum = %d\n", mx);
    printf("Minimum = %d\n", mn);
    printf("Total comparisons = %d (bound is 3n/2 = %d)\n", comparisons, 3 * n / 2);
    return 0;
}
