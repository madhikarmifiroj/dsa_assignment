## Program 7 – Dijkstra’s Algorithm for Shortest Paths in a Weighted Graph

This program represents a **weighted graph** using an **adjacency matrix** and implements **Dijkstra’s algorithm** to find the shortest path from a **source vertex** to all other vertices. It also reconstructs and prints the actual shortest paths using a parent array.

---

### (a) Explanation of Data Structures

The graph is defined as:

```c
#define MAX_VERTICES 10
#define INF 1000000000  // A large value to represent "infinity"

typedef struct {
    int numVertices;
    int weight[MAX_VERTICES][MAX_VERTICES]; // weight[i][j] = 0 if no edge, >0 if edge with weight
} Graph;
```

- **`numVertices`**: Number of vertices in the graph.
- **`weight[i][j]`**:
  - `0` means **no edge** from vertex `i` to vertex `j`.
  - A **positive integer** means there is a directed edge from `i` to `j` with that weight.
- **`INF`**: A large constant (`1000000000`) used to represent “infinite” distance for unreachable vertices.

Additional arrays used in Dijkstra’s algorithm:

- **`dist[MAX_VERTICES]`**:
  - `dist[v]` stores the current **shortest known distance** from the source vertex to vertex `v`.
- **`visited[MAX_VERTICES]`**:
  - `visited[v] = 1` means vertex `v` has already been **processed** and its shortest distance is finalized.
- **`parent[MAX_VERTICES]`**:
  - `parent[v]` stores the **previous vertex** on the shortest path from the source to `v`.
  - Used later to reconstruct and print the actual path.

---

### (b) Description of Functions Implemented

1. **`void initGraph(Graph *g, int vertices)`**
   - Initializes the graph:
     - Sets `g->numVertices = vertices`.
     - Sets all entries in `weight[i][j]` to `0` (no edges initially).

2. **`void addEdge(Graph *g, int u, int v, int w)`**
   - Adds a **directed edge** from vertex `u` to vertex `v` with weight `w`.
   - Checks that `u` and `v` are within valid range and that `w` is non-negative.
   - Sets `g->weight[u][v] = w`.
   - Note: This creates a **directed** edge (`u → v`), not undirected.

3. **`int minDistance(int dist[], int visited[], int n)`**
   - Finds and returns the index of the vertex with the **minimum distance value** among all vertices that are **not yet visited**.
   - Iterates through all vertices:
     - If `visited[v] == 0` and `dist[v]` is smaller than the current minimum, updates the minimum and remembers the index.
   - Returns `-1` if no such vertex is found (remaining vertices are unreachable).

4. **`void dijkstra(Graph *g, int src)`**
   - Core implementation of **Dijkstra’s shortest path algorithm** from source vertex `src`.
   - Steps:
     1. Initialize all distances in `dist[]` to `INF`, all `visited[]` to `0`, and all `parent[]` to `-1`.
     2. Set `dist[src] = 0` because the distance from the source to itself is zero.
     3. Repeat up to `n - 1` times:
        - Call `minDistance(dist, visited, n)` to pick the unvisited vertex `u` with the smallest `dist[u]`.
        - Mark `u` as visited.
        - For each vertex `v`:
          - If:
            - `v` is not visited,
            - there is an edge `u → v` (`weight[u][v] > 0`),
            - and going from `src` to `v` through `u` gives a **shorter path** (`dist[u] + weight[u][v] < dist[v]`),
          - then update:
            - `dist[v] = dist[u] + weight[u][v]`
            - `parent[v] = u`
     4. After the loop, `dist[]` contains the **shortest distances** from `src` to all vertices.
   - The function then:
     - Prints the distances from the source to every vertex.
     - Uses `parent[]` to reconstruct and print the full **shortest path** from the source to each vertex, along with the path cost.

---

### (c) Organization of `main()` Function

```c
int main(void) {
    Graph g;
    int vertices = 6;

    // Initialize graph with 6 vertices: 0, 1, 2, 3, 4, 5
    initGraph(&g, vertices);

    // Example weighted directed graph (non-negative weights):
    //
    // 0 -> 1 (4), 0 -> 2 (2)
    // 1 -> 2 (5), 1 -> 3 (10)
    // 2 -> 4 (3)
    // 4 -> 3 (4), 4 -> 5 (11)
    // 3 -> 5 (1)
    addEdge(&g, 0, 1, 4);
    addEdge(&g, 0, 2, 2);
    addEdge(&g, 1, 2, 5);
    addEdge(&g, 1, 3, 10);
    addEdge(&g, 2, 4, 3);
    addEdge(&g, 4, 3, 4);
    addEdge(&g, 4, 5, 11);
    addEdge(&g, 3, 5, 1);

    int source = 0;
    dijkstra(&g, source);

    return 0;
}
```

The `main()` function:

1. Declares a `Graph g` and sets the number of vertices to `6` (`0` to `5`).
2. Calls `initGraph(&g, vertices)` to clear the adjacency matrix.
3. Adds directed edges with weights to form the example weighted graph.
4. Selects `source = 0` as the starting vertex.
5. Calls `dijkstra(&g, source)` to compute and print:
   - The shortest distance from vertex `0` to all other vertices.
   - The actual shortest path to each vertex.
6. Returns `0` to indicate successful program termination.

---

### (d) Sample Output of a Complete Run

For the example graph defined in `main()`, a typical output will look like:

```text
Vertex  Distance from source 0
0       0
1       4
2       2
3       9
4       5
5       10

Shortest paths from source 0:
Path to 0: 0
Path to 1: 0 -> 1 (cost = 4)
Path to 2: 0 -> 2 (cost = 2)
Path to 3: 0 -> 2 -> 4 -> 3 (cost = 9)
Path to 4: 0 -> 2 -> 4 (cost = 5)
Path to 5: 0 -> 2 -> 4 -> 3 -> 5 (cost = 10)
```

Explanation:

- The **distance table** shows the minimum cost to reach each vertex from source `0`.
- The **paths** reconstructed using `parent[]` show one shortest path for each vertex:
  - To reach vertex `3`, the best route is `0 → 2 → 4 → 3` with total cost \(2 + 3 + 4 = 9\).
  - To reach vertex `5`, the best route is `0 → 2 → 4 → 3 → 5` with total cost \(2 + 3 + 4 + 1 = 10\).

This confirms that the program correctly implements Dijkstra’s algorithm and finds shortest paths from a source node to all other nodes in a weighted graph with non-negative edge weights.

