#include <stdio.h>
#include <stdlib.h>

int cmp_int(const void *a, const void *b) { return (*(int *)a) - (*(int *)b); }

int main(void) {
    int n;
    printf("Enter number of scientists n: ");
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    int *birth = malloc(n * sizeof(int));
    int *death = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("Scientist %d (birth death): ", i + 1);
        if (scanf("%d %d", &birth[i], &death[i]) != 2 || birth[i] > death[i]) return 1;
    }

    int *b_sorted = malloc(n * sizeof(int));
    int *d_sorted = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) { b_sorted[i] = birth[i]; d_sorted[i] = death[i]; }
    qsort(b_sorted, n, sizeof(int), cmp_int);
    qsort(d_sorted, n, sizeof(int), cmp_int);

    int i = 0, j = 0, alive = 0, best = 0, best_year = b_sorted[0];
    while (i < n) {
        if (j < n && d_sorted[j] <= b_sorted[i]) {
            alive--;
            j++;
        } else {
            alive++;
            if (alive > best) { best = alive; best_year = b_sorted[i]; }
            i++;
        }
    }

    printf("\nMax scientists alive simultaneously: %d\n", best);
    printf("First attained in year: %d\n", best_year);

    free(birth); free(death); free(b_sorted); free(d_sorted);
    return 0;
}
