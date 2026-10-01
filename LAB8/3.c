/* Q3 LCS + reconstruction. Input: X Y (strings). Time O(mn), Space O(mn) */
#include <stdio.h>
#include <string.h>
#define MX(a,b) ((a)>(b)?(a):(b))
int main(void) {
    static char X[1001], Y[1001]; scanf("%1000s %1000s", X, Y);
    int m = strlen(X), n = strlen(Y), L[m + 1][n + 1];
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++)
            L[i][j] = !i || !j ? 0 : X[i-1] == Y[j-1] ? L[i-1][j-1] + 1 : MX(L[i-1][j], L[i][j-1]);
    int k = L[m][n]; char s[k + 1]; s[k] = 0;
    for (int i = m, j = n; i && j;)
        if (X[i-1] == Y[j-1]) s[--k] = X[--i], j--;
        else if (L[i-1][j] >= L[i][j-1]) i--; else j--;
    printf("%d %s\n", L[m][n], s);
    return 0;
}
