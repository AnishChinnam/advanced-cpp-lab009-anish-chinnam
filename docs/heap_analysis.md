# Max-Heap Analysis

A max-heap is a complete binary tree stored in a vector. Every parent is at least
as large as its children, so index 0 holds the maximum. With zero-based indices,
left(i) = 2i + 1, right(i) = 2i + 2, and parent(i) = (i - 1) / 2 for i > 0.
Child indices are used only when they are within the vector. Duplicates and
negative integers are supported. Empty `top` and `pop` throw `std::logic_error`.

## Runtime and space

| Operation | Time | Auxiliary space |
|---|---|---|
| top / size / empty | O(1) | O(1) |
| contains | O(n) worst case | O(1) |
| heapifyUp / heapifyDown | O(log n) worst case | O(1) |
| push | O(log n) amortized; O(n) on vector reallocation | O(1), excluding vector growth |
| pop | O(log n) worst case | O(1) |
| buildHeap | O(n) | O(n) vector storage |
| heapSort | O(n log n) | O(n) |
| toVector | O(n) | O(n) returned copy |

Insertion appends a leaf and swaps upward until the parent order is restored.
Removal saves the root, moves the last leaf to the root, and swaps downward with
the larger child. Each follows at most the O(log n) height of a complete tree;
when no swaps are needed, repair is O(1). Vector growth can copy all elements,
so an individual push can cost O(n), despite its usual amortized logarithmic cost.

Bottom-up construction repairs internal nodes from the last parent to the root.
Most nodes are near leaves: summing O(n / 2^(k+1)) nodes times O(k) work over
heights k gives O(n), rather than the O(n log n) bound from repeated insertion.
The implementation copies the input into owned vector storage first.

`heapSort` copies the heap, repeatedly extracts maxima, and fills the result from
right to left. It returns ascending order and preserves the original heap.
Its O(n) extra memory differs from in-place heapsort's O(1) auxiliary space.
Stored heap data itself takes O(n) space, with vector capacity potentially larger
than the active size. The iterative repair routines avoid recursive stack use.

## Trade-offs

A sorted vector offers O(log n) binary search and O(1) maximum lookup, but arbitrary
insertion takes O(n) shifts. A balanced BST supports search, insertion, and
removal in O(log n), with pointer overhead and less contiguous storage; an
unbalanced BST may degrade to O(n). A heap gives efficient priority insertion and
maximum removal with contiguous storage, but arbitrary membership is O(n):
sibling subtrees are not globally sorted.

A priority queue is an abstraction; this max-heap is one implementation. It is
appropriate for schedulers, highest-priority work selection, and repeated maximum
extraction. Prefer a balanced BST for ordered searches/range queries or a sorted
vector for mostly static, search-heavy data.

## Validation

Run `make`, `make run`, and `make test`. Tests cover empty exceptions, singleton
removal, duplicates, negatives, rebuilding, sorted output without mutation, and
mixed operations compared against `std::priority_queue` while checking parent order.
