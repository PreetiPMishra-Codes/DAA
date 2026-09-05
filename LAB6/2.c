// Q2: 0/1 Knapsack Problem using Dynamic Programming
// Time Complexity: O(n*W)   Space Complexity: O(n*W)
#include <stdio.h>

int max(int a, int b) { return (a > b) ? a : b; }

int knapsack(int W, int wt[], int profit[], int n) {
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(profit[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][W];
}

int main() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);
    int wt[n], profit[n];

    printf("Enter weights: ");
    for (int i = 0; i < n; i++) scanf("%d", &wt[i]);

    printf("Enter profits: ");
    for (int i = 0; i < n; i++) scanf("%d", &profit[i]);

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    printf("Maximum profit = %d\n", knapsack(W, wt, profit, n));

    // Complexity analysis
    printf("\nTime Complexity : O(n * W)\n");
    printf("Space Complexity: O(n * W)\n");
    return 0;
}
