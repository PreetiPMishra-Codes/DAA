
#include <stdio.h>
#define N 100005

int p[N], a[N], idx[N], val[N];

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) p[a] = b;
}

int main() {
    int n, m, u, v, count;

    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        p[i] = i;
        printf("Enter A[%d]: ", i);
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        printf("Enter swappable pair (u v): ");
        scanf("%d%d", &u, &v);
        unite(u, v);
    }

    for (int root = 1; root <= n; root++) {
        if (find(root) != root) continue;

        count = 0;
        for (int j = 1; j <= n; j++) {
            if (find(j) == root) {
                idx[count] = j;
                val[count++] = a[j];
            }
        }

        for (int i = 0; i < count; i++)
            for (int j = i + 1; j < count; j++) {
                if (idx[i] > idx[j]) {
                    int t = idx[i]; idx[i] = idx[j]; idx[j] = t;
                }
                if (val[i] > val[j]) {
                    int t = val[i]; val[i] = val[j]; val[j] = t;
                }
            }

        for (int i = 0; i < count; i++)
            a[idx[i]] = val[i];
    }

    printf("Smallest permutation: ");
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);

    return 0;
}
