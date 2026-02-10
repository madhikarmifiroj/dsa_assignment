## DSA Assignment Programs (C)

This repository contains a collection of **Data Structures and Algorithms** programs written in **C**, along with detailed Markdown documentation for each question.

All source files and docs are under the `dsa_assignment/` directory.

---

### Structure

- **Programs**: `prog_1.c` – `prog_8.c`
- **Documentation**: `doc_1.md` – `doc_8.md`  
  Each `doc_X.md` corresponds to `prog_X.c` and explains:
  - Data structures used
  - Functions and their purpose
  - Organization of `main()`
  - Sample outputs

---

### List of Programs

- **`prog_1.c` / `doc_1.md`**  
  Stack-based checker for **balanced parentheses/brackets** in expressions.

- **`prog_2.c` / `doc_2.md`**  
  **Infix to postfix** conversion and **postfix evaluation** using stacks.

- **`prog_3.c` / `doc_3.md`**  
  Singly linked list with **reverse traversal** implemented via recursion.

- **`prog_4.c` / `doc_4.md`**  
  **Doubly linked list** with **insert-after** and **delete-node** operations.

- **`prog_5.c` / `doc_5.md`**  
  Undirected graph using an **adjacency matrix**, with **BFS** and **DFS** traversals.

- **`prog_6.c` / `doc_6.md`**  
  Building **min-heap** and **max-heap** from an unsorted array using heapify.

- **`prog_7.c` / `doc_7.md`**  
  **Dijkstra’s algorithm** on a weighted graph (adjacency matrix) to find shortest paths from a source.

- **`prog_8.c` / `doc_8.md`**  
  Generates random integers, lets the user choose a **sorting algorithm** (Bubble, Selection, Insertion, Merge), sorts the data, and reports **comparisons** and **swaps**.

---

### How to Compile and Run

From the project root:

```bash
cd dsa_assignment

# Example: compile and run program 1
gcc prog_1.c -o prog_1
./prog_1

# Example: compile and run program 8
gcc prog_8.c -o prog_8
./prog_8
```

Use the corresponding `doc_X.md` while reviewing or demonstrating each program.

