//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Vertice {
//	char name;
//	int inDegree;	// 진입차수
//	struct InciList* toInciList;	// 진출간선리스트
//	struct InciList* fromInciList;	// 진입간선리스트
//}Vertice;
//
//typedef struct InciList {
//	struct InciList* next;
//	int edgeIdx;
//}InciList;
//
//typedef struct Edge {
//	int fromIdx;
//	int toIdx;
//}Edge;
//
//typedef struct Graph {
//	struct Vertice* vertice;
//	struct Edge* edge;
//	int verticeNum;
//	int edgeNum;
//}Graph;
//
//int index(Graph G, char VerticeName);
//
//Graph initGraph();
//InciList* getInciList(int edgeIdx);
//
//char* topologicalSort(Graph G);
//
//int main() {
//	Graph G = initGraph();
//
//	char* topOrder = topologicalSort(G);
//	if (topOrder[0] == 0) printf("0\n");
//	else {
//		for (int i = 0; i < G.verticeNum; i++)
//			printf("%c ", topOrder[i + 1]);
//		printf("\n");
//	}
//}
//
//int index(Graph G, char VerticeName) {
//	for (int i = 0; i < G.verticeNum; i++)
//		if (G.vertice[i].name == VerticeName)
//			return i;
//}
//
//Graph initGraph() {
//	Graph G;
//
//	scanf("%d", &G.verticeNum);
//	getchar();
//	G.vertice = (Vertice*)malloc(sizeof(Vertice) * G.verticeNum);
//
//	for (int i = 0; i < G.verticeNum; i++) {
//		scanf("%c", &G.vertice[i].name);
//		getchar();
//
//		G.vertice[i].fromInciList = getInciList(-1);
//		G.vertice[i].toInciList = getInciList(-1);
//		G.vertice[i].inDegree = 0;
//	}
//
//	scanf("%d", &G.edgeNum);
//	getchar();
//
//	G.edge = (Edge*)malloc(sizeof(Edge) * G.edgeNum);
//
//	char v1Num, v2Num;
//	for (int i = 0; i < G.edgeNum; i++) {
//		scanf("%c %c", &v1Num, &v2Num);
//		getchar();
//
//		int v1Idx = index(G, v1Num);
//		int v2Idx = index(G, v2Num);
//
//		G.edge[i].fromIdx = v1Idx;
//		G.edge[i].toIdx = v2Idx;
//
//		G.vertice[v2Idx].inDegree++;
//
//		InciList* v1InciList = G.vertice[v1Idx].toInciList;
//		InciList* v2InciList = G.vertice[v2Idx].fromInciList;
//
//		InciList* newNode1 = getInciList(i);
//		InciList* newNode2 = getInciList(i);
//
//		newNode1->next = v1InciList->next;
//		v1InciList->next = newNode1;
//
//		newNode2->next = v2InciList->next;
//		v2InciList->next = newNode2;
//	}
//
//	return G;
//}
//
//InciList* getInciList(int edgeIdx) {
//	InciList* newNode = (InciList*)malloc(sizeof(InciList));
//	newNode->edgeIdx = edgeIdx;
//	newNode->next = NULL;
//
//	return newNode;
//}
//
//char* topologicalSort(Graph G) {
//	Vertice* Q[100];
//
//	int startIdx = 0, endIdx = 0;
//	for (int i = 0; i < G.verticeNum; i++)
//		if (G.vertice[i].inDegree == 0)
//			Q[endIdx++] = &G.vertice[i];
//
//	int order = 1;
//	char* topological = (char*)malloc(sizeof(char) * (G.verticeNum + 1));
//	
//	while (startIdx != endIdx) {
//		Vertice* u = Q[startIdx++];	// dequeue;
//		topological[order++] = u->name;
//
//		InciList* toInci = u->toInciList;
//		while (toInci->next != NULL) {
//			toInci = toInci->next;
//			Vertice* w = &G.vertice[G.edge[toInci->edgeIdx].toIdx];
//
//			if (--w->inDegree == 0)
//				Q[endIdx++] = w;
//		}
//	}
//
//	if (order <= G.verticeNum) topological[0] = 0;
//	else topological[0] = 1;
//
//	return topological;
//}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

typedef struct Vertice {
	char name;
	int inDegree;
	struct InciList* fromInciList;	// 진입 간선
	struct InciList* toInciList; //	진출간선
}Vertice;

typedef struct InciList {
	int edgeIdx;
	struct InciList* next;
}InciList;

typedef struct Edge {
	int fromIdx;
	int toIdx;
}Edge;

typedef struct Graph {
	struct Vertice* vertice;
	struct Edge* edge;
	int verticeNum;
	int edgeNum;
}Graph;

Graph initGraph();
InciList* getInciList(int edgeIdx);
int index(Graph G, char vName);

char* topologicalSort(Graph G);

int main() {
	Graph G = initGraph();
	char* topOrder = topologicalSort(G);

	if (topOrder[0] == 0) printf("0");
	else
		for (int i = 0; i < G.verticeNum; i++)
			printf("%c ", topOrder[i + 1]);
}

Graph initGraph() {
	Graph G;

	scanf("%d", &G.verticeNum);
	G.vertice = (Vertice*)malloc(sizeof(Vertice) * G.verticeNum);
	getchar();

	for (int i = 0; i < G.verticeNum; i++) {
		scanf("%c", &G.vertice[i].name);
		getchar();
		G.vertice[i].fromInciList = getInciList(-1);
		G.vertice[i].toInciList = getInciList(-1);
		G.vertice[i].inDegree = 0;
	}

	scanf("%d", &G.edgeNum);
	getchar();
	G.edge = (Edge*)malloc(sizeof(Edge) * G.edgeNum);
	char v1, v2;
	for (int i = 0; i < G.edgeNum; i++) {
		scanf("%c %c", &v1, &v2);
		getchar();
		int v1Idx = index(G, v1);
		int v2Idx = index(G, v2);

		G.edge[i].fromIdx = v1Idx;
		G.edge[i].toIdx = v2Idx;

		InciList* v1Inci = getInciList(i);
		InciList* v2Inci = getInciList(i);

		InciList* v1IH = G.vertice[v1Idx].toInciList;
		InciList* v2IH = G.vertice[v2Idx].fromInciList;

		v1Inci->next = v1IH->next;
		v1IH->next = v1Inci;

		v2Inci->next = v2IH->next;
		v2IH->next = v2Inci;

		G.vertice[v2Idx].inDegree++;
	}

	return G;
}

InciList* getInciList(int edgeIdx) {
	InciList* newInci = (InciList*)malloc(sizeof(InciList));
	newInci->edgeIdx = edgeIdx;
	newInci->next = NULL;

	return newInci;
}

int index(Graph G, char vName) {
	for (int i = 0; i < G.verticeNum; i++) 
		if (vName == G.vertice[i].name)
			return i;
}

char* topologicalSort(Graph G) {
	Vertice* Q[100];
	char* topOrder = (char*)malloc(sizeof(char) * (G.verticeNum + 1));
	int order = 1;

	int startIdx = 0, endIdx = 0;
	for (int i = 0; i < G.verticeNum; i++) {
		if (G.vertice[i].inDegree == 0) {
			Q[endIdx++] = &G.vertice[i];
		}
	}

	while (startIdx != endIdx) {
		Vertice* u = Q[startIdx++];	// dequeue
		topOrder[order++] = u->name;

		InciList* iH = u->toInciList;

		while (iH->next != NULL) {
			iH = iH->next;
			Vertice* w = &G.vertice[G.edge[iH->edgeIdx].toIdx];
			if (--w->inDegree == 0) {
				Q[endIdx++] = w;
			}
		}
	}

	if (order <= G.verticeNum) topOrder[0] = 0;
	else topOrder[0] = 1;

	return topOrder;
}