/* Q6 Edit distance + traceback. Input: A B (strings). Time O(mn), Space O(mn) */
#include <stdio.h>
#include <string.h>
#define MN(a,b) ((a)<(b)?(a):(b))
int main(void) {
    static char A[1001], B[1001]; scanf("%1000s %1000s", A, B);
    int m = strlen(A), n = strlen(B), D[m + 1][n + 1], c = 0, P[m + n][2]; char op[m + n];
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++)
            D[i][j] = !i ? j : !j ? i : A[i-1] == B[j-1] ? D[i-1][j-1]
                    : 1 + MN(D[i-1][j-1], MN(D[i-1][j], D[i][j-1]));
    for (int i = m, j = n; i || j; c++) {
        P[c][0] = i; P[c][1] = j;
        if (i && j && A[i-1] == B[j-1]) op[c] = 'M', i--, j--;
        else if (i && j && D[i][j] == D[i-1][j-1] + 1) op[c] = 'R', i--, j--;
        else if (i && D[i][j] == D[i-1][j] + 1) op[c] = 'D', i--;
        else op[c] = 'I', j--;
    }
    printf("Distance = %d\n", D[m][n]);
    while (c--) {
        int i = P[c][0], j = P[c][1];
        if (op[c] == 'M') printf("match   %c\n", A[i-1]);
        else if (op[c] == 'R') printf("replace %c -> %c\n", A[i-1], B[j-1]);
        else if (op[c] == 'D') printf("delete  %c\n", A[i-1]);
        else printf("insert  %c\n", B[j-1]);
    }
    return 0;
}
