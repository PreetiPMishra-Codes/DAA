/* ============================================================
   Q4: Sorting a permutation using reverse(p, i, j)
   ============================================================

   PART A. "Any permutation can be sorted using O(n) reversals."
   -----------------------------------------------------------
   Claim : At most 2(n-1) = O(n) calls to reverse() suffice.

   Proof (constructive, by induction - this is exactly "Pancake
   Sort"):
     Base case: n = 1, already sorted, 0 reversals needed.
     Inductive step: Suppose any permutation of size k can be
     sorted with <= 2(k-1) reversals. Given a permutation p of
     size k+1:
       1. Locate the position `idx` of the maximum element
          (value k+1) in p[0..k].                         -- O(n) search
       2. reverse(p, 0, idx)   -> brings the maximum to p[0].
       3. reverse(p, 0, k)     -> brings the maximum from p[0]
                                   to its correct final slot p[k].
       (If idx == k already, skip both reversals - the element
        is already in place.)
     After these <=2 reversals, p[k] = k+1 is permanently fixed
     and never touched again. By the inductive hypothesis the
     remaining prefix p[0..k-1] (a permutation of size k) can be
     sorted with <= 2(k-1) further reversals.
     Total reversals <= 2 + 2(k-1) = 2k = 2((k+1)-1).   QED.

   Hence sorting p of length n costs at most 2(n-1) = O(n)
   reversal OPERATIONS (this bound counts the number of
   reversals, NOT their length/cost).


   PART B. Minimizing total COST = sum of reversal lengths.
   -----------------------------------------------------------
   Pancake sort above uses O(n) reversals but each can be as
   long as n, giving cost O(n^2) in the worst case - too costly.

   We instead use a MERGE-SORT-style divide and conquer:

       reversalMergeSort(p, lo, hi):
           if hi - lo <= 1: return
           mid = (lo+hi)/2
           reversalMergeSort(p, lo, mid)          -- T(n/2)
           reversalMergeSort(p, mid, hi)          -- T(n/2)
           inPlaceMergeByRotation(p, lo, mid, hi) -- merge step

   The merge step merges two sorted halves *in place* using only
   rotations, and each rotation of a block of length L is done
   with exactly 3 reversals (reverse-reverse-reverse trick),
   costing 2L (since each of the 3 reversed sub-ranges is
   scanned once, total <= 2 * L per rotation - see rotate()).

   inPlaceMergeByRotation uses the classical median + binary
   search technique: to merge A=p[lo..mid) and B=p[mid..hi),
   take the median element of the larger half, binary-search
   its insertion point in the other half (O(log n) - no
   reversal cost), rotate just the "crossing" block into place
   (cost O(block length)), then RECURSE independently on the
   two now-disjoint sub-merges. Because the two recursive calls
   partition the n elements with no overlap, and each level's
   rotation costs sum to O(n), and recursion depth is O(log n),
   ONE merge call over n elements costs O(n log n).

   Overall recurrence for reversalMergeSort:
       T(n) = 2 T(n/2) + O(n log n)
   By the Akra-Bazzi / master theorem (case f(n) = Theta(n log n)
   with a = b = 2):
       T(n) = O(n log^2 n).

   This is verified experimentally below by tracking the exact
   total reversal cost and comparing it against n*(log2 n)^2.
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

/* ---------- global counters ---------- */
long long g_reversalCount = 0;
long long g_reversalCost  = 0;

void reverse(int p[], int i, int j) {
    g_reversalCount++;
    g_reversalCost += (j - i + 1);
    while (i < j) { int t = p[i]; p[i] = p[j]; p[j] = t; i++; j--; }
}

/* ===================== PART A: Pancake sort, O(n) reversals ===================== */
void pancakeSort(int p[], int n) {
    for (int size = n; size > 1; size--) {
        int maxIdx = 0;
        for (int i = 1; i < size; i++) if (p[i] > p[maxIdx]) maxIdx = i;
        if (maxIdx == size - 1) continue;
        if (maxIdx != 0) reverse(p, 0, maxIdx);
        reverse(p, 0, size - 1);
    }
}

/* ===================== PART B: O(n log^2 n) cost sort ===================== */

/* rotate p[lo..hi-1] so that block [lo,mid) and [mid,hi) swap places.
   3-reversal trick: cost = (mid-lo) + (hi-mid) + (hi-lo) <= 2*(hi-lo) */
void rotateBlock(int p[], int lo, int mid, int hi) {
    if (lo >= mid || mid >= hi) return;
    reverse(p, lo, mid - 1);
    reverse(p, mid, hi - 1);
    reverse(p, lo, hi - 1);
}

int lowerBound(int p[], int lo, int hi, int val) { /* first idx in [lo,hi) with p[idx] >= val */
    while (lo < hi) { int m = (lo + hi) / 2; if (p[m] < val) lo = m + 1; else hi = m; }
    return lo;
}
int upperBound(int p[], int lo, int hi, int val) { /* first idx in [lo,hi) with p[idx] > val */
    while (lo < hi) { int m = (lo + hi) / 2; if (p[m] <= val) lo = m + 1; else hi = m; }
    return lo;
}

/* merges sorted p[lo..mid) and p[mid..hi) in place, using rotations only */
void inPlaceMergeByRotation(int p[], int lo, int mid, int hi) {
    if (lo >= mid || mid >= hi) return;
    if (p[mid - 1] <= p[mid]) return; /* already merged */

    int len1 = mid - lo, len2 = hi - mid;

    /* Base case: both halves length 1 (only remaining case once
       len1+len2 <= 2, given len1,len2 >= 1 here) - just swap them.
       Without this, splitting a length-1 half produces a degenerate
       empty sub-range and the recursion never shrinks. */
    if (len1 + len2 <= 2) {
        reverse(p, lo, hi - 1);
        return;
    }

    int mid1, mid2;

    if (len1 >= len2) {
        mid1 = lo + len1 / 2;
        int val = p[mid1];
        mid2 = lowerBound(p, mid, hi, val);
    } else {
        mid2 = mid + len2 / 2;
        int val = p[mid2];
        mid1 = upperBound(p, lo, mid, val);
    }

    rotateBlock(p, mid1, mid, mid2);
    int newMid = mid1 + (mid2 - mid);

    inPlaceMergeByRotation(p, lo, mid1, newMid);
    inPlaceMergeByRotation(p, newMid, mid2, hi);
}

void reversalMergeSort(int p[], int lo, int hi) {
    if (hi - lo <= 1) return;
    int mid = (lo + hi) / 2;
    reversalMergeSort(p, lo, mid);
    reversalMergeSort(p, mid, hi);
    inPlaceMergeByRotation(p, lo, mid, hi);
}

/* ---------- helpers ---------- */
int isSorted(int p[], int n) {
    for (int i = 1; i < n; i++) if (p[i - 1] > p[i]) return 0;
    return 1;
}
void printArr(int p[], int n) { for (int i = 0; i < n; i++) printf("%d ", p[i]); printf("\n"); }

int main() {
    int n;
    printf("Enter n (permutation of 1..n): ");
    scanf("%d", &n);
    int *p = malloc(n * sizeof(int));
    printf("Enter the %d permutation values: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &p[i]);

    /* ---- Part A demo ---- */
    int *pa = malloc(n * sizeof(int));
    memcpy(pa, p, n * sizeof(int));
    g_reversalCount = g_reversalCost = 0;
    pancakeSort(pa, n);
    printf("\n[Part A] Pancake sort result: "); printArr(pa, n);
    printf("[Part A] Sorted correctly? %s\n", isSorted(pa, n) ? "Yes" : "No");
    printf("[Part A] #Reversals used = %lld  (bound: O(n) = %d)\n", g_reversalCount, 2 * (n - 1));
    free(pa);

    /* ---- Part B demo ---- */
    int *pb = malloc(n * sizeof(int));
    memcpy(pb, p, n * sizeof(int));
    g_reversalCount = g_reversalCost = 0;
    reversalMergeSort(pb, 0, n);
    printf("\n[Part B] Reversal-merge-sort result: "); printArr(pb, n);
    printf("[Part B] Sorted correctly? %s\n", isSorted(pb, n) ? "Yes" : "No");
    double bound = (n > 1) ? n * pow(log2((double)n), 2) : 1;
    printf("[Part B] #Reversals = %lld, Total reversal COST = %lld  (reference bound n*log2(n)^2 = %.1f)\n",
           g_reversalCount, g_reversalCost, bound);
    free(pb);

    free(p);
    return 0;
}
