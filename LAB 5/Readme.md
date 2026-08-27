# DAA LAB-5

**Why O(n log n) in all cases:**
- Heap is always a complete binary tree
- Heapify always takes O(log n) regardless of input
- No dependence on data distribution

---

## Summary
```
| Problem         | Algorithm    | Time Complexity             | Recurrence                       |
|-----------------|--------------|-----------------------------|----------------------------------|
| 1. Find Median  | Quickselect  | O(n) avg, O(n²) worst       | T(n) = T(n/2) + O(n)             |
| 2. K'th Smallest| Quickselect  | O(n) avg, O(n²) worst       | T(n) = T(n/2) + O(n)             |
| 3. Quick Sort   | Quick Sort   | O(n log n) avg, O(n²) worst | T(n) = 2T(n/2) + O(n)            |
| 4. Heap Sort    | Heap Sort    | O(n log n) all cases        | Build: O(n), Extract: O(n log n) |
```
