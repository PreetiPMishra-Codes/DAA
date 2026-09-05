// Q3: Longest Common Subsequence (LCS) using Dynamic Programming
// Time Complexity: O(m*n)   Space Complexity: O(m*n)
#include <stdio.h>
#include <string.h>

int max(int a, int b) { return (a > b) ? a : b; }

void lcs(char *X, char *Y) {
    int m = strlen(X), n = strlen(Y);
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    int len = dp[m][n];
    char result[len + 1];
    result[len] = '\0';

    int i = m, j = n, idx = len - 1;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            result[idx--] = X[i - 1];
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("Length of LCS = %d\n", len);
    printf("LCS = %s\n", result);
    printf("\nTime Complexity : O(m * n)\n");
    printf("Space Complexity: O(m * n)\n");
}

int main() {
    char X[100], Y[100];
    printf("Enter first string: ");
    scanf("%s", X);
    printf("Enter second string: ");
    scanf("%s", Y);

    lcs(X, Y);
    return 0;
}
