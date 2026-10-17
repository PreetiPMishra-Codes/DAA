
<div align="center">

# 🔷 DAA LAB — 10
### Graph Algorithms · Disjoint Set Union · Connected Components

**Design and Analysis of Algorithms | BTech — 3rd Semester**

![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)
![Topic](https://img.shields.io/badge/Topic-Graphs%20%26%20DSU-6f42c1?style=for-the-badge)
![Programs](https://img.shields.io/badge/Programs-5-success?style=for-the-badge)

*A concise collection of C implementations for graph and Union-Find problems.*

</div>

---

## 📂 Repository Structure

```text
DAA-Lab-10/
├── 1.c   # Online Graph Bipartiteness Testing
├── 2.c   # Dynamic Connected Components in a Grid
├── 3.c   # Maximum Weight Component with Size Constraints
├── 4.c   # Reverse Time-Step DSU Application
├── 5.c   # Lexicographically Smallest Connected Component Permutation
└── README.md
```

## 🧭 Problem Index

| File | Problem | Core technique |
|:---:|---|---|
| [`1.c`](1.c) | **Online Graph Bipartiteness** | Parity DSU |
| [`2.c`](2.c) | **Dynamic Grid Islands** | Flattened-grid DSU |
| [`3.c`](3.c) | **Maximum-Weight Component** | DSU + component size and weight sum |
| [`4.c`](4.c) | **Reverse Vertex Deletions** | Reverse processing + DSU |
| [`5.c`](5.c) | **Lexicographically Smallest Permutation** | DSU + sorting |

---

## ⚙️ Getting Started

### Compile and run

Using GCC:

```bash
gcc 1.c -o 1
./1
```

On Windows:

```powershell
gcc 1.c -o 1.exe
.\1.exe
```

Replace `1.c` with the filename you want to run.

> **Input:** Each program reads data using `scanf`. Follow the input order listed under the relevant problem.

---

## 🧠 Solutions at a Glance

<details>
<summary><strong>1. Online Graph Bipartiteness Testing — 1.c</strong></summary>

**Concept:** A graph is bipartite if every edge connects vertices belonging to different color groups.

**Approach**
- Process edges one at a time.
- Use DSU with parity to track whether vertices have the same or opposite colors.
- Accept an edge if the endpoints can have opposite colors; otherwise, reject it.

**Input format**
```text
V E
u1 v1
u2 v2
...
```

**Complexity**
- ⏱️ **Time:** DSU-style bound `O((V + E) α(V))` with union by size/rank. The current implementation does not use balancing, so this bound is not guaranteed.
- 💾 **Space:** `O(V)` for parent and parity arrays.

</details>

<details>
<summary><strong>2. Dynamic Connected Components in a Grid — 2.c</strong></summary>

**Concept:** Count islands as land cells are added to a water-filled grid. Only up, down, left, and right neighbors are connected.

**Approach**
- Flatten `(r, c)` to `(r - 1) * C + (c - 1)`.
- Each newly added land cell creates one island.
- Merge it with active neighboring land cells; each successful union reduces the island count by one.
- Repeated additions of the same cell do not change the count.

**Input format**
```text
R C k
r1 c1
r2 c2
...
rk ck
```

**Complexity**
- ⏱️ **Time:** `O(RC + k α(RC))`, including initialization.
- 💾 **Space:** `O(RC)`.

</details>

<details>
<summary><strong>3. Maximum Weight Component with Size Constraints — 3.c</strong></summary>

**Concept:** Find the maximum sum of vertex weights among connected components whose size is at most `K`.

**Approach**
- Initialize each vertex as its own component.
- Maintain each component's size and total vertex weight.
- After every edge insertion, scan the component representatives and select the greatest weight sum among components of size `≤ K`.

**Input format**
```text
n m K
w1 w2 ... wn
u1 v1
u2 v2
...
```

**Complexity**
- ⏱️ **Time:** `O(n + (n + m) α(n) + mn)`.
- 💾 **Space:** `O(n)`.

> This solution maximizes vertex-weight sums; edge weights are not used.

</details>

<details>
<summary><strong>4. Reverse Time-Step DSU Application — 4.c</strong></summary>

**Concept:** Deleting a vertex can split a component, so process deletions backward and restore vertices instead.

**Approach**
- Read all vertices, weights, edges, and the deletion order.
- Restore vertices in reverse deletion order.
- Connect each restored vertex to currently active vertices using the graph's edges.
- Track the maximum component weight sum and report answers in the original deletion order.

**Input format**
```text
n m
w1 w2 ... wn
u1 v1
u2 v2
...
p1 p2 ... pn
```

**Complexity**
- ⏱️ **Time:** `O(nm α(n) + n² α(n))` as a conservative bound for this implementation.
- 💾 **Space:** `O(n + m)`.

</details>

<details>
<summary><strong>5. Lexicographically Smallest Connected Component Permutation — 5.c</strong></summary>

**Concept:** Values can be swapped along graph edges. Within each connected component, its values can be rearranged among its indices.

**Approach**
- Use DSU to group indices connected by allowed swaps.
- Collect each component's indices and values.
- Sort both lists in ascending order and assign the smallest value to the smallest index.

**Input format**
```text
n m
a1 a2 ... an
u1 v1
u2 v2
...
```

**Complexity**
- ⏱️ **Time:** `O(n² α(n) + n² + m α(n))` as a conservative bound for this implementation.
- 💾 **Space:** `O(n)` auxiliary space.

</details>

---

## 📊 Complexity Comparison

Let `α(n)` denote the **inverse Ackermann function**, which grows so slowly that it is effectively constant for practical input sizes.

| File | Time complexity | Space complexity |
|:---:|---|---|
| `1.c` | DSU-style `O((V + E) α(V))` with balancing; not guaranteed by current unbalanced unions | `O(V)` |
| `2.c` | `O(RC + k α(RC))` | `O(RC)` |
| `3.c` | `O(n + (n + m) α(n) + mn)` | `O(n)` |
| `4.c` | `O(nm α(n) + n² α(n))` (conservative) | `O(n + m)` |
| `5.c` | `O(n² α(n) + n² + m α(n))` (conservative) | `O(n)` |

---

## 📝 Notes

- The programs use fixed-size arrays, so inputs must remain within each file's declared array limits.
- `2.c` uses a larger array for grid cells; ensure `R × C` fits within that limit.
- Complexity reflects the implementations described here, including their straightforward scans. More optimized solutions are possible.
- Compile each file separately because each contains its own `main()` function.

---

<div align="center">

**Made for DAA Lab-10** · *Graphs and Disjoint Set Union*

</div>
