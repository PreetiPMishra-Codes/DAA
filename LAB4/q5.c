#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Interval;

int cmp(const void *p, const void *q) {
    Interval *a = (Interval *)p;
    Interval *b = (Interval *)q;
    return a->x - b->x;}
int mergeIntervals(Interval in[], int n, Interval out[]) {
    qsort(in, n, sizeof(Interval), cmp);
    int m = 0;
    int curX = in[0].x, curY = in[0].y;
    for (int i = 1; i < n; i++) {
        if (in[i].x <= curY) {
            if (in[i].y > curY) curY = in[i].y;
        } else {
            out[m].x = curX;
            out[m].y = curY;
            m++;
            curX = in[i].x;
            curY = in[i].y;}}
    out[m].x = curX;
    out[m].y = curY;
    m++;
    return m;}
int main(void) {
    Interval in[] = { {1, 3}, {2, 6}, {8, 10}, {7, 18} };
    int n = sizeof(in) / sizeof(in[0]);
    Interval out[100];
    int m = mergeIntervals(in, n, out);
    printf("Merged intervals: ");
    for (int i = 0; i < m; i++)
        printf("(%d,%d) ", out[i].x, out[i].y);
    printf("\n");
    return 0;
}
