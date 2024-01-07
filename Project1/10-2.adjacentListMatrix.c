#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Edge {
	int v1;
	int v2;
	int weight;
}Edge;

void insertEdge(int v1, int v2, Edge* edge, int arr[][6], int weight);
void modifyWeight(int v1, int v2, Edge* edge, int arr[][6], int weight);
void printEdge(Edge* edge, int arr[][6], int v);

int main() {
	int verticeArr[6];
	int adjacencyMatrix[6][6];
	Edge edge[21];
	
	// vertice 배열 초기화
	for (int i = 0; i < 6; i++) verticeArr[i] = i + 1;

	// adjacency matrix 초기화 (모두 -1)
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			adjacencyMatrix[i][j] = -1;

	//edge 구조체 배열을 초기 상태로 (모두 w = 0)
	int k = 0;
	for (int i = 1; i <= 6; i++) 
		for (int j = i; j <= 6; j++) {
			edge[k].v1 = i;
			edge[k].v2 = j;
			edge[k++].weight = 0;
		}

	insertEdge(1, 2, edge, adjacencyMatrix, 1);
	insertEdge(1, 3, edge, adjacencyMatrix, 1);
	insertEdge(1, 4, edge, adjacencyMatrix, 1);
	insertEdge(1, 6, edge, adjacencyMatrix, 2);
	insertEdge(2, 3, edge, adjacencyMatrix, 1);
	insertEdge(3, 5, edge, adjacencyMatrix, 4);
	insertEdge(5, 5, edge, adjacencyMatrix, 4);
	insertEdge(5, 6, edge, adjacencyMatrix, 3);

	while (1) {
		char a;
		scanf("%c", &a);
		if (a == 'q') break;
		else if (a == 'm') {
			int a, b, m;
			scanf("%d %d %d", &a, &b, &m);
			if ((a >= 1 && a <= 6) && (b >= 1 && b <= 6)) modifyWeight(a, b, edge, adjacencyMatrix, m);
			else printf("-1\n");
			
		}
		else if (a == 'a') {
			int a;
			scanf("%d", &a);
			if (a >= 1 && a <= 6) printEdge(edge, adjacencyMatrix, a);
			else printf("-1\n");
		}
		getchar();
	}
}

void insertEdge(int v1, int v2, Edge* edge, int arr[][6], int weight) {
	if (v1 > v2) {
		int tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
	int i = 0;
	for (i = 0; i < 21; i++) {
		if (edge[i].v1 == v1 && edge[i].v2 == v2) {
			edge[i].weight = weight;
			break;
		}
	}
	arr[v1 - 1][v2 - 1] = arr[v2 - 1][v1 - 1] = i;
}

void modifyWeight(int v1, int v2, Edge* edge, int arr[][6], int weight) {
	if (v1 > v2) {
		int tmp = v1;
		v1 = v2;
		v2 = tmp;
	}

	if (weight == 0) {
		// 삭제
		edge[arr[v1 - 1][v2 - 1]].weight = 0;
		arr[v1 - 1][v2 - 1] = arr[v2 - 1][v1 - 1] = -1;
	}
	else {
		// 추가, 변경
		int i = 0;
		for (i = 0; i < 21; i++) 
			if (edge[i].v1 == v1 && edge[i].v2 == v2) break;
		
		arr[v1 - 1][v2 - 1] = arr[v2 - 1][v1 - 1] = i;
		edge[i].weight = weight;
	}
}

void printEdge(Edge* edge, int arr[][6], int v) {
	for (int i = 0; i < 6; i++) {
		if (arr[v - 1][i] != -1) {
			int oppose = edge[arr[v - 1][i]].v1 == v ? edge[arr[v - 1][i]].v2 : edge[arr[v - 1][i]].v1;
			printf(" %d %d", oppose, edge[arr[v - 1][i]].weight);
		}
	}
	printf("\n");
}