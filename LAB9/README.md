# DAA Lab-09 – Greedy algorithms (solutions)

Compile any program with `gcc -O2 -o qN qN_*.c` (keep `heap.h` in the same folder). Input formats are in the header comment of each file.

| # | Problem | Greedy choice | Time | Space |
|---|---------|---------------|------|-------|
| 1 | Fractional knapsack with decay | take item with largest current density v/w − λt | O(n²) simple; O(n log n) with upper envelope of lines | O(n) |
| 2 | Huffman + canonical code | merge two least-frequent nodes (min-heap); assign canonical codes by (length, symbol) | O(n log n) | O(n) |
| 3 | Min refuelling stops | when stuck, refuel at largest station already passed (max-heap) | O(n log n) | O(n) |
| 4 | Connect sticks | join two shortest (min-heap) | O(n log n) | O(n) |
| 5 | Candy | left→right pass, right→left pass, take max | O(n) | O(n) |
| 6 | Reorganise string, distance K | place char with most copies left that is "cooled down" | O(nσ), σ=256 (O(n log σ) with heap+queue) | O(σ + n) |
| 7 | Minimise deviation | double all odds (max form), then repeatedly halve the max while it is even | O(n log n · log M) | O(n) |
| 8 | Meeting rooms | sort starts & ends; sweep | O(n log n) | O(n) |
| 9 | Hu–Tucker | merge min-weight *compatible* pair (no leaf between) | O(n²) as coded (O(n log n) with the full algorithm) | O(n) |
| 10 | Greedy superstring | merge pair with max overlap | O(n²·L) greedy; brute force O(n!·n) for checking | – |

## Notes per problem

**1. Decay knapsack.** The statement doesn't fix when "time t" is measured, so I assumed unit-rate consumption: t = total weight already taken when an item starts, and the item is taken at the density it has at that moment. Greedy picks the largest current density d_i(t) = v_i/w_i − λ_i t, takes min(w_i, remaining), advances t, and stops when no density is positive. Each step needs an argmax over remaining items, so O(n²); the d_i(t) are lines in t, so a kinetic/upper-envelope structure gives O(n log n). Caveat: an adjacent-swap exchange argument on two whole items shows the pairwise order favours larger λ first (the later item loses λ·t·x), which is not always the same as largest current density. So treat this as the natural greedy, and check it against brute force on small cases before claiming optimality for your chosen model.

**2. Huffman.** Optimality via the exchange argument (the two rarest symbols can be siblings at maximum depth) plus optimal substructure. n−1 merges × O(log n) per heap operation. Canonical codes: sort by (length, symbol); first code = 0; each next code = (prev+1) << (len_next − len_prev).

**3. Refuelling.** Invariant: `reach` = farthest point attainable with k stops. Every station within reach is a candidate; if we must stop, using the largest candidate is never worse (exchange argument). Each station is pushed/popped once → O(n log n) after the sort.

**4. Sticks.** Same structure as Huffman: sticks that are merged early are counted in more additions, so the smallest ones must be merged first. n−1 iterations, O(log n) each.

**5. Candy.** Constraints are only between neighbours: the left pass satisfies "higher than left neighbour", the right pass "higher than right neighbour", and the max satisfies both with the least candies per child. (An O(1)-space version counts rising/falling slopes.)

**6. Reorganise.** The most frequent remaining character is the hardest to place, so use it whenever it is allowed. If no character is available at some position, the answer is empty. Feasibility check is implicit.

**7. Min deviation.** Odd x can become 2x, even x can only shrink, so after doubling the odds every element only goes down by halving. The max is the only element worth shrinking; stop when it is odd. Each element is halved ≤ log M times, each heap step is O(log n).

**8. Meeting rooms.** The maximum overlap equals the number of rooms. Sorting starts and ends separately and sweeping computes it; `end == start` does not conflict.

**9. Hu–Tucker.** Phase 1 builds a (non-alphabetic) tree with the compatible-pair rule; leaf depths from it are optimal, and an alphabetic tree with the same depths exists (phase 2). Cost = Σ wᵢ·depthᵢ. The program checks this against an O(n³) interval DP; I ran 400 random cases (n ≤ 10, with many ties) with 0 mismatches. This is a simple O(n²) simulation, not the O(n log n) implementation.

**10. Greedy superstring.** Open problem, no proof expected. The program removes substrings, runs the greedy max-overlap merge, brute-forces the optimum for n ≤ 8, and prints the ratio, so you can search for bad instances. I couldn't verify the September 2026 arXiv claim, so I'd read the paper and test its counterexample family (even k ≥ 10) with the program before relying on it. Known baseline: greedy is proven to be within a factor 3.5 of optimal; the 2-approximation was conjectured, and the 9k+2 over 4k+4 figure in the sheet comes from that paper. Also note that the original problem is NP-hard.
