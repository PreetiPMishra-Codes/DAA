#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int type; 
} Event;
int cmp(const void *p, const void *q) {
    Event *e1 = (Event *)p;
    Event *e2 = (Event *)q;
    return e1->time - e2->time;}
int main(void) {
    int a[] = {1, 2, 4, 7, 9, 11};
    int b[] = {8, 5, 6, 10, 13, 12};
    int n = sizeof(a) / sizeof(a[0]);
    Event ev[2 * 6];
    int m = 0;
    for (int i = 0; i < n; i++) {
        ev[m].time = a[i]; ev[m].type = 1;  m++; 
        ev[m].time = b[i]; ev[m].type = -1; m++;  }
    qsort(ev, m, sizeof(Event), cmp);
    int count = 0, maxCount = 0, maxTime = -1;
    for (int i = 0; i < m; i++) {
        count += ev[i].type;
        if (count > maxCount) {
            maxCount = count;
            maxTime = ev[i].time; }}
    printf("Max people present at once: %d\n", maxCount);
    printf("This first happens at time : %d\n", maxTime);
    return 0;}
