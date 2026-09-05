/* ============================================================
   Q1: 1D Array Operations and their Worst-Case Complexities
   ============================================================
   Input representation: a statically-declared int array of size n,
   read from stdin (unsorted, may contain duplicates).

   Operation                         Worst-case complexity
   -------------------------------   ----------------------
   (i)    Maximum element            O(n)
   (ii)   First & second largest     O(n)
   (iii)  Mean                       O(n)
   (iv)   Median                     O(n log n)  [sort-based;
                                       O(n) possible with median-of-
                                       medians selection, not used here]
   (v)    Standard deviation         O(n)
   (vi)   Mode                       O(n log n)  [sort-based]
   (vii)  Remove all duplicates      O(n log n)  [sort-based]
   (viii) Reverse the array          O(n)
   (ix)   Partition around pivot p   O(n)
          (elements < p pushed AFTER elements >= p)
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int cmp(const void *a, const void *b) { return (*(int*)a - *(int*)b); }

/* (i) O(n) */
int findMax(int a[], int n) {
    int mx = a[0];
    for (int i = 1; i < n; i++) if (a[i] > mx) mx = a[i];
    return mx;
}

/* (ii) O(n) - single pass */
void firstSecondLargest(int a[], int n, int *first, int *second) {
    *first = *second = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (a[i] > *first) { *second = *first; *first = a[i]; }
        else if (a[i] > *second && a[i] != *first) *second = a[i];
    }
}

/* (iii) O(n) */
double findMean(int a[], int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return (double)sum / n;
}

/* (iv) O(n log n) via sorting */
double findMedian(int a[], int n) {
    int *tmp = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) tmp[i] = a[i];
    qsort(tmp, n, sizeof(int), cmp);
    double med = (n % 2) ? tmp[n/2] : (tmp[n/2 - 1] + tmp[n/2]) / 2.0;
    free(tmp);
    return med;
}

/* (v) O(n) - needs mean, so O(n)+O(n)=O(n) */
double findStdDev(int a[], int n, double mean) {
    double sumSq = 0;
    for (int i = 0; i < n; i++) sumSq += (a[i] - mean) * (a[i] - mean);
    return sqrt(sumSq / n);
}

/* (vi) O(n log n) via sorting, then linear scan */
int findMode(int a[], int n) {
    int *tmp = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) tmp[i] = a[i];
    qsort(tmp, n, sizeof(int), cmp);
    int mode = tmp[0], bestCount = 1, curCount = 1;
    for (int i = 1; i < n; i++) {
        if (tmp[i] == tmp[i-1]) curCount++;
        else curCount = 1;
        if (curCount > bestCount) { bestCount = curCount; mode = tmp[i]; }
    }
    free(tmp);
    return mode;
}

/* (vii) O(n log n) via sorting, then compaction */
int removeDuplicates(int a[], int n, int result[]) {
    int *tmp = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) tmp[i] = a[i];
    qsort(tmp, n, sizeof(int), cmp);
    int k = 0;
    for (int i = 0; i < n; i++)
        if (i == 0 || tmp[i] != tmp[i-1]) result[k++] = tmp[i];
    free(tmp);
    return k; /* new length */
}

/* (viii) O(n) - two pointer swap */
void reverseArray(int a[], int n) {
    int i = 0, j = n - 1;
    while (i < j) { int t = a[i]; a[i] = a[j]; a[j] = t; i++; j--; }
}

/* (ix) O(n) - Lomuto-style partition, but flipped:
   elements < pivot go to the END, elements >= pivot stay at the FRONT */
int partitionAroundPivot(int a[], int n, int pivotValue) {
    int i = -1;
    for (int j = 0; j < n; j++) {
        if (a[j] >= pivotValue) {
            i++;
            int t = a[i]; a[i] = a[j]; a[j] = t;
        }
    }
    return i + 1; /* index where the "< pivot" block begins */
}

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of elements n: ");
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    printf("\nOriginal array: "); printArray(a, n);

    printf("\n(i) Max element = %d   [O(n)]\n", findMax(a, n));

    int f, s;
    firstSecondLargest(a, n, &f, &s);
    printf("(ii) First largest = %d, Second largest = %d   [O(n)]\n", f, s);

    double mean = findMean(a, n);
    printf("(iii) Mean = %.4f   [O(n)]\n", mean);

    printf("(iv) Median = %.4f   [O(n log n)]\n", findMedian(a, n));

    printf("(v) Std Dev = %.4f   [O(n)]\n", findStdDev(a, n, mean));

    printf("(vi) Mode = %d   [O(n log n)]\n", findMode(a, n));

    int *dedup = malloc(n * sizeof(int));
    int newLen = removeDuplicates(a, n, dedup);
    printf("(vii) After removing duplicates (len=%d): ", newLen);
    printArray(dedup, newLen);
    printf("      [O(n log n)]\n");
    free(dedup);

    int *rev = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) rev[i] = a[i];
    reverseArray(rev, n);
    printf("(viii) Reversed array: "); printArray(rev, n);
    printf("       [O(n)]\n");
    free(rev);

    int pivot;
    printf("\nEnter pivot value for partition test: ");
    scanf("%d", &pivot);
    int *part = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) part[i] = a[i];
    int idx = partitionAroundPivot(part, n, pivot);
    printf("(ix) Partitioned (>=pivot first, then <pivot), split index=%d: ", idx);
    printArray(part, n);
    printf("     [O(n)]\n");
    free(part);

    free(a);
    return 0;
}
