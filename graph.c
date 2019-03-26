/*
 * Functions to allocate space for and create a graph, add edges to graph, run a DFS, and free allocated memory.
 * The structure for the node, createNode(), createGraph(), addEdge(), and DFS() came from https://www.programiz.com/dsa/graph-dfs.
 */

#include "graph.h"
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

/*
 * The struct node is used to represent each node in the graph.
 * The struct contains attributes vertex, the vertex number, and a pointer to the next node.
 * https://www.programiz.com/dsa/graph-dfs
 *
 */
struct node {
    int vertex;
    struct node* next;
};

/*
 * The createNode() function allocates space for a new node, assigns the vertex, and sets the pointer next to NULL.
 * The function is passed the integer num, the vertex number, and returns a pointer to the new node.
 * https://www.programiz.com/dsa/graph-dfs
 */
struct node *createNode(int num) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = num;
    newNode->next = NULL;
    return newNode;
}

/*
 * The createGraph() function  allocates space for a new graph with num number of vertices,
 * allocates space for the adjacency list and visited arrays, and sets all visited slots to 0 and adjacency pointers to NULL.
 * The function returns a pointer to the new graph.
 * https://www.programiz.com/dsa/graph-dfs
 */
struct Graph *createGraph(int num) {
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numVertices = num;
    graph->adjacencyList = malloc(num * sizeof(struct node *));
    graph->visited = malloc(num * sizeof(int));
    for(int i = 0; i < num; i++) {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

/*
 * The freeAdjacencyList() function frees the memory allocated for the nodes at a particular vertex in the adjacency list.
 * The function takes in a pointer to a graph, and the vertex number vertex to free the adjacency list at.
 */
void freeAdjacencyList(struct Graph *graph, int vertex) {
    //while there is still a node in the adjacency list at the vertex
    while(graph->adjacencyList[vertex] != NULL) {
        struct node *temp;
        temp = graph->adjacencyList[vertex];
        graph->adjacencyList[vertex] = temp->next;
        free(temp);
    }
}

/*
 * The freeGraph() function frees the memory allocated for a graph and its included visited array and adjacency list.
 * The function is passed a pointer to the graph to be freed.
 */
void freeGraph(struct Graph *graph) {
    free(graph->visited);
    for(int i = 0; i < graph->numVertices; i++) {
        freeAdjacencyList(graph, i);
    }
    free(graph->adjacencyList);
    free(graph);
}

/*
 * The addEdge() function adds an edge between vertex one and two in a graph, but only in one direction
 * (vertex one points to two, but two doesn't point to one unless the function is called again with the vertices switched)
 * The function is passed a pointer to a graph, the vertex vertexOne to add the edge to,
 * and the vertex vertexTwo to add to the adjacency list.
 * https://www.programiz.com/dsa/graph-dfs
 */
void addEdge(struct Graph *graph, int vertexOne, int vertexTwo) {
    struct node *newNode = createNode(vertexTwo);
    newNode->next = graph->adjacencyList[vertexOne];
    graph->adjacencyList[vertexOne] = newNode;
}

/*
 * The updateEdge() function allows edges to be added to a graph either from only vertex A to B, or from A to B and B to A.
 * The function is passed a pointer to the graph to be updated, the first vertex vertexOne, the second vertex vertexTwo,
 * and either 1 or 2 through edgeToAdd which determines if the edge is added only A to B (1) or A to B and B to A (2).
 */
void updateEdge(struct Graph *graph, int vertexOne, int vertexTwo, int edgeToAdd) {
    //an edge is added vertexOne to vertexTwo
    if(edgeToAdd == 1) {
        addEdge(graph, vertexOne, vertexTwo);
    }
    //an edge is added vertexOne to vertexTwo and vertexTwo to vertexOne
    else {
        addEdge(graph, vertexOne, vertexTwo);
        addEdge(graph, vertexTwo, vertexOne);
    }
}

/*
 * The DFS() function does a depth first search of a graph and returns the length of the DFS.
 * The function is passed a pointer to the graph, and the vertex of the node to complete the DFS on.
 * https://www.programiz.com/dsa/graph-dfs
 */
int DFS(struct Graph *graph, int vertex) {
    struct node *adjacencyList = graph->adjacencyList[vertex];
    struct node *temp = adjacencyList;
    while(temp != NULL) {
        graph->visited[vertex] = 1;
        int connectedVertex = temp->vertex;
        //if the next node hasn't been visited return 1 + DFS() on the next node
        if(graph->visited[connectedVertex] == 0)
            return 1 + DFS(graph, connectedVertex);
        temp = temp->next;
    }
    return 0;
}

/*
 * The clearVisited() function resets the visited array of a graph to all 0's.
 * The function is passed a pointer to the graph.
 */
void clearVisited(struct Graph *graph) {
    int numVertices = graph->numVertices;
    for(int i = 0; i < numVertices; i++) {
        graph->visited[i] = 0;
    }
}

/*
 * The adjLength() function returns the length of the adjacency matrix at a specified vertex in a graph.
 * The function is passed a pointer to the graph and the vertex.
 */
int adjLength(struct Graph *graph, int vertex) {
    int length = 0;
    struct node *adjacencyList = graph->adjacencyList[vertex];
    struct node *temp = adjacencyList;
    //while there is another node in the adjacency list
    while(temp) {
        length++;
        temp = temp->next;
    }
    return length;
}