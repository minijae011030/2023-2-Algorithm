#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INFINITY INT_MAX

typedef struct Graph {
	struct Vertices* Vertices;
	struct Edge* Edge;
	int verticeNum;
	int edgeNum;
	int startIdx;
}Graph;

typedef struct Vertices {
	int num;
	struct IncidenceList* incidenceList;
	int distance;
}Vertices;

typedef struct Edge {
	int v1Idx;
	int v2Idx;
	int weight;
}Edge;

typedef struct IncidenceList {
	struct IncidenceList* next;
	int edgeIdx;
}IncidenceList;


Graph initGraph();
IncidenceList* getIncidenceList(int idx);
void addIncidenceNode(Graph G, int verticeNum, int edgeIdx);
void insertEdge(Graph G, int i, int v1, int v2, int weight);

void Dijkstra(Graph G);
Vertices* removeMin(Vertices** Q, int n);

int main() {
	Graph G = initGraph();
	Dijkstra(G);

	// distance �ۿ��� ���
	for (int i = 0; i < G.verticeNum; i++)
		if (i != G.startIdx && G.Vertices[i].distance != 30000)
			printf("%d %d\n", i + 1, G.Vertices[i].distance);
}

Graph initGraph() {
	Graph G;
	scanf("%d %d %d", &G.verticeNum, &G.edgeNum, &G.startIdx);
	G.startIdx--;

	G.Vertices = (Vertices*)malloc(sizeof(Vertices) * G.verticeNum);
	G.Edge = (Edge*)malloc(sizeof(Edge) * G.edgeNum);

	for (int i = 0; i < G.verticeNum; i++) {
		G.Vertices[i].num = i + 1;
		G.Vertices[i].incidenceList = getIncidenceList(-1);
	}

	for (int i = 0; i < G.edgeNum; i++) {
		int v1, v2, weight;
		scanf("%d %d %d", &v1, &v2, &weight);

		insertEdge(G, i, v1, v2, weight);
	}

	return G;
}

void insertEdge(Graph G, int i, int v1, int v2, int weight) {
	if (v1 > v2) {
		int tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
	G.Edge[i].v1Idx = v1 - 1;
	G.Edge[i].v2Idx = v2 - 1;
	G.Edge[i].weight = weight;

	addIncidenceNode(G, v1, i);
	if (v1 != v2) addIncidenceNode(G, v2, i);
}

IncidenceList* getIncidenceList(int idx) {
	IncidenceList* newInciNode = (IncidenceList*)malloc(sizeof(IncidenceList));
	newInciNode->edgeIdx = idx;
	newInciNode->next = NULL;

	return newInciNode;
}

void addIncidenceNode(Graph G, int verticeNum, int edgeIdx) {
	IncidenceList* incidenceHead = G.Vertices[verticeNum - 1].incidenceList;

	IncidenceList* newInciNode = getIncidenceList(edgeIdx);
	newInciNode->next = incidenceHead->next;
	incidenceHead->next = newInciNode;
}

void Dijkstra(Graph G) {
	// ������ ������ ������� ����
	int n = 0;
	for (int i = 0; i < G.verticeNum; i++)
		if (G.Vertices[i].incidenceList->next != NULL) n++;

	// ������带 ���� ť �����
	Vertices** Q = (Vertices**)malloc(sizeof(Vertices*) * n);

	// distance �������� �ϰ� ť�� �ֱ�
	int idx = 0;
	for (int i = 0; i < G.verticeNum; i++) {
		G.Vertices[i].distance = 30000;
		if (G.Vertices[i].incidenceList->next != NULL) {
			Q[idx] = &G.Vertices[i];
			idx++;
		}
	}

	// ���� ���� distance 0���� �ʱ�ȭ
	G.Vertices[G.startIdx].distance = 0;

	// ť�� �� ������ �ݺ�
	while (n > 0) {
		// distance�� ���� ���� ���� ����
		Vertices* u = removeMin(Q, n);
		n--;

		// �� ������ �����鿡 ���� �ݺ��� ����
		IncidenceList* inciNode = u->incidenceList->next;
		while (inciNode != NULL) {
			// �ݴ� ���� ã��
			int zN = G.Edge[inciNode->edgeIdx].v2Idx;
			if (zN == u->num - 1) zN = G.Edge[inciNode->edgeIdx].v1Idx;

			Vertices* z = &G.Vertices[zN];
			int weight = G.Edge[inciNode->edgeIdx].weight;

			// ť�� �����ϸ鼭 ������ �����ϸ� �ٲٱ�
			for (int i = 0; i < n; i++)
				if (z == Q[i])
					if (u->distance + weight < z->distance) 
						z->distance = u->distance + weight;

			inciNode = inciNode->next;
		}
	}

	free(Q);
}

Vertices* removeMin(Vertices** Q, int n) {
	int minDistance = 30000;
	int idx = -1;

	for (int i = 0; i < n; i++) {
		if ((*Q[i]).distance < minDistance) {
			minDistance = (*Q[i]).distance;
			idx = i;
		}
	}

	Vertices* tmp = Q[n - 1];
	Q[n - 1] = Q[idx];
	Q[idx] = tmp;
	return Q[n - 1];
}
