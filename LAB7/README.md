# DAA Lab-07

Files: `1.c` through `7.c`, one per question.
---

## 1.c — Invert the coin-triangle

**Problem:** Coins packed in a triangle (n rows, n(n+1)/2 coins). Flip it upside down by sliding one coin at a time, in the minimum number of moves.

**Approach:** Overlay the upward triangle on the target downward triangle so the overlap is maximized. Coins in the overlap don't need to move; only the "leftover" coins do.

**Formula:** `M(n) = floor(n(n+1)/6)` — i.e. total coins divided by 3, remainder dropped.
(4 rows / 10 coins → 3 moves, matching the classic version of this puzzle.)

**Complexity:** O(1) for the formula; O(n) to generate an example move list.

---

## 2.c — Super egg testing experiment

**Problem:** With E eggs and F floors, find the minimum number of drops that guarantees finding the highest "safe" floor, in the worst case.

**Approach:** DP over `dp[e][f]` = min drops needed for e eggs, f floors.
```
dp[e][f] = 1 + min over x of max( dp[e-1][x-1], dp[e][f-x] )
```
(if the egg breaks at floor x → e-1 eggs, x-1 floors left; if it survives → e eggs, f-x floors left; take the worse case, then pick the best x.)

**Result:** E=2, F=100 → 14 drops (also checked against the closed form: smallest t with t(t+1)/2 ≥ F).

**Complexity:** O(E·F²) time, O(E·F) space.

---

## 3.c — Reve's puzzle (4-peg Tower of Hanoi)

**Problem:** Move n disks across 4 pegs (instead of the usual 3), minimum moves. For n=8, expect 33.

**Approach:** Frame–Stewart algorithm.
```
FS(n) = min over k of  2*FS(k) + 2^(n-k) - 1
```
Move top k disks to a spare peg (recursively, all 4 pegs), move remaining n-k disks with normal 3-peg Hanoi, then move the k disks back (recursively).

**Result:** n=8 → 33 moves (optimal split k=4), sequence verified legal (no larger disk ever placed on a smaller one).

**Complexity:** O(n²) to compute the optimal split for all sizes; O(FS(n)) to generate the moves.

---

## 4.c — Security switches

**Problem:** n switches, all ON. A switch can only be toggled if very specific right-side conditions hold. Turn all switches OFF in minimum moves.

**Approach:** This is the classical Chinese Rings (Baguenaudier) puzzle in disguise. Every configuration has at most 2 legal moves, so the graph of legal moves over all 2^n states is just a simple path. BFS from all-ON to all-OFF along this path gives the guaranteed-correct, guaranteed-legal shortest solution.

**Result:** matches OEIS A000975: 1, 2, 5, 10, 21, 42, 85, ... for n = 1..7.

**Complexity:** O(2^n · n) time, O(2^n) space — exponential, but that's inherent to the puzzle itself.

---

## 5.c — Hitting a moving target

**Problem:** A target hides among n spots and moves to an adjacent spot after every shot. You can't see it. Does a sequence of shots exist that's guaranteed to hit it eventually?

**Approach:** Yes. Since the target's position parity flips every move, sweep the interior spots once forward and once backward:
```
shoot 2, 3, ..., n-1, then n-1, n-2, ..., 2
```
This covers both possible parity classes of the target's unknown starting position.

**Validation:** Brute-force simulation tracks the full set of positions the target could still occupy (given adversarial movement) for every possible start, and confirms this set always empties out.

**Complexity:** O(n) to build the shot sequence; O(n²) for the validation.

---

## 6.c — The best time to be alive

**Problem:** Given (birth, death) years of n scientists, find the year(s) when the most were alive at once. Tie-break: if A dies the same year B is born, A is considered dead before B is born (they don't overlap).

**Approach:** Classic sweep-line / max-overlapping-intervals. Sort births and deaths separately; scan through them in order, incrementing on a birth and decrementing on a death, processing same-year deaths before same-year births (this directly encodes the tie-break rule).

**Complexity:** O(n log n) (sorting dominates), O(n) space.

---

## 7.c — Matrix Chain Multiplication (MCM)

**Problem:** Given a chain of matrices, find the parenthesization (order of multiplication) that minimizes the total scalar multiplications.

**Approach:** Standard interval DP.
```
m[i][j] = min over k of  m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j]
```
Fill the table by increasing chain length; track split points to reconstruct the optimal parenthesization.

**Result:** Verified against the classic textbook example (p = [30,35,15,5,10,20,25]) → minimum cost 15125, optimal order `((A1(A2A3))((A4A5)A6))`.

**Complexity:** O(n³) time, O(n²) space.

---

## Summary table

| File | Problem | Technique | Time Complexity |
|------|---------|-----------|------------------|
| 1.c | Invert coin-triangle | Overlap/counting argument | O(1) formula, O(n) demo |
| 2.c | Egg drop | Dynamic Programming | O(E·F²) |
| 3.c | Reve's puzzle | Frame–Stewart (Divide & Conquer) | O(n²) planning, O(FS(n)) moves |
| 4.c | Security switches | BFS on state graph (Gray code) | O(2^n · n) |
| 5.c | Moving target | Constructive parity strategy | O(n) strategy, O(n²) validation |
| 6.c | Best time alive | Sweep line | O(n log n) |
| 7.c | Matrix Chain Multiplication | Dynamic Programming | O(n³) |
