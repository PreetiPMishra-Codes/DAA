/**
 * @file Q1.c
 * @author Preeti Pragyan Mishra
 * @course Design and Analysis of Algorithms (DAA)
 * @description Compares and ranks the growth rates of various mathematical 
 *              functions for increasing values of n using insertion sort.
 */

#include <stdio.h>
#include <math.h>

// Structure to store function name and value
typedef struct {
    const char *name;
    double value;
} FuncVal;
//sorting all funcs in ascending order based on their results using insertion sort algo.
//insertion sort is optimal and lightweight as total no.of functions are less
void sortFunctions(FuncVal arr[], int n) {
    for (int i = 1; i < n; i++) {
        FuncVal key = arr[i];
        int j = i - 1;

      // shifting elements that are greater than key.value to one position ahead
        while (j >= 0 && arr[j].value > key.value) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
  //array of sample sizes chosen to demonstrate asymptotic behaviour as n->infinity
    double nval[] = {100.0, 1000.0, 10000.0};
    int num = sizeof(nval) / sizeof(nval[0]);

    printf("FUNCTION GROWTH RATE COMPARISON\n\n");
// looping through each input size n to observe how functions scale dynamically
    for (int k = 0; k < num; k++) {
        double n = nval[k];
        printf("----------------------------------------\n");
        printf("For n = %.0f:\n", n);
        printf("----------------------------------------\n");

      FuncVal funcs[] = {
            {"n * log2(n)",     n * log2(n)},             // Linearithmic: O(n log n)
            {"12 * sqrt(n)",    12.0 * sqrt(n)},          // Sub-linear: O(n^0.5)
            {"n^(log2(n))",     pow(n, log2(n))},         // Quasi-polynomial: O(n^(log n))
            {"100*n^2 + 6*n",   100.0 * n * n + 6.0 * n}, // Quadratic: O(n^2) with large coefficient
            {"n^0.51",          pow(n, 0.51)},            // Sub-linear: slightly faster than sqrt(n)
            {"n^2 - 324",       n * n - 324.0},           // Quadratic: O(n^2) standard
            {"50 * n^0.5",      50.0 * pow(n, 0.5)},      // Sub-linear: O(n^0.5) with constant multiplier
            {"2*n^3",           2.0 * pow(n, 3)},         // Cubic: O(n^3)
            {"3^n",             pow(3.0, n)},             // Exponential: O(3^n)
            {"2^32 * n",        pow(2.0, 32) * n},        // Linear: O(n) with huge constant factor (2^32)
            {"log2(n)",         log2(n)}                  // Logarithmic: O(log n)
        };
// total number of functions dynamically calculated
        int total = sizeof(funcs) / sizeof(funcs[0]);

     // sort functions in-place by evaluated output value (ascending order)
        sortFunctions(funcs, total);

        for (int i = 0; i < total; i++) {
            printf("%2d. %-18s = %e\n", i + 1, funcs[i].name, funcs[i].value);
        }
        printf("\n");
    }

    return 0;
}
