#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int cmp_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int* merge_two(int *a, int na, int *b, int nb) {
    int *res = malloc(sizeof(int) * (na + nb));
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        if (a[i] <= b[j]) res[k++] = a[i++];
        else res[k++] = b[j++];
    }
    while (i < na) res[k++] = a[i++];
    while (j < nb) res[k++] = b[j++];
    return res;
}

int* merge_k_sequential(int **arrs, int *sizes, int k, int *out_size) {
    int cur_size = sizes[0];
    int *cur = malloc(sizeof(int) * cur_size);
    memcpy(cur, arrs[0], sizeof(int) * cur_size);

    for (int i = 1; i < k; i++) {
        int *merged = merge_two(cur, cur_size, arrs[i], sizes[i]);
        free(cur);
        cur = merged;
        cur_size += sizes[i];
    }
    *out_size = cur_size;
    return cur;
}

int* merge_k_pairwise(int **arrs, int *sizes, int k, int *out_size) {
    int **cur = malloc(sizeof(int *) * k);
    int *cur_sizes = malloc(sizeof(int) * k);
    int cur_k = k;

    for (int i = 0; i < k; i++) {
        cur[i] = malloc(sizeof(int) * sizes[i]);
        memcpy(cur[i], arrs[i], sizeof(int) * sizes[i]);
        cur_sizes[i] = sizes[i];
    }

    while (cur_k > 1) {
        int next_k = (cur_k + 1) / 2;
        int **next = malloc(sizeof(int *) * next_k);
        int *next_sizes = malloc(sizeof(int) * next_k);

        int idx = 0;
        for (int i = 0; i + 1 < cur_k; i += 2) {
            next[idx] = merge_two(cur[i], cur_sizes[i], cur[i + 1], cur_sizes[i + 1]);
            next_sizes[idx] = cur_sizes[i] + cur_sizes[i + 1];
            free(cur[i]);
            free(cur[i + 1]);
            idx++;
        }
        if (cur_k % 2 == 1) {
            next[idx] = cur[cur_k - 1];
            next_sizes[idx] = cur_sizes[cur_k - 1];
            idx++;
        }

        free(cur);
        free(cur_sizes);
        cur = next;
        cur_sizes = next_sizes;
        cur_k = next_k;
    }

    int *result = cur[0];
    *out_size = cur_sizes[0];
    free(cur);
    free(cur_sizes);
    return result;
}

int is_sorted(int *arr, int n) {
    for (int i = 1; i < n; i++) if (arr[i - 1] > arr[i]) return 0;
    return 1;
}

int** make_k_sorted_arrays(int k, int n) {
    int **arrs = malloc(sizeof(int *) * k);
    for (int i = 0; i < k; i++) {
        arrs[i] = malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) arrs[i][j] = rand();
        qsort(arrs[i], n, sizeof(int), cmp_int);
    }
    return arrs;
}

void free_k_arrays(int **arrs, int k) {
    for (int i = 0; i < k; i++) free(arrs[i]);
    free(arrs);
}

int main(void) {
    FILE *out = fopen("results_q3.csv", "w");
    if (!out) { perror("fopen"); return 1; }
    fprintf(out, "method,varying,n,k,time_sec\n");

    srand(42);

    int fixed_n = 2000;
    int ks[] = {2, 4, 8, 16, 32, 64, 128, 256};
    int num_ks = sizeof(ks) / sizeof(ks[0]);

    for (int i = 0; i < num_ks; i++) {
        int k = ks[i];
        int *sizes = malloc(sizeof(int) * k);
        for (int j = 0; j < k; j++) sizes[j] = fixed_n;

        int **arrs1 = make_k_sorted_arrays(k, fixed_n);
        int out_size;
        double t0 = now_sec();
        int *r1 = merge_k_sequential(arrs1, sizes, k, &out_size);
        double t1 = now_sec();
        if (!is_sorted(r1, out_size)) fprintf(stderr, "sequential merge failed k=%d\n", k);
        fprintf(out, "Sequential,k,%d,%d,%.9f\n", fixed_n, k, t1 - t0);
        free(r1);
        free_k_arrays(arrs1, k);

        int **arrs2 = make_k_sorted_arrays(k, fixed_n);
        t0 = now_sec();
        int *r2 = merge_k_pairwise(arrs2, sizes, k, &out_size);
        t1 = now_sec();
        if (!is_sorted(r2, out_size)) fprintf(stderr, "pairwise merge failed k=%d\n", k);
        fprintf(out, "Pairwise,k,%d,%d,%.9f\n", fixed_n, k, t1 - t0);
        free(r2);
        free_k_arrays(arrs2, k);

        free(sizes);
        fflush(out);
    }

    int fixed_k = 16;
    int ns[] = {500, 1000, 2000, 4000, 8000, 16000, 32000, 64000};
    int num_ns = sizeof(ns) / sizeof(ns[0]);

    for (int i = 0; i < num_ns; i++) {
        int n = ns[i];
        int *sizes = malloc(sizeof(int) * fixed_k);
        for (int j = 0; j < fixed_k; j++) sizes[j] = n;

        int **arrs1 = make_k_sorted_arrays(fixed_k, n);
        int out_size;
        double t0 = now_sec();
        int *r1 = merge_k_sequential(arrs1, sizes, fixed_k, &out_size);
        double t1 = now_sec();
        if (!is_sorted(r1, out_size)) fprintf(stderr, "sequential merge failed n=%d\n", n);
        fprintf(out, "Sequential,n,%d,%d,%.9f\n", n, fixed_k, t1 - t0);
        free(r1);
        free_k_arrays(arrs1, fixed_k);

        int **arrs2 = make_k_sorted_arrays(fixed_k, n);
        t0 = now_sec();
        int *r2 = merge_k_pairwise(arrs2, sizes, fixed_k, &out_size);
        t1 = now_sec();
        if (!is_sorted(r2, out_size)) fprintf(stderr, "pairwise merge failed n=%d\n", n);
        fprintf(out, "Pairwise,n,%d,%d,%.9f\n", n, fixed_k, t1 - t0);
        free(r2);
        free_k_arrays(arrs2, fixed_k);

        free(sizes);
        fflush(out);
    }

    fclose(out);
    printf("Saved results_q3.csv\n");
    return 0;
}
