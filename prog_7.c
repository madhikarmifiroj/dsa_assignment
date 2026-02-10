// Program 7: Dijkstra's algorithm for shortest paths from a source vertex

#include <stdio.h>

#define MAX_VERTICES 10
#define INF 1000000000  // A large value to represent "infinity"

// Graph represented using adjacency matrix with weights
typedef struct {
    int numVertices;
    int weight[MAX_VERTICES][MAX_VERTICES]; // weight[i][j] = 0 if no edge, >0 if edge with weight
} Graph;

// Initialize graph with given number of vertices
void initGraph(Graph *g, int vertices) {
    g->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->weight[i][j] = 0; // 0 means no edge between i and j
        }
    }
}

// Add a directed edge u -> v with given non-negative weight
void addEdge(Graph *g, int u, int v, int w) {
    if (u < 0 || v < 0 || u >= g->numVertices || v >= g->numVertices) {
        printf("Invalid edge (%d -> %d)\n", u, v);
        return;
    }
    if (w < 0) {
        printf("Negative weights are not allowed in Dijkstra's algorithm.\n");
        return;
    }
    g->weight[u][v] = w;
}

// Find the vertex with the minimum distance value from the set of vertices
// not yet included in the shortest path tree
int minDistance(int dist[], int visited[], int n) {
    int min = INF;
    int minIndex = -1;

    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Dijkstra's algorithm to find shortest paths from src to all vertices
void dijkstra(Graph *g, int src) {
    int n = g->numVertices;
    int dist[MAX_VERTICES];    // dist[i] will hold the shortest distance from src to i
    int visited[MAX_VERTICES]; // visited[i] will be 1 if vertex i is included in shortest path tree
    int parent[MAX_VERTICES];  // To store shortest path tree (for path reconstruction)

    // Initialize all distances as infinite and visited[] as 0
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < n - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, visited, n);
        if (u == -1) {
            // Remaining vertices are not reachable from src
            break;
        }

        visited[u] = 1;

        // Update dist[v] only if:
        // - v is not visited
        // - there is an edge from u to v
        // - and total weight of path from src to v through u is smaller than current dist[v]
        for (int v = 0; v < n; v++) {
            if (!visited[v] && g->weight[u][v] > 0 && dist[u] != INF &&
                dist[u] + g->weight[u][v] < dist[v]) {
                dist[v] = dist[u] + g->weight[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the result: distances from src to each vertex
    printf("Vertex\tDistance from source %d\n", src);
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            printf("%d\tINF (unreachable)\n", i);
        } else {
            printf("%d\t%d\n", i, dist[i]);
        }
    }

    // Optionally, print paths using the parent[] array
    printf("\nShortest paths from source %d:\n", src);
    for (int i = 0; i < n; i++) {
        if (i == src) {
            printf("Path to %d: %d\n", i, src);
        } else if (dist[i] == INF) {
            printf("Path to %d: unreachable\n", i);
        } else {
            // Reconstruct path in reverse using parent[]
            int path[MAX_VERTICES];
            int pathLen = 0;
            int current = i;
            while (current != -1) {
                path[pathLen++] = current;
                current = parent[current];
            }

            printf("Path to %d: ", i);
            // Print path from src to i (reverse the collected order)
            for (int j = pathLen - 1; j >= 0; j--) {
                printf("%d", path[j]);
                if (j > 0) {
                    printf(" -> ");
                }
            }
            printf(" (cost = %d)\n", dist[i]);
        }
    }
}

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

