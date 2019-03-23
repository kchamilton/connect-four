//
// Created by Kayla Hamilton on 3/13/2019.
//

#ifndef CONNECT_FOUR_GRAPH_H
#define CONNECT_FOUR_GRAPH_H

struct Graph {
    int numVertices;
    int *visited;
    struct node **adjacencyList;
};

struct Graph *createGraph(int num);
void freeAdjacencyList(struct Graph *graph, int vertex);
void freeGraph(struct Graph *graph);
void updateEdge(struct Graph *graph, int vertexOne, int vertexTwo, char PlayerNum, int edgeToAdd);
int DFS(struct Graph *graph, int vertex);
void clearVisited(struct Graph *graph);
int adjLength(struct Graph *graph, int vertex);

#endif //CONNECT_FOUR_GRAPH_H
