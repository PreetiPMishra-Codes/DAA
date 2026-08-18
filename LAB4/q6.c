#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int point;
    int type;
} Event;
int cmp(const void *p, const void *q) {
    Event *e1 = (Event *)p;
    Event *e2 = (Event *)q;
    if (e1->point != e2->point) return e1->point - e2->point;
    return e1->type - e2->type;   }
int main(void) {
    int l[] = {10, 20, 50, 15};
    int r[] = {40, 60, 90, 70};
    int n = sizeof(l) / sizeof(l[0]);
    Event ev[2 * 4];
    int m = 0;
    for (int i = 0; i < n; i++) {
        ev[m].point = l[i]; ev[m].type = 0; m++;
        ev[m].point = r[i]; ev[m].type = 1; m++;}
    qsort(ev, m, sizeof(Event), cmp);
    int count = 0, maxCount = 0, bestPoint = -1;
    for (int i = 0; i < m; i++) {
        if (ev[i].type == 0) {
            count++;
            if (count >= maxCount) {
                maxCount = count;
                bestPoint = ev[i].point;}
        } else {
            count--;}}
    printf("Point with max coverage: %d\n", bestPoint);
    printf("Number of intervals covering it: %d\n", maxCount);
    return 0;
}
