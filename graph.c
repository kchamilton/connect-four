//
// Created by Kayla Hamilton on 3/13/2019.
//

#include "graph.h"
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>


struct node {
    int vertex;
    char player;
    struct node* next;
};

struct node *createNode(int num) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = num;
    newNode->player = ' ';
    newNode->next = NULL;
    return newNode;
}

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

void freeAdjacencyList(struct Graph *graph, int vertex) {
    while(graph->adjacencyList[vertex] != NULL) {
        struct node *temp;
        temp = graph->adjacencyList[vertex];
        graph->adjacencyList[vertex] = temp->next;
    }
}

void freeGraph(struct Graph *graph) {
    free(graph->visited);
    for(int i = 0; i < graph->numVertices; i++) {
        freeAdjacencyList(graph, i);
    }
    free(graph->adjacencyList);
    free(graph);
}

//add edge between vertex one and two - only vertex one points to two, two doesn't point to one
void addEdge(struct Graph *graph, int vertexOne, int vertexTwo, char playerNum) {
    struct node *newNode = createNode(vertexTwo);
    newNode->player = playerNum;
    newNode->next = graph->adjacencyList[vertexOne];
    graph->adjacencyList[vertexOne] = newNode;
}

void updateEdge(struct Graph *graph, int vertexOne, int vertexTwo, char PlayerNum, int edgeToAdd) {
    if(edgeToAdd == 1) {
        addEdge(graph, vertexOne, vertexTwo, PlayerNum);
    }
    else {
        addEdge(graph, vertexOne, vertexTwo, PlayerNum);
        addEdge(graph, vertexTwo, vertexOne, PlayerNum);
    }
}

int DFS(struct Graph *graph, int vertex) {
    struct node *adjacencyList = graph->adjacencyList[vertex];
    struct node *temp = adjacencyList;
    while(temp != NULL) {
        graph->visited[vertex] = 1;
        int connectedVertex = temp->vertex;
        if(graph->visited[connectedVertex] == 0)
            return 1 + DFS(graph, connectedVertex);
        temp = temp->next;
    }
    return 0;
}

void clearVisited(struct Graph *graph) {
    int numVertices = graph->numVertices;
    for(int i = 0; i < numVertices; i++) {
        graph->visited[i] = 0;
    }
}

int adjLength(struct Graph *graph, int vertex) {
    int length = 0;
    struct node *adjacencyList = graph->adjacencyList[vertex];
    struct node *temp = adjacencyList;
    while(temp) {
        length++;
        temp = temp->next;
    }
    return length;
}