// Q4: Matrix Chain Multiplication using Dynamic Programming
// Time Complexity: O(N^3)   Space Complexity: O(N^2)
#include <stdio.h>
#include <limits.h>

int min(int a, int b) { return (a < b) ? a : b; }

int matrixChainOrder(int arr[], int N) {
    // N-1 matrices -> dp indexed 1..N-1
    int dp[N][N];

    for (int i = 1; i < N; i++)
        dp[i][i] = 0;

    for (int len = 2; len < N; len++) {
        for (int i = 1; i < N - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[1][N - 1];
}

int main() {
    int N;
    printf("Enter N (number of dimensions, matrices = N-1): ");
    scanf("%d", &N);

    int arr[N];
    printf("Enter %d dimensions: ", N);
    for (int i = 0; i < N; i++) scanf("%d", &arr[i]);

    printf("Minimum number of multiplications = %d\n", matrixChainOrder(arr, N));

    printf("\nTime Complexity : O(N^3)\n");
    printf("Space Complexity: O(N^2)\n");
    return 0;
}

/*
Sample:
Input:  N = 4
        arr[] = {10, 30, 5, 60}
Output: 4500
Time Complexity: O(N^3)
*/
