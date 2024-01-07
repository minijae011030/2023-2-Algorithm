//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Vertice {
//	int name;
//	struct InciList* inciList;
//	int distance;
//	int parentVerticeIdx;
//}Vertice;
//
//typedef struct InciList {
//	struct InciList* next;
//	int edgeIdx;
//}InciList;
//
//typedef struct Edge {
//	int v1Idx;
//	int v2Idx;
//	int weight;
//}Edge;
//
//typedef struct Graph {
//	struct Vertice* vertice;
//	struct Edge* edge;
//	int verticeNum;
//	int edgeNum;
//}Graph;
//
//Graph initGraph();
//InciList* getInciList(int edgeIdx);
//void addInciList(Graph G, int verticeNum, int edgeIdx);
//
//void PrimJarnik(Graph G);
//Vertice* removeMin(Vertice** Q, int n);
//
//int main() {
//	Graph G = initGraph();
//	PrimJarnik(G);
//}
//
//Graph initGraph() {
//	Graph G;
//	scanf("%d %d", &G.verticeNum, &G.edgeNum);
//	G.vertice = (Vertice*)malloc(sizeof(Vertice) * G.verticeNum);
//	G.edge = (Edge*)malloc(sizeof(Edge) * G.edgeNum);
//
//	for (int i = 0; i < G.verticeNum; i++) {
//		G.vertice[i].name = i + 1;
//		G.vertice[i].inciList = getInciList(-1);
//	}
//
//	for (int i = 0; i < G.edgeNum; i++) {
//		int v1Idx, v2Idx, weight;
//		scanf("%d %d %d", &v1Idx, &v2Idx, &weight);
//		v1Idx--;
//		v2Idx--;
//		if (v1Idx > v2Idx) {
//			int tmp = v1Idx;
//			v1Idx = v2Idx;
//			v2Idx = tmp;
//		}
//
//		G.edge[i].v1Idx = v1Idx;
//		G.edge[i].v2Idx = v2Idx;
//		G.edge[i].weight = weight;
//
//		addInciList(G, v1Idx, i);
//		if (v1Idx != v2Idx) addInciList(G, v2Idx, i);
//	
//	}
//	return G;
//}
//
//InciList* getInciList(int edgeIdx) {
//	InciList* newInci = (InciList*)malloc(sizeof(InciList));
//	newInci->edgeIdx = edgeIdx;
//	newInci->next = NULL;
//
//	return newInci;
//}
//
//void addInciList(Graph G, int verticeNum, int edgeIdx) {
//	InciList* newInci = getInciList(edgeIdx);
//
//	InciList* iH = G.vertice[verticeNum].inciList;
//	newInci->next = iH->next;
//	iH->next = newInci;
//}
//
//void PrimJarnik(Graph G) {
//	int totalWeight = 0;
//
//	// 모든 정점에 대해 distance 무한, parentV = null로 초기화
//	for (int i = 0; i < G.verticeNum; i++) {
//		G.vertice[i].distance = 300000;
//		G.vertice[i].parentVerticeIdx = -1;
//	}
//
//	// 시작정점 distance 0으로 설정
//	G.vertice[0].distance = 0;
//
//	// 큐에 모든 정점 넣기
//	Vertice** Q = (Vertice**)malloc(sizeof(Vertice*) * G.verticeNum);
//
//	for (int i = 0; i < G.verticeNum; i++) Q[i] = &G.vertice[i];
//
//	// 큐가 빌 때까지
//	int n = G.verticeNum;
//	while (n > 0) {
//		// distance가 가장 작은 정점 빼기
//		Vertice* u = removeMin(Q, n);
//		
//		// 출력하고 totalWeight에 distance 더하기
//		printf(" %d", u->name);
//		totalWeight += u->distance;
//		n--;
//
//		// 정점의 모든 간선에 대해
//		InciList* uInciList = u->inciList;
//		while (uInciList->next != NULL) {
//			uInciList = uInciList->next;
//			// 반대 정점
//			Vertice* oppose = &G.vertice[G.edge[uInciList->edgeIdx].v1Idx];
//			if (oppose == u) oppose = &G.vertice[G.edge[uInciList->edgeIdx].v2Idx];
//
//			// 반대정점의 distance가 간선의 weight보다 작으면 변경
//			int weight = G.edge[uInciList->edgeIdx].weight;
//			if (oppose->distance > weight) {
//				oppose->distance = weight;
//				oppose->parentVerticeIdx = uInciList->edgeIdx;
//			}
//		}
//	}
//	printf("\n%d", totalWeight);
//}
//
//Vertice* removeMin(Vertice** Q, int n) {
//	int minDistance = 30000;
//	int minIdx = -1;
//
//	for (int i = 0; i < n; i++) {
//		if ((*Q[i]).distance < minDistance) {
//			minDistance = (*Q[i]).distance;
//			minIdx = i;
//		}
//	}
//
//	Vertice* tmp = Q[n - 1];
//	Q[n - 1] = Q[minIdx];
//	Q[minIdx] = tmp;
//
//	return Q[n - 1];
//}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Vertice {
	int name;
	struct InciList* inciList;
	int distance;
	int parentIdx;
}Vertice;

typedef struct InciList {
	int edgeIdx;
	struct InciList* next;
}InciList;

typedef struct Edge {
	int v1Idx;
	int v2Idx;
	int weight;
}Edge;

typedef struct Graph {
	struct Vertice* vertice;
	struct Edge* edge;
	int verticeNum;
	int edgeNum;
}Graph;

Graph initGraph();
InciList* getInciList(int edgeIdx);
void addInciList(Graph G, int verticeIdx, int edgeIdx);

void PrimJarnik(Graph G);
Vertice* removeMin(Vertice** Q, int n);

int main() {
	Graph G = initGraph();
	PrimJarnik(G);
}

Graph initGraph() {
	Graph G;

	scanf("%d %d", &G.verticeNum, &G.edgeNum);
	G.vertice = (Vertice*)malloc(sizeof(Vertice) * G.verticeNum);
	for (int i = 0; i < G.verticeNum; i++) {
		G.vertice[i].name = i + 1;
		G.vertice[i].inciList = getInciList(-1);
	}

	G.edge = (Edge*)malloc(sizeof(Edge) * G.edgeNum);
	int v1, v2, weight;
	for (int i = 0; i < G.edgeNum; i++) {
		scanf("%d %d %d", &v1, &v2, &weight);
		v1--;
		v2--;

		if (v1 > v2) {
			int tmp = v1;
			v1 = v2;
			v2 = tmp;
		}

		G.edge[i].v1Idx = v1;
		G.edge[i].v2Idx = v2;
		G.edge[i].weight = weight;

		addInciList(G, v1, i);
		if (v1 != v2) addInciList(G, v2, i);
	}

	return G;
}

InciList* getInciList(int edgeIdx) {
	InciList* newInci = (InciList*)malloc(sizeof(InciList));
	newInci->edgeIdx = edgeIdx;
	newInci->next = NULL;

	return newInci;
}

void addInciList(Graph G, int verticeIdx, int edgeIdx) {
	InciList* iH = G.vertice[verticeIdx].inciList;
	InciList* newInci = getInciList(edgeIdx);

	newInci->next = iH->next;
	iH->next = newInci;
}

void PrimJarnik(Graph G) {
	int totalWeight = 0;

	for (int i = 0; i < G.verticeNum; i++) {
		G.vertice[i].distance = 30000;
		G.vertice[i].parentIdx = -1;
	}

	G.vertice[0].distance = 0;

	Vertice** Q = (Vertice**)malloc(sizeof(Vertice*) * G.verticeNum);
	for (int i = 0; i < G.verticeNum; i++) 
		Q[i] = &G.vertice[i];


	int n = G.verticeNum;
	while (n > 0) {
		Vertice* u = removeMin(Q, n);
		printf(" %d", u->name);
		totalWeight += u->distance;
		n--;

		InciList* iH = u->inciList;
		while (iH->next != NULL) {
			iH = iH->next;
			Vertice* oppose = &G.vertice[G.edge[iH->edgeIdx].v1Idx];
			if (u == oppose) oppose = &G.vertice[G.edge[iH->edgeIdx].v2Idx];
			int weight = G.edge[iH->edgeIdx].weight;
			if (oppose->distance > weight) {
				oppose->distance = weight;
				oppose->parentIdx = u->name - 1;
			}
		}
	}

	printf("\n%d", totalWeight);
	
}

Vertice* removeMin(Vertice** Q, int n) {
	int minDistance = 30000;
	int idx = -1;

	for (int i = 0; i < n; i++) {
		if (minDistance > (*Q[i]).distance) {
			minDistance = (*Q[i]).distance;
			idx = i;
		}
	}

	Vertice* tmp = Q[n - 1];
	Q[n - 1] = Q[idx];
	Q[idx] = tmp;

	return Q[n - 1];
}