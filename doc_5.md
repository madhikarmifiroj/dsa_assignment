## Program 5 – Undirected Graph Using Adjacency Matrix with BFS and DFS

This program represents an **undirected graph** using an **adjacency matrix** and implements **Breadth-First Search (BFS)** and **Depth-First Search (DFS)** traversal techniques. It demonstrates both traversals on a sample graph.

---

### (a) Explanation of Data Structures

The graph is defined using a structure with an adjacency matrix:

```c
#define MAX_VERTICES 10

typedef struct {
    int numVertices;
    int adj[MAX_VERTICES][MAX_VERTICES];
} Graph;
```

- **`numVertices`**: Stores the actual number of vertices in the graph.
- **`adj`**: A 2D array where:
  - `adj[i][j] = 1` if there is an edge between vertex `i` and vertex `j`.
  - `adj[i][j] = 0` if there is **no** edge between `i` and `j`.
- Because the graph is **undirected**, the matrix is **symmetric**:
  - If there is an edge between `u` and `v`, then:
    - `adj[u][v] = 1` and `adj[v][u] = 1`.

For BFS and DFS, the program also uses:

- A **`visited`** array:

  ```c
  int visited[MAX_VERTICES] = {0};
  ```

  - `visited[i] = 1` means vertex `i` has already been visited.

- A simple **queue** implemented with an array for BFS:

  ```c
  int queue[MAX_VERTICES];
  int front = 0, rear = 0;
  ```

---

### (b) Description of Functions Implemented

1. **`void initGraph(Graph *g, int vertices)`**
   - Initializes the graph with a given number of vertices.
   - Sets `g->numVertices = vertices`.
   - Fills the adjacency matrix with zeros (no edges initially).

2. **`void addEdge(Graph *g, int u, int v)`**
   - Adds an **undirected edge** between vertices `u` and `v`.
   - Validates that `u` and `v` are within range.
   - Sets:
     - `g->adj[u][v] = 1`
     - `g->adj[v][u] = 1`
   - This ensures the adjacency matrix is symmetric for an undirected graph.

3. **`void printAdjacencyMatrix(Graph *g)`**
   - Prints the adjacency matrix row by row.
   - Helps visualize the graph connections in matrix form.

4. **`void BFS(Graph *g, int start)`**
   - Performs **Breadth-First Search** starting from vertex `start`.
   - Uses:
     - `visited[]` array to track visited vertices.
     - `queue[]` array to process vertices in FIFO order.
   - Algorithm:
     1. Mark `start` as visited and enqueue it.
     2. While the queue is not empty:
        - Dequeue a vertex `current` and print it.
        - For every vertex `v`:
          - If there is an edge `current → v` (`adj[current][v] == 1`) and `v` is not visited:
            - Mark `v` as visited and enqueue `v`.
   - Visits vertices **level by level** (all neighbors first, then neighbors of neighbors).

5. **`void DFSUtil(Graph *g, int vertex, int visited[])`**
   - Helper function that performs **recursive DFS** from a given `vertex`.
   - Marks `vertex` as visited and prints it.
   - For each neighbor `v`:
     - If there is an edge `vertex → v` and `v` is not visited, recursively calls `DFSUtil(g, v, visited)`.

6. **`void DFS(Graph *g, int start)`**
   - Wrapper function to start DFS from a given starting vertex.
   - Initializes a `visited[]` array to all zeros.
   - Calls `DFSUtil(g, start, visited)` and prints the traversal order.
   - DFS explores **as deep as possible** along each branch before backtracking.

---

### (c) Organization of `main()` Function

```c
int main(void) {
    Graph g;
    int vertices = 5;

    // Initialize graph with 5 vertices: 0, 1, 2, 3, 4
    initGraph(&g, vertices);

    // Example undirected graph:
    // 0 - 1 - 2
    // |   |
    // 3 - 4
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 0, 3);
    addEdge(&g, 1, 4);
    addEdge(&g, 3, 4);

    // Show adjacency matrix
    printAdjacencyMatrix(&g);

    // Demonstrate BFS and DFS from vertex 0
    BFS(&g, 0);
    DFS(&g, 0);

    return 0;
}
```

The `main()` function follows these steps:

1. **Graph initialization**:
   - Creates a `Graph` variable `g`.
   - Sets number of vertices to `5` (`0, 1, 2, 3, 4`).
   - Calls `initGraph(&g, vertices)` to clear the adjacency matrix.
2. **Build example graph**:
   - Adds undirected edges to form the structure:
     - `0` connected to `1` and `3`
     - `1` connected to `2` and `4`
     - `3` connected to `4`
3. **Display structure**:
   - Calls `printAdjacencyMatrix(&g)` to print the adjacency matrix.
4. **Graph traversals**:
   - Calls `BFS(&g, 0)` to perform breadth-first traversal starting from vertex `0`.
   - Calls `DFS(&g, 0)` to perform depth-first traversal starting from the same vertex.
5. **Program termination**:
   - Returns `0` to indicate successful execution.

---

### (d) Sample Output of a Complete Run

For the example graph initialized in `main()`, a sample run may produce:

```text
Adjacency Matrix:
0 1 0 1 0
1 0 1 0 1
0 1 0 0 0
1 0 0 0 1
0 1 0 1 0
BFS traversal starting from vertex 0: 0 1 3 2 4
DFS traversal starting from vertex 0: 0 1 2 4 3
```

Explanation:

- **BFS**:
  - Starts at `0`, visits neighbors `1` and `3` first.
  - Then visits neighbors of `1` (`2` and `4`), giving the order: `0 1 3 2 4`.
- **DFS**:
  - Starts at `0`, goes deep via `1 → 2` first.
  - Backtracks, then visits other neighbors (`4`, then `3`), giving one possible DFS order: `0 1 2 4 3`.

This confirms that the program correctly represents an undirected graph using an adjacency matrix and traverses it using both BFS and DFS techniques.

