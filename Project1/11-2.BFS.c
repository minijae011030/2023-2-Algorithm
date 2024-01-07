#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int n, m;

typedef struct Vertices {
	int node;
	bool isFresh;
}Vertices;

typedef struct Edge {
	int v1, v2;
	bool isFresh;
	bool treeOrCross;
}Edge;

void BFS(Vertices* vertice, Edge* edge, int* adjacencyMatrix, int startIdx);
void BFS1(Vertices* vertice, Vertices startVertice, Edge* edge, int** adjacencyMatrix);

int main() {
	int s;
	scanf("%d %d %d", &n, &m, &s);
	
	// ��� �ʱ�ȭ
	Vertices* vertice = (Vertices*)malloc(sizeof(Vertices) * n);
	for (int i = 0; i < n; i++) vertice[i].node = i + 1;

	// ���� �ʱ�ȭ
	Edge* edge = (Edge*)malloc(sizeof(Edge) * m);
	for (int i = 0; i < m; i++) edge[i].v1 = edge[i].v2 = -1;

	// ���� ��� �ʱ�ȭ
	int** adjacencyMatrix = (int**)malloc(sizeof(int*) * n);
	for (int i = 0; i < m; i++) adjacencyMatrix[i] = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			adjacencyMatrix[i][j] = -1;

	// ��� �Է¹ް� ���� �߰�
	int v1, v2;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &v1, &v2);

		v1--;
		v2--;
		edge[i].v1 = v1;
		edge[i].v2 = v2;

		adjacencyMatrix[v1][v2] = adjacencyMatrix[v2][v1] = i;
	}

	BFS(vertice, edge, adjacencyMatrix, s);

}

void BFS(Vertices* vertice, Edge* edge, int* adjacencyMatrix, int startIdx) {
	for (int i = 0; i < n; i++) vertice[i].isFresh = true;
	for (int i = 0; i < m; i++) edge[i].isFresh = true;
	startIdx--;

	for (int i = startIdx; i < n; i++)
		if (vertice[i].isFresh) {
			printf("%d\n", vertice[i].node);
			BFS1(vertice, vertice[i], edge, adjacencyMatrix);
		}

	for (int i = 0; i < startIdx; i++)
		if (vertice[i].isFresh) {
			printf("%d\n", vertice[i].node);
			BFS1(vertice, vertice[i], edge, adjacencyMatrix);
		}
}

void BFS1(Vertices* vertice, Vertices startVertice, Edge* edge, int** adjacencyMatrix) {
	/*
		adjacencyMatrix���� ������� ã��!!! -> opposeVertice ������ ����
		opposeVertice ��尡 fresh�̸�
		��� visited, ���� tree�� �ٲ�
		nextVerticeList�� ���� -> index�� newVerticeListLength
		newVerticeListLength + 1

		opposeVertice ��尡 visited�̸�
		���� cross�� �ٲ�

		verticeListLength = newVerticeListLength;
		verticeList = nextVertice;
		newVerticeListLength = 0;
	*/
	Vertices* verticeList = (Vertices*)malloc(sizeof(Vertices) * n);
	verticeList[0] = startVertice;
	int verticeListLength = 1;

	while (1) {
		if (verticeListLength == 0) return;

		Vertices* nextVerticeList = (Vertices*)malloc(sizeof(Vertices) * n);
		int newVerticeListLength = 0;

		for (int i = 0; i < verticeListLength; i++) {
			int matrixIdx = verticeList[i].node - 1;

			for (int j = 0; j < n; j++) {	// adjacencyMatrix i�� 0~n��° ��	
				if (adjacencyMatrix[matrixIdx][j] != -1) {	// ���� ��尡 ���� ��
					int edgeIdx = adjacencyMatrix[matrixIdx][j];	// ���� �ε��� ������ ����

					if (edge[edgeIdx].isFresh) {
						edge[edgeIdx].isFresh = false;
						int verticeIdx = verticeList[i].node - 1 == edge[edgeIdx].v1 ? edge[edgeIdx].v2 : edge[edgeIdx].v1;	// opposeVerticeIdx ���� ����
						Vertices* opposeVertice = &vertice[verticeIdx];

						if (opposeVertice->isFresh) {
							printf("%d\n", opposeVertice->node);
							opposeVertice->isFresh = false;
							edge[edgeIdx].treeOrCross = true;
							nextVerticeList[newVerticeListLength] = *opposeVertice;
							newVerticeListLength++;
						}
						else edge[edgeIdx].treeOrCross = false;
					}
				}

			}
		}
		verticeListLength = newVerticeListLength;
		verticeList = nextVerticeList;
	}
}
