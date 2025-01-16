#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the subnet graph
struct node {
  int id;
  int weight;
  struct node *next;
};

// Structure to represent the subnet graph
struct subnet_graph {
  struct node *nodes;
};

// Function to create a new node
struct node *create_node(int id, int weight) {
  struct node *new_node = malloc(sizeof(struct node));
  new_node->id = id;
  new_node->weight = weight;
  new_node->next = NULL;
  return new_node;
}

// Function to add a new node to the subnet graph
void add_node(struct subnet_graph *graph, struct node *new_node) {
  new_node->next = graph->nodes;
  graph->nodes = new_node;
}

// Function to print the subnet graph
void print_subnet_graph(struct subnet_graph *graph) {
  struct node *current_node = graph->nodes;
  while (current_node != NULL) {
    printf("Node %d: weight %d\n", current_node->id, current_node->weight);
    current_node = current_node->next;
  }
}

// Function to calculate the routing table for each node in the subnet graph using the distance vector routing algorithm
void calculate_routing_table(struct subnet_graph *graph) {
  // Initialize the routing table for each node
  graph->num_nodes = 0;
  struct node *current_node = graph->nodes;
  while (current_node != NULL) {
    graph->num_nodes++;
    current_node->routing_table = malloc(sizeof(int) * graph->num_nodes);
    for (int i = 0; i < graph->num_nodes; i++) {
      current_node->routing_table[i] = INFINITY;
    }
    current_node->routing_table[current_node->id] = 0;
    current_node = current_node->next;
  }

  // Iterate over the nodes in the graph and update their routing tables
  ...
}
Wi

  // Iterate over the nodes in the graph and update their routing tables
  for (int i = 0; i < graph->num_nodes; i++) {
    current_node = graph->nodes;
    while (current_node != NULL) {
      for (struct node *neighbor = current_node->next; neighbor != NULL; neighbor = neighbor->next) {
        int new_distance = current_node->weight + neighbor->weight;
        if (new_distance < current_node->routing_table[neighbor->id]) {
          current_node->routing_table[neighbor->id] = new_distance;
        }
      }
      current_node = current_node->next;
    }
  }

  // Print the routing table for each node
  current_node = graph->nodes;
  while (current_node != NULL) {
    printf("Routing table for node %d:\n", current_node->id);
    for (int i = 0; i < graph->num_nodes; i++) {
      printf("Node %d: distance %d\n", i, current_node->routing_table[i]);
    }
    current_node = current_node->next;
  }
}

int main() {
  // Create a new subnet graph
  struct subnet_graph *graph = malloc(sizeof(struct subnet_graph));
  graph->nodes = NULL;

  // Add nodes to the subnet graph
  add_node(graph, create_node(0, 10));
  add_node(graph, create_node(1, 20));
  add_node(graph, create_node(2, 30));
  add_node(graph, create_node(3, 40));

  // Print the subnet graph
  print_subnet_graph(graph);

  // Calculate the routing table for each node in the subnet graph
  calculate_routing_table(graph);

  return 0;
}