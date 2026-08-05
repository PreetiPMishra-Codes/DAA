#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void merge2(int *arr, int l, int m, int r, int *temp) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (int x = l; x <= r; x++) arr[x] = temp[x];
}

void merge_sort(int *arr, int l, int r, int *temp) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    merge_sort(arr, l, m, temp);
    merge_sort(arr, m + 1, r, temp);
    merge2(arr, l, m, r, temp);
}

void merge3(int *arr, int l, int m1, int m2, int r, int *temp) {
    int i = l, j = m1 + 1, k = m2 + 1, idx = l;
    while (i <= m1 && j <= m2 && k <= r) {
        if (arr[i] <= arr[j] && arr[i] <= arr[k]) temp[idx++] = arr[i++];
        else if (arr[j] <= arr[i] && arr[j] <= arr[k]) temp[idx++] = arr[j++];
        else temp[idx++] = arr[k++];
    }
    while (i <= m1 && j <= m2) {
        if (arr[i] <= arr[j]) temp[idx++] = arr[i++];
        else temp[idx++] = arr[j++];
    }
    while (j <= m2 && k <= r) {
        if (arr[j] <= arr[k]) temp[idx++] = arr[j++];
        else temp[idx++] = arr[k++];
    }
    while (i <= m1 && k <= r) {
        if (arr[i] <= arr[k]) temp[idx++] = arr[i++];
        else temp[idx++] = arr[k++];
    }
    while (i <= m1) temp[idx++] = arr[i++];
    while (j <= m2) temp[idx++] = arr[j++];
    while (k <= r) temp[idx++] = arr[k++];
    for (int x = l; x <= r; x++) arr[x] = temp[x];
}

void merge_sort3(int *arr, int l, int r, int *temp) {
    int len = r - l + 1;
    if (len < 2) return;
    if (len == 2) {
        if (arr[l] > arr[r]) { int t = arr[l]; arr[l] = arr[r]; arr[r] = t; }
        return;
    }
    int third = len / 3;
    int m1 = l + third - 1;
    int m2 = m1 + third;
    merge_sort3(arr, l, m1, temp);
    merge_sort3(arr, m1 + 1, m2, temp);
    merge_sort3(arr, m2 + 1, r, temp);
    merge3(arr, l, m1, m2, r, temp);
}

int cmp_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int is_sorted(int *arr, int n) {
    for (int i = 1; i < n; i++) if (arr[i - 1] > arr[i]) return 0;
    return 1;
}

int main(void) {
    FILE *out = fopen("results_q2.csv", "w");
    if (!out) { perror("fopen"); return 1; }
    fprintf(out, "algorithm,n,time_sec\n");

    srand(42);
    int sizes[] = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];

        int *arr1 = malloc(sizeof(int) * n);
        int *temp1 = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) arr1[i] = rand();

        double t0 = now_sec();
        merge_sort(arr1, 0, n - 1, temp1);
        double t1 = now_sec();

        if (!is_sorted(arr1, n)) fprintf(stderr, "merge_sort failed at n=%d\n", n);
        fprintf(out, "MergeSort2Way,%d,%.9f\n", n, t1 - t0);
        free(arr1);
        free(temp1);

        int *arr2 = malloc(sizeof(int) * n);
        int *temp2 = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) arr2[i] = rand();

        t0 = now_sec();
        merge_sort3(arr2, 0, n - 1, temp2);
        t1 = now_sec();

        if (!is_sorted(arr2, n)) fprintf(stderr, "merge_sort3 failed at n=%d\n", n);
        fprintf(out, "MergeSort3Way,%d,%.9f\n", n, t1 - t0);
        free(arr2);
        free(temp2);

        fflush(out);
    }

    fclose(out);
    printf("Saved results_q2.csv\n");
    return 0;
}
