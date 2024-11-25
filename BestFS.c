#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100  // Maximum number of vertices

// Structure for adjacency list node
struct Node {
    int vertex;
    int cost;
    struct Node* next;
};

// Structure for a priority queue node
struct PriorityQueue {
    int vertex;
    int priority;
};

// Structure for the graph
struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
    int* heuristic;
};

// Function to create a new adjacency list node
struct Node* createNode(int v, int cost) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->cost = cost;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with n vertices
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));
    graph->heuristic = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int cost) {
    struct Node* newNode = createNode(dest, cost);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // For undirected graph, add an edge from dest to src
    newNode = createNode(src, cost);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Swap function for the priority queue
void swap(struct PriorityQueue* a, struct PriorityQueue* b) {
    struct PriorityQueue temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify the priority queue
void heapify(struct PriorityQueue* pq, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && pq[left].priority < pq[smallest].priority)
        smallest = left;

    if (right < n && pq[right].priority < pq[smallest].priority)
        smallest = right;

    if (smallest != i) {
        swap(&pq[i], &pq[smallest]);
        heapify(pq, n, smallest);
    }
}

// Function to insert into the priority queue
void insert(struct PriorityQueue* pq, int* size, int vertex, int priority) {
    pq[*size].vertex = vertex;
    pq[*size].priority = priority;
    (*size)++;

    // Heapify the new node upwards
    for (int i = (*size) / 2 - 1; i >= 0; i--) {
        heapify(pq, *size, i);
    }
}

// Function to extract the minimum (best) from the priority queue
struct PriorityQueue extractMin(struct PriorityQueue* pq, int* size) {
    struct PriorityQueue root = pq[0];
    pq[0] = pq[(*size) - 1];
    (*size)--;

    heapify(pq, *size, 0);

    return root;
}

// Best-First Search Algorithm
void bestFirstSearch(struct Graph* graph, int startVertex, int goalVertex) {
    struct PriorityQueue pq[MAX];
    int pqSize = 0;

    // Insert the start vertex with its heuristic value into the priority queue
    insert(pq, &pqSize, startVertex, graph->heuristic[startVertex]);
    graph->visited[startVertex] = 1;

    printf("Best-First Search traversal:\n");

    while (pqSize > 0) {
        // Extract the node with the lowest heuristic value (best node)
        struct PriorityQueue current = extractMin(pq, &pqSize);
        int currentVertex = current.vertex;

        printf("Visited %d\n", currentVertex);

        // If the goal is reached, terminate the search
        if (currentVertex == goalVertex) {
            printf("Goal vertex %d reached!\n", goalVertex);
            return;
        }

        // Explore neighbors
        struct Node* adjList = graph->adjLists[currentVertex];
        while (adjList != NULL) {
            int adjVertex = adjList->vertex;

            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                // Insert the neighbor into the priority queue based on heuristic
                insert(pq, &pqSize, adjVertex, graph->heuristic[adjVertex]);
            }
            adjList = adjList->next;
        }
    }

    printf("Goal vertex %d not reachable from start vertex %d\n", goalVertex, startVertex);
}

int main() {
    int vertices, edges, src, dest, cost, startVertex, goalVertex;

    // Input number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    struct Graph* graph = createGraph(vertices);

    // Input edges and their costs
    for (int i = 0; i < edges; i++) {
        printf("Enter edge %d (source destination cost): ", i + 1);
        scanf("%d %d %d", &src, &dest, &cost);
        addEdge(graph, src, dest, cost);
    }

    // Input heuristic values for each vertex
    printf("Enter heuristic values for each vertex:\n");
    for (int i = 0; i < vertices; i++) {
        printf("Heuristic for vertex %d: ", i);
        scanf("%d", &graph->heuristic[i]);
    }

    // Input the start and goal vertices
    printf("Enter the starting vertex: ");
    scanf("%d", &startVertex);
    printf("Enter the goal vertex: ");
    scanf("%d", &goalVertex);

    // Perform Best-First Search
    bestFirstSearch(graph, startVertex, goalVertex);

    return 0;
}
