#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}
typedef struct { int *data; int n, cap; } UArray;

UArray uarr_create(int cap) { UArray a; a.data = malloc(sizeof(int) * cap); a.n = 0; a.cap = cap; return a; }
void uarr_insert(UArray *a, int x) { a->data[a->n++] = x; }             
int  uarr_search(UArray *a, int k) {                                      
    for (int i = 0; i < a->n; i++) if (a->data[i] == k) return i;
    return -1;
}
void uarr_delete(UArray *a, int idx) {                                     
    for (int i = idx; i < a->n - 1; i++) a->data[i] = a->data[i + 1];
    a->n--;
}
int uarr_max(UArray *a) { int m = a->data[0]; for (int i = 1; i < a->n; i++) if (a->data[i] > m) m = a->data[i]; return m; }
int uarr_min(UArray *a) { int m = a->data[0]; for (int i = 1; i < a->n; i++) if (a->data[i] < m) m = a->data[i]; return m; }
int uarr_predecessor(UArray *a, int x) {                                 
    int best = -2147483647, found = 0;
    for (int i = 0; i < a->n; i++) if (a->data[i] < x && a->data[i] > best) { best = a->data[i]; found = 1; }
    return found ? best : -1;
}
int uarr_successor(UArray *a, int x) {                                 
    int best = 2147483647, found = 0;
    for (int i = 0; i < a->n; i++) if (a->data[i] > x && a->data[i] < best) { best = a->data[i]; found = 1; }
    return found ? best : -1;
}
typedef struct { int *data; int n, cap; } SArray;

SArray sarr_create(int cap) { SArray a; a.data = malloc(sizeof(int) * cap); a.n = 0; a.cap = cap; return a; }

int sarr_lower_bound(SArray *a, int x) {  
    int lo = 0, hi = a->n;
    while (lo < hi) { int mid = (lo + hi) / 2; if (a->data[mid] < x) lo = mid + 1; else hi = mid; }
    return lo;
}
void sarr_insert(SArray *a, int x) {         
    int pos = sarr_lower_bound(a, x);
    for (int i = a->n; i > pos; i--) a->data[i] = a->data[i - 1];
    a->data[pos] = x; a->n++;
}
int sarr_search(SArray *a, int k) {           
    int pos = sarr_lower_bound(a, k);
    if (pos < a->n && a->data[pos] == k) return pos;
    return -1;
}
void sarr_delete(SArray *a, int idx) {             
    for (int i = idx; i < a->n - 1; i++) a->data[i] = a->data[i + 1];
    a->n--;
}
int sarr_max(SArray *a) { return a->data[a->n - 1]; }  
int sarr_min(SArray *a) { return a->data[0]; }          
int sarr_predecessor(SArray *a, int x) {                
    int pos = sarr_lower_bound(a, x);
    return (pos - 1 >= 0) ? a->data[pos - 1] : -1;
}
int sarr_successor(SArray *a, int x) {                  /
    int pos = sarr_lower_bound(a, x);
    if (pos < a->n && a->data[pos] == x) pos++;
    return (pos < a->n) ? a->data[pos] : -1;
}

typedef struct SNode { int key; struct SNode *next; } SNode;
typedef struct { SNode *head; } SList;

SList slist_create(void) { SList l; l.head = NULL; return l; }
void slist_insert(SList *l, int x) {                     
    SNode *node = malloc(sizeof(SNode));
    node->key = x; node->next = l->head; l->head = node;
}
SNode* slist_search(SList *l, int k) {                   
    SNode *cur = l->head;
    while (cur) { if (cur->key == k) return cur; cur = cur->next; }
    return NULL;
}
void slist_delete(SList *l, int k) {                     
    SNode *cur = l->head, *prev = NULL;
    while (cur) {
        if (cur->key == k) {
            if (prev) prev->next = cur->next; else l->head = cur->next;
            free(cur); return;
        }
        prev = cur; cur = cur->next;
    }
}
int slist_max(SList *l) { int m = l->head->key; for (SNode *c = l->head; c; c = c->next) if (c->key > m) m = c->key; return m; }
int slist_min(SList *l) { int m = l->head->key; for (SNode *c = l->head; c; c = c->next) if (c->key < m) m = c->key; return m; } 
int slist_predecessor(SList *l, int x) {                  /* O(n) */
    int best = -2147483647, found = 0;
    for (SNode *c = l->head; c; c = c->next) if (c->key < x && c->key > best) { best = c->key; found = 1; }
    return found ? best : -1;
}
int slist_successor(SList *l, int x) {                    /* O(n) */
    int best = 2147483647, found = 0;
    for (SNode *c = l->head; c; c = c->next) if (c->key > x && c->key < best) { best = c->key; found = 1; }
    return found ? best : -1;
}
typedef SList SSortedList;

void sslist_insert(SSortedList *l, int x) {                /* O(n) - walk until we find where x belongs */
    SNode *node = malloc(sizeof(SNode)); node->key = x;
    if (!l->head || l->head->key >= x) { node->next = l->head; l->head = node; return; }
    SNode *cur = l->head;
    while (cur->next && cur->next->key < x) cur = cur->next;
    node->next = cur->next; cur->next = node;
}
SNode* sslist_search(SSortedList *l, int k) {                /* O(n) worst case (can stop early on average, but worst case still n) */
    SNode *cur = l->head;
    while (cur && cur->key < k) cur = cur->next;
    if (cur && cur->key == k) return cur;
    return NULL;
}
void sslist_delete(SSortedList *l, int k) {                  /* O(n) - need previous node, must walk */
    SNode *cur = l->head, *prev = NULL;
    while (cur && cur->key < k) { prev = cur; cur = cur->next; }
    if (cur && cur->key == k) {
        if (prev) prev->next = cur->next; else l->head = cur->next;
        free(cur);
    }
}
int sslist_max(SSortedList *l) {                              /* O(n) - no tail pointer kept, so we walk to the end */
    SNode *cur = l->head; while (cur->next) cur = cur->next; return cur->key;
}
int sslist_min(SSortedList *l) { return l->head->key; }        /* O(1) - it's right at the head */
int sslist_predecessor(SSortedList *l, int x) {                 /* O(n) */
    SNode *cur = l->head, *prev = NULL;
    while (cur && cur->key < x) { prev = cur; cur = cur->next; }
    return prev ? prev->key : -1;
}
int sslist_successor(SSortedList *l, int x) {                   /* O(n) */
    SNode *cur = l->head;
    while (cur && cur->key <= x) cur = cur->next;
    return cur ? cur->key : -1;
}

typedef struct DNode { int key; struct DNode *prev, *next; } DNode;
typedef struct { DNode *head, *tail; } DList;

DList dlist_create(void) { DList l; l.head = l.tail = NULL; return l; }
void dlist_insert(DList *l, int x) {                          /* O(1) */
    DNode *node = malloc(sizeof(DNode)); node->key = x; node->prev = NULL; node->next = l->head;
    if (l->head) l->head->prev = node; else l->tail = node;
    l->head = node;
}
DNode* dlist_search(DList *l, int k) {                          /* O(n) */
    DNode *cur = l->head;
    while (cur) { if (cur->key == k) return cur; cur = cur->next; }
    return NULL;
}
void dlist_delete_node(DList *l, DNode *node) {                  /* O(1) - this is the whole point of a doubly linked list! */
    if (node->prev) node->prev->next = node->next; else l->head = node->next;
    if (node->next) node->next->prev = node->prev; else l->tail = node->prev;
    free(node);
}
int dlist_max(DList *l) { int m = l->head->key; for (DNode *c = l->head; c; c = c->next) if (c->key > m) m = c->key; return m; } /* O(n) */
int dlist_min(DList *l) { int m = l->head->key; for (DNode *c = l->head; c; c = c->next) if (c->key < m) m = c->key; return m; } /* O(n) */
int dlist_predecessor(DList *l, int x) {                          /* O(n) - still unsorted, must scan */
    int best = -2147483647, found = 0;
    for (DNode *c = l->head; c; c = c->next) if (c->key < x && c->key > best) { best = c->key; found = 1; }
    return found ? best : -1;
}
int dlist_successor(DList *l, int x) {                             /* O(n) */
    int best = 2147483647, found = 0;
    for (DNode *c = l->head; c; c = c->next) if (c->key > x && c->key < best) { best = c->key; found = 1; }
    return found ? best : -1;
}
typedef DList DSortedList;

void dslist_insert(DSortedList *l, int x) {                        /* O(n) - walk to find the spot */
    DNode *node = malloc(sizeof(DNode)); node->key = x;
    if (!l->head || l->head->key >= x) {
        node->prev = NULL; node->next = l->head;
        if (l->head) l->head->prev = node; else l->tail = node;
        l->head = node; return;
    }
    DNode *cur = l->head;
    while (cur->next && cur->next->key < x) cur = cur->next;
    node->next = cur->next; node->prev = cur;
    if (cur->next) cur->next->prev = node; else l->tail = node;
    cur->next = node;
}
DNode* dslist_search(DSortedList *l, int k) {                        /* O(n) worst case */
    DNode *cur = l->head;
    while (cur && cur->key < k) cur = cur->next;
    if (cur && cur->key == k) return cur;
    return NULL;
}
int dslist_max(DSortedList *l) { return l->tail->key; }              /* O(1) - tail pointer kept up to date */
int dslist_min(DSortedList *l) { return l->head->key; }              /* O(1) */
int dslist_predecessor_node(DNode *node) { return node->prev ? node->prev->key : -1; } /* O(1) */
int dslist_successor_node(DNode *node)   { return node->next ? node->next->key : -1; } /* O(1) */
void run_benchmarks(const char *csv_path) {
    FILE *out = fopen(csv_path, "w");
    if (!out) { perror("fopen results.csv"); exit(1); }

    srand(42);
    int sizes[] = {500, 1000, 2000, 4000, 8000, 16000, 32000, 64000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    fprintf(out, "structure,operation,n,time_sec\n");

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int *keys = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) keys[i] = i * 2;      /* distinct even keys */
        for (int i = n - 1; i > 0; i--) {                 /* shuffle -> random insertion order */
            int j = rand() % (i + 1);
            int tmp = keys[i]; keys[i] = keys[j]; keys[j] = tmp;
        }
        int search_key = keys[n / 2];
        int missing_key = -1;                             /* forces full scan worst case */

        double t0, t1;
        {
            UArray a = uarr_create(n);
            t0 = now_sec(); for (int i = 0; i < n; i++) uarr_insert(&a, keys[i]); t1 = now_sec();
            fprintf(out, "UnsortedArray,Insert,%d,%.9f\n", n, (t1 - t0) / n);
            t0 = now_sec(); uarr_search(&a, missing_key); t1 = now_sec();
            fprintf(out, "UnsortedArray,Search,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); uarr_max(&a); t1 = now_sec();
            fprintf(out, "UnsortedArray,Max,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); uarr_min(&a); t1 = now_sec();
            fprintf(out, "UnsortedArray,Min,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); uarr_predecessor(&a, search_key); t1 = now_sec();
            fprintf(out, "UnsortedArray,Predecessor,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); uarr_successor(&a, search_key); t1 = now_sec();
            fprintf(out, "UnsortedArray,Successor,%d,%.9f\n", n, t1 - t0);
            int idx = uarr_search(&a, keys[0]);
            t0 = now_sec(); uarr_delete(&a, idx); t1 = now_sec();
            fprintf(out, "UnsortedArray,Delete,%d,%.9f\n", n, t1 - t0);
            free(a.data);
        }
        {
            SArray a = sarr_create(n);
            t0 = now_sec(); for (int i = 0; i < n; i++) sarr_insert(&a, keys[i]); t1 = now_sec();
            fprintf(out, "SortedArray,Insert,%d,%.9f\n", n, (t1 - t0) / n);
            t0 = now_sec(); sarr_search(&a, missing_key); t1 = now_sec();
            fprintf(out, "SortedArray,Search,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); sarr_max(&a); t1 = now_sec();
            fprintf(out, "SortedArray,Max,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); sarr_min(&a); t1 = now_sec();
            fprintf(out, "SortedArray,Min,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); sarr_predecessor(&a, search_key); t1 = now_sec();
            fprintf(out, "SortedArray,Predecessor,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); sarr_successor(&a, search_key); t1 = now_sec();
            fprintf(out, "SortedArray,Successor,%d,%.9f\n", n, t1 - t0);
            int idx = sarr_search(&a, a.data[0]);
            t0 = now_sec(); sarr_delete(&a, idx); t1 = now_sec();
            fprintf(out, "SortedArray,Delete,%d,%.9f\n", n, t1 - t0);
            free(a.data);
        }
        {
            SList l = slist_create();
            t0 = now_sec(); for (int i = 0; i < n; i++) slist_insert(&l, keys[i]); t1 = now_sec();
            fprintf(out, "SinglyLinkedUnsorted,Insert,%d,%.9f\n", n, (t1 - t0) / n);
            t0 = now_sec(); slist_search(&l, missing_key); t1 = now_sec();
            fprintf(out, "SinglyLinkedUnsorted,Search,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); slist_max(&l); t1 = now_sec();
            fprintf(out, "SinglyLinkedUnsorted,Max,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); slist_min(&l); t1 = now_sec();
            fprintf(out, "SinglyLinkedUnsorted,Min,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); slist_predecessor(&l, search_key); t1 = now_sec();
            fprintf(out, "SinglyLinkedUnsorted,Predecessor,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); slist_successor(&l, search_key); t1 = now_sec();
            fprintf(out, "SinglyLinkedUnsorted,Successor,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); slist_delete(&l, keys[0]); t1 = now_sec();
            fprintf(out, "SinglyLinkedUnsorted,Delete,%d,%.9f\n", n, t1 - t0);
            SNode *cur = l.head; while (cur) { SNode *nx = cur->next; free(cur); cur = nx; }
        }
        {
            SSortedList l = slist_create();
            t0 = now_sec(); for (int i = 0; i < n; i++) sslist_insert(&l, keys[i]); t1 = now_sec();
            fprintf(out, "SinglyLinkedSorted,Insert,%d,%.9f\n", n, (t1 - t0) / n);
            t0 = now_sec(); sslist_search(&l, missing_key); t1 = now_sec();
            fprintf(out, "SinglyLinkedSorted,Search,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); sslist_max(&l); t1 = now_sec();
            fprintf(out, "SinglyLinkedSorted,Max,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); sslist_min(&l); t1 = now_sec();
            fprintf(out, "SinglyLinkedSorted,Min,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); sslist_predecessor(&l, search_key); t1 = now_sec();
            fprintf(out, "SinglyLinkedSorted,Predecessor,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); sslist_successor(&l, search_key); t1 = now_sec();
            fprintf(out, "SinglyLinkedSorted,Successor,%d,%.9f\n", n, t1 - t0);
            int last_key = (n - 1) * 2;
            t0 = now_sec(); sslist_delete(&l, last_key); t1 = now_sec();
            fprintf(out, "SinglyLinkedSorted,Delete,%d,%.9f\n", n, t1 - t0);
            SNode *cur = l.head; while (cur) { SNode *nx = cur->next; free(cur); cur = nx; }
        }
        {
            DList l = dlist_create();
            t0 = now_sec(); for (int i = 0; i < n; i++) dlist_insert(&l, keys[i]); t1 = now_sec();
            fprintf(out, "DoublyLinkedUnsorted,Insert,%d,%.9f\n", n, (t1 - t0) / n);
            t0 = now_sec(); DNode *found = dlist_search(&l, missing_key); t1 = now_sec();
            fprintf(out, "DoublyLinkedUnsorted,Search,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); dlist_max(&l); t1 = now_sec();
            fprintf(out, "DoublyLinkedUnsorted,Max,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); dlist_min(&l); t1 = now_sec();
            fprintf(out, "DoublyLinkedUnsorted,Min,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); dlist_predecessor(&l, search_key); t1 = now_sec();
            fprintf(out, "DoublyLinkedUnsorted,Predecessor,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); dlist_successor(&l, search_key); t1 = now_sec();
            fprintf(out, "DoublyLinkedUnsorted,Successor,%d,%.9f\n", n, t1 - t0);
            found = dlist_search(&l, keys[0]);
            t0 = now_sec(); dlist_delete_node(&l, found); t1 = now_sec();
            fprintf(out, "DoublyLinkedUnsorted,Delete,%d,%.9f\n", n, t1 - t0);
            DNode *cur = l.head; while (cur) { DNode *nx = cur->next; free(cur); cur = nx; }
        }
        {
            DSortedList l = dlist_create();
            t0 = now_sec(); for (int i = 0; i < n; i++) dslist_insert(&l, keys[i]); t1 = now_sec();
            fprintf(out, "DoublyLinkedSorted,Insert,%d,%.9f\n", n, (t1 - t0) / n);
            t0 = now_sec(); DNode *found = dslist_search(&l, missing_key); t1 = now_sec();
            fprintf(out, "DoublyLinkedSorted,Search,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); dslist_max(&l); t1 = now_sec();
            fprintf(out, "DoublyLinkedSorted,Max,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); dslist_min(&l); t1 = now_sec();
            fprintf(out, "DoublyLinkedSorted,Min,%d,%.9f\n", n, t1 - t0);
            found = dslist_search(&l, search_key);
            t0 = now_sec(); dslist_predecessor_node(found); t1 = now_sec();
            fprintf(out, "DoublyLinkedSorted,Predecessor,%d,%.9f\n", n, t1 - t0);
            t0 = now_sec(); dslist_successor_node(found); t1 = now_sec();
            fprintf(out, "DoublyLinkedSorted,Successor,%d,%.9f\n", n, t1 - t0);
            found = dslist_search(&l, keys[0]);
            t0 = now_sec(); dlist_delete_node(&l, found); t1 = now_sec();
            fprintf(out, "DoublyLinkedSorted,Delete,%d,%.9f\n", n, t1 - t0);
            DNode *cur = l.head; while (cur) { DNode *nx = cur->next; free(cur); cur = nx; }
        }

        free(keys);
    }

    fclose(out);
}
int main(void) {
    printf("Running benchmarks for all 6 structures x 7 operations...\n");
    run_benchmarks("results.csv");
    printf("Done. Timings saved to results.csv\n");
    printf("Now run the SDL grapher (dict_graph_sdl.c) on this results.csv to see the plots.\n");
    return 0;
}
