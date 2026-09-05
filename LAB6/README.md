# DAA Lab-6 — C Solutions

This repo contains C solutions for two related Lab-6 assignments on
**Dynamic Programming** and **Algorithm Design (arrays, matrices,
divide & conquer, greedy reversal sorting)**.

All programs are single-file, self-contained, and compile with plain `gcc`.

```bash
gcc -o <name> <name>.c -lm      # -lm needed only where math.h is used
./<name>
```

---

## Part 1 — Dynamic Programming

| File | Problem | Time | Space |
|---|---|---|---|
| `1.c` | nth Fibonacci number | O(n) | O(n) |
| `2.c` | 0/1 Knapsack (max profit for capacity `W`) | O(n·W) | O(n·W) |
| `3.c` | Longest Common Subsequence (length + the subsequence itself) | O(m·n) | O(m·n) |
| `4.c` | Matrix Chain Multiplication (min scalar multiplications) | O(N³) | O(N²) |

### How to run

**1. Fibonacci**
```bash
gcc -o fib 1_fibonacci.c
echo 10 | ./fib          # Fibonacci(10) = 55
```

**2. 0/1 Knapsack**
```
Input : number of items n, weight[], profit[], capacity W
Output: maximum achievable profit, plus time/space complexity note
```
```bash
gcc -o knap 2_knapsack.c
printf "3\n1 3 4\n15 20 30\n4\n" | ./knap    # Maximum profit = 35
```

**3. Longest Common Subsequence**
```
Input : two strings X, Y
Output: length of LCS and the actual LCS string
```
```bash
gcc -o lcs 3_lcs.c
printf "ABCBDAB\nBDCABA\n" | ./lcs           # Length = 4, LCS = BDAB
```

**4. Matrix Chain Multiplication**
```
Input : N (dimension count), array of N dimensions
Output: minimum scalar multiplications to multiply the full chain
```
```bash
gcc -o mcm 4_matrix_chain.c
printf "4\n10 30 5 60\n" | ./mcm             # Minimum multiplications = 4500
```

---

## Part 2 — Arrays, Matrices, Divide & Conquer, Reversal Sorting

| File | Problem | Key complexity result |
|---|---|---|
| `5.c` | 9 classic 1D array operations | see table below |
| `6.c` | 7 classic n×n matrix operations | see table below |
| `7.c` | Vector convolution via D&C FFT | **O(n log n)** |
| `8.c` | Sort a permutation using only `reverse(p,i,j)` | O(n) reversal **count**, then O(n log²n) reversal **cost** |

### 5. Array operations — `5.c`

Given an unsorted `int` array of size `n`:

| Operation | Worst-case | How |
|---|---|---|
| Maximum element | O(n) | single linear scan |
| First & second largest | O(n) | single linear scan, tracked together |
| Mean | O(n) | running sum |
| Median | O(n log n) | sort, then take middle |
| Standard deviation | O(n) | needs mean first, then one more pass |
| Mode | O(n log n) | sort, then longest run of equal values |
| Remove all duplicates | O(n log n) | sort, then compact adjacent equals |
| Reverse the array | O(n) | two-pointer swap |
| Partition around a pivot (elements **< pivot pushed to the end**, `>= pivot` kept at the front) | O(n) | single Lomuto-style pass |

```bash
gcc -o arr 1_array_ops.c -lm
printf "8\n5 3 9 3 7 1 9 2\n5\n" | ./arr
```
Prompts for `n`, the `n` elements, then a pivot value at the end (for the partition demo). Prints the result and Big-O of every operation.

### 6. Matrix operations — `6.c`

Given two n×n matrices `A`, `B` (as `double`):

| Operation | Worst-case | How |
|---|---|---|
| Addition | O(n²) | elementwise |
| Multiplication | O(n³) | naive triple loop |
| Zero-matrix check | O(n²) | scan all entries |
| Symmetric check | O(n²) | compare upper/lower triangles |
| Determinant | O(n³) | Gaussian elimination with partial pivoting (naive cofactor expansion would be O(n!)) |
| Transpose in place | O(n²) | swap upper/lower triangle entries |
| Dominant eigenvalue / eigenvector | O(k·n²) for `k` iterations | Power Iteration (Rayleigh-quotient estimate). Note: for n > 4 there is no closed-form solution for eigenvalues (Abel–Ruffini theorem), so numerical iteration is unavoidable in general |

```bash
gcc -o mat 2_matrix_ops.c -lm
printf "3\n2 0 0\n0 2 0\n0 0 2\n1 2 3\n4 5 6\n7 8 9\n" | ./mat
```
Prompts for `n`, matrix `A`, matrix `B`; prints every result with its complexity tag.

### 7. Convolution — `7.c`

Computes `C[k] = Σ A[j]·B[k−j]` for vectors `A` (length `m`) and `B`
(length `n ≥ m`) in **O(n log n)** using a divide-and-conquer radix-2
Cooley–Tukey FFT:

* Zero-pad both vectors to the next power of two, `N ≥ m+n−1`.
* Recursively split each vector into even/odd-indexed halves,
  recurse on both (`T(N) = 2T(N/2) + O(N)` ⇒ `O(N log N)`).
* Multiply the two transforms pointwise, O(N).
* Inverse-FFT back, O(N log N).

```bash
gcc -o conv 3_convolution_fft.c -lm
printf "3\n1 2 3\n4\n4 5 6 7\n" | ./conv
# Convolution C (length 6): 4.00 13.00 28.00 34.00 32.00 21.00
```
Verified against `numpy.convolve` — exact match.

### 8. Sorting via reversal — `8.c`

Given a permutation `p` of `1..n`, the only allowed operation is
`reverse(p, i, j)`.

**Part A — O(n) reversals suffice.**
This is Pancake Sort: repeatedly find the maximum of the unsorted
prefix, reverse it to the front, then reverse it to its final slot —
2 reversals per element, `≤ 2(n−1) = O(n)` reversals total. Proved by
induction in the file's header comment.

**Part B — O(n log²n) total reversal *cost*** (cost = Σ reversal
lengths, not just the count).
Uses a merge-sort where the merge step is done **in place** via
rotations (each rotation = 3 reversals). The merge locates the
median of the larger half, binary-searches its insertion point in
the other half (no reversal cost — pure comparison), rotates only
the crossing block into place, then recurses independently on the
two now-disjoint pieces. One such merge over `n` elements costs
`O(n log n)`; with the outer merge-sort recursion,
`T(n) = 2T(n/2) + O(n log n) = O(n log²n)`.

```bash
gcc -o rev 4_reversal_sort.c -lm
printf "10\n5 3 9 1 7 2 10 4 8 6\n" | ./rev
```
Prints, for both methods: the sorted result, a correctness check,
the reversal count (Part A) and total reversal cost (Part B) versus
the `n·log₂(n)²` reference bound. Verified correct and within bound
for random permutations up to `n = 20,000`.

> **Note on a fixed bug:** the first version of the Part B merge had
> a degenerate case — when both sub-halves shrank to length 1, the
> median-split logic produced an empty rotation range and the
> recursion never shrank, causing infinite recursion (stack
> overflow). Caught with AddressSanitizer and fixed by adding an
> explicit length-≤2 base case that swaps the pair directly via a
> single `reverse()` call.

---

## Compiling everything at once

```bash
for f in *.c; do gcc -o "${f%.c}" "$f" -lm -Wall; done
```

All eight programs compile warning-free under `gcc -Wall` and have
been tested against hand-computed and reference (NumPy) outputs.
