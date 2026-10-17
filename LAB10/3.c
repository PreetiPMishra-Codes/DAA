
#include <stdio.h>
#define N 100005

int p[N], sz[N];
long long w[N], sum[N];

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;

    if (sz[a] < sz[b]) {
        int t = a; a = b; b = t;
    }
    p[b] = a;
    sz[a] += sz[b];
    sum[a] += sum[b];
}

int main() {
    int n, m, K, u, v;
    scanf("%d%d%d", &n, &m, &K);

    for (int i = 1; i <= n; i++) {
        printf("Enter weight of vertex %d: ", i);
        scanf("%lld", &w[i]);
        p[i] = i;
        sz[i] = 1;
        sum[i] = w[i];
    }

    for (int i = 0; i < m; i++) {
        printf("Enter edge (u v): ");
        scanf("%d%d", &u, &v);
        unite(u, v);

        long long best = 0;
        int found = 0;

        for (int j = 1; j <= n; j++) {
            if (find(j) == j && sz[j] <= K) {
                if (!found || sum[j] > best)
                    best = sum[j];
                found = 1;
            }
        }

        if (found) printf("Maximum weight: %lld\n", best);
        else printf("No eligible component\n");
    }
    return 0;
}
