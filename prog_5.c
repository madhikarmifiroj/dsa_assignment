// Program 5: Undirected graph using adjacency matrix with BFS and DFS

#include <stdio.h>

#define MAX_VERTICES 10

// Graph represented using adjacency matrix
typedef struct {
    int numVertices;
    int adj[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Initialize graph with given number of vertices
void initGraph(Graph *g, int vertices) {
    g->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->adj[i][j] = 0;
        }
    }
}

// Add an undirected edge between u and v
void addEdge(Graph *g, int u, int v) {
    if (u < 0 || v < 0 || u >= g->numVertices || v >= g->numVertices) {
        printf("Invalid edge (%d, %d)\n", u, v);
        return;
    }
    g->adj[u][v] = 1;
    g->adj[v][u] = 1; // undirected graph
}

// Print adjacency matrix
void printAdjacencyMatrix(Graph *g) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = 0; j < g->numVertices; j++) {
            printf("%d ", g->adj[i][j]);
        }
        printf("\n");
    }
}

// Breadth-First Search (BFS) from a starting vertex
void BFS(Graph *g, int start) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    if (start < 0 || start >= g->numVertices) {
        printf("Invalid start vertex for BFS: %d\n", start);
        return;
    }

    visited[start] = 1;
    queue[rear++] = start;

    printf("BFS traversal starting from vertex %d: ", start);

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (int v = 0; v < g->numVertices; v++) {
            if (g->adj[current][v] == 1 && !visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }
    printf("\n");
}

// Depth-First Search (DFS) helper (recursive)
void DFSUtil(Graph *g, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int v = 0; v < g->numVertices; v++) {
        if (g->adj[vertex][v] == 1 && !visited[v]) {
            DFSUtil(g, v, visited);
        }
    }
}

// DFS starting from a given vertex
void DFS(Graph *g, int start) {
    int visited[MAX_VERTICES] = {0};

    if (start < 0 || start >= g->numVertices) {
        printf("Invalid start vertex for DFS: %d\n", start);
        return;
    }

    printf("DFS traversal starting from vertex %d: ", start);
    DFSUtil(g, start, visited);
    printf("\n");
}

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

