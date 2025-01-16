#include <stdio.h>
#include <limits.h>

#define MAX_NODES 10
#define INF INT_MAX

// Structure to represent a node in the subnet graph
typedef struct {
    int weight[MAX_NODES];
} Node;

// Function to initialize the subnet graph
void initGraph(Node graph[MAX_NODES], int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (i == j) {
                graph[i].weight[j] = 0; // Distance to self is 0
            } else {
                graph[i].weight[j] = INF; // Initialize all other distances to infinity
            }
        }
    }
}

// Function to add an edge (link) between two nodes in the subnet graph
void addEdge(Node graph[MAX_NODES], int src, int dest, int weight) {
    graph[src].weight[dest] = weight;
    graph[dest].weight[src] = weight; // Assuming bidirectional links
}

// Function to print the routing table of a node using distance vector routing algorithm
void printRoutingTable(Node graph[MAX_NODES], int numNodes, int node) {
    int distance[numNodes];
    int nextHop[numNodes];

    // Initialize distance and nextHop arrays
    for (int i = 0; i < numNodes; i++) {
        distance[i] = INF;
        nextHop[i] = -1;
    }

    distance[node] = 0; // Distance to self is 0

    // Perform distance vector routing algorithm
    for (int k = 0; k < numNodes; k++) {
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                if (graph[i].weight[j] != INF && distance[i] + graph[i].weight[j] < distance[j]) {
                    distance[j] = distance[i] + graph[i].weight[j];
                    nextHop[j] = i;
                }
            }
        }
    }

    // Print routing table
    printf("Routing table for Node %d:\n", node);
    printf("Destination\tNext Hop\tDistance\n");
    for (int i = 0; i < numNodes; i++) {
        if (i != node) {
            printf("%d\t\t%d\t\t%d\n", i, nextHop[i], distance[i]);
        }
    }
}

int main() {
    int numNodes, numEdges;
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    Node graph[MAX_NODES];
    initGraph(graph, numNodes);

    // Input edges (links) and weights
    printf("Enter the source, destination, and weight for each edge:\n");
    for (int i = 0; i < numEdges; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    // Print routing table for each node
    for (int i = 0; i < numNodes; i++) {
        printRoutingTable(graph, numNodes, i);
        printf("\n");
    }

    return 0;
}
