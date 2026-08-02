#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//terminates early if array becomes sorted before (n-1)th pass
long long optimizedbs(int arr[], int n) {
    long long c = 0;
    int swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            c++;
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        // If no two elements were swapped in inner loop, array is sorted
        if (!swapped) {
            break;
        }
    }
    return c;
}

//always completes the (n-1)th pass regardless of sorted status
long long stdbs(int arr[], int n) {
    long long c = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            c++;
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return c;
}

// to fill array with random integers
void ranarr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

//copy array contents
void copy(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main() {
    srand((unsigned int)time(NULL));

    int sizes[] = {100, 500, 1000, 5000, 10000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    printf("                         Bubble Sort Performance Analysis                              \n");
    printf("%-10s | %-25s | %-25s\n", "Size (n)", "Variant (i) [Optimized]", "Variant (ii) [Standard]");

    for (int k = 0; k < num_sizes; k++) {
        int n = sizes[k];

        // allocate dynamic memory for arrays
        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));

        // generate random data sequence
        ranarr(arr1, n);
        copy(arr1, arr2, n); // both variants run on identical input ensure it

        //simulations running
        long long comp_opt = optimizedbs(arr1, n);
        long long comp_std =stdbs(arr2, n);

        printf("%-10d | %-25lld | %-25lld\n", n, comp_opt, comp_std);

        free(arr1);
        free(arr2);
    }

    printf("=========================================================================\n");

    return 0;
}
