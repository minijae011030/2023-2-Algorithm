#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertices {
	int name;
	int distance;
	int inDegree;
	int outDegree;
}Vertices;

typedef struct Edge {
	int toIdx;
	int fromIdx;
	int weight;
}Edge;

typedef struct Graph {
	struct Vertices* vertices;
	struct Edge* edge;
	int verticeNum;
	int edgeNum;
	int startIdx;
}Graph;

Graph initGraph();
void BellmanFordAlg(Graph G, Vertices* startVertice);

int main() {
	Graph G = initGraph();

	BellmanFordAlg(G, &G.vertices[G.startIdx]);

	if (G.vertices[G.startIdx].outDegree != 0)
		for (int i = 0; i < G.verticeNum; i++)
			if (i != G.startIdx && G.vertices[i].distance != 20000)
				printf("%d %d\n", i + 1, G.vertices[i].distance);
}

Graph initGraph() {
	Graph G;
	scanf("%d %d %d", &G.verticeNum, &G.edgeNum, &G.startIdx);
	G.startIdx--;

	G.vertices = (Vertices*)malloc(sizeof(Vertices) * G.verticeNum);
	for (int i = 0; i < G.verticeNum; i++) {
		G.vertices[i].name = i + 1;
		G.vertices[i].inDegree = 0;
		G.vertices[i].outDegree = 0;
	}
		
	G.edge = (Edge*)malloc(sizeof(Edge) * G.edgeNum);
	for (int i = 0; i < G.edgeNum; i++) {
		int fromIdx, toIdx, weight;
		scanf("%d %d %d", &fromIdx, &toIdx, &weight);

		G.vertices[toIdx - 1].inDegree++;
		G.vertices[fromIdx - 1].outDegree++;

		G.edge[i].fromIdx = fromIdx - 1;
		G.edge[i].toIdx = toIdx - 1;
		G.edge[i].weight = weight;
	}

	return G;
}

void BellmanFordAlg(Graph G, Vertices* startVertice) {
	for (int i = 0; i < G.verticeNum; i++)
		G.vertices[i].distance = 20000;

	startVertice->distance = 0;

	for (int i = 0; i < G.verticeNum - 1; i++) {
		for (int j = 0; j < G.edgeNum; j++) {
			Vertices* u = &G.vertices[G.edge[j].fromIdx];
			Vertices* z = &G.vertices[G.edge[j].toIdx];

			int weight = G.edge[j].weight;
			int min = z->distance < u->distance + weight ? 
				z->distance : u->distance + weight;

			z->distance = min;
		}
	}
}