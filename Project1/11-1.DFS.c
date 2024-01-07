//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//
//typedef struct Vertices {
//    struct Incidence* inciList;
//    int num;
//    bool isFresh;   // true; fresh, false: visited
//}Vertices;
//
//typedef struct Incidence {
//    int edgeIndex;
//    struct Incidence* next;
//}Incidence;
//
//typedef struct Edge {
//    int v1;
//    int v2;
//    bool isFresh;       // true: fresh, false: visited
//    bool treeOrBack;    // true: tree, false: back
//}Edge;
//
//int n, m;
//
//Incidence* getInciList(int index);
//void insertEdge(int v1_num, int v2_num, Edge* edge, Vertices* vertices);
//void addIncidenceList(Edge* edge, Incidence* iH, int edgeIndex, int value, int insertValue); void printedge(int a_num, Vertices* v, Edge* e);
//
//void DFS(Vertices* vertice, Edge* edge, int startVertice);
//void rDFS(Vertices* vertice, Vertices* startVertice, Edge* edge);
//
//int main() {
//    int s;    // n: 정점의 개수, m: 간선의 개수, s: 순회 시작 정점 번호
//    scanf("%d %d %d", &n, &m, &s);
//
//    Vertices* vertice = (Vertices*)malloc(n * sizeof(Vertices));
//    Edge* edge = (Edge*)malloc(m * sizeof(Edge));
//
//    for (int i = 0; i < n; i++) {    // 노드 초기화
//        vertice[i].num = i + 1;
//        vertice[i].inciList = getInciList(-1);
//    }
//
//    for (int i = 0; i < m; i++) edge[i].v1 = edge[i].v2 = -1;   // 간선 리스트 초기화
//
//    int v1, v2;
//    for (int i = 0; i < m; i++) {  
//        scanf("%d %d", &v1, &v2);
//        insertEdge(v1, v2, edge, vertice);
//    }
//    
//    DFS(vertice, edge, s);
//    
//}
//
//Incidence* getInciList(int index) {
//    Incidence* newIncidenceList = (Incidence*)malloc(sizeof(Incidence));
//    newIncidenceList->edgeIndex = index;
//    newIncidenceList->next = NULL;
//
//    return newIncidenceList;
//}
//
//void addIncidenceList(Edge* edge, Incidence* iH, int edgeIndex, int value, int insertValue) {
//    /* 3-5 에서 3: value, 5: insertValue
//     3의 incidenceList에 3-5 edge 인덱스를 넣고싶은거임
//     3-1. 3-2, 3-4, 3-6 edge인덱스가 존재함
//     1, 2, 3등에 접근하는 방법 oppose vertice: edge->v1 == value ? v2 : v1 (루프는 고려 안함)
//     oppose vertice랑 insertvalue랑 비교해서 넣으면 됨*/
//
//    Incidence* newIncidence = getInciList(edgeIndex);
//    int opposeValue = 0;
//    while (iH->next != NULL) {
//        opposeValue = edge[iH->next->edgeIndex].v1 == value ? edge[iH->next->edgeIndex].v2 : edge[iH->next->edgeIndex].v1;
//        if (opposeValue > insertValue) break;
//        iH = iH->next;
//
//    }
//
//    newIncidence->next = iH->next;
//    iH->next = newIncidence;
//    return;
//}
//
//void insertEdge(int v1_num, int v2_num, Edge* edge, Vertices* vertices) {
//    if (v1_num > v2_num) {
//        int tmp = v1_num;
//        v1_num = v2_num;
//        v2_num = tmp;
//    }
//
//    // 노드 생성
//    Vertices v1 = { NULL, 0, true };
//    Vertices v2 = { NULL, 0, true };
//
//    // 노드 리스트에서 노드 찾기
//    for (int i = 0; i < n; i++) {
//        if (vertices[i].num == v1_num) v1 = vertices[i];
//        if (vertices[i].num == v2_num) v2 = vertices[i];
//    }
//
//    // 간선 추가
//    for (int i = 0; i < m; i++) {
//        if (edge[i].v1 == -1 && edge[i].v2 == -1) {
//            edge[i].v1 = v1_num;
//            edge[i].v2 = v2_num;
//
//            addIncidenceList(edge, v1.inciList, i, v1_num, v2_num);
//            if (v1_num != v2_num) addIncidenceList(edge, v2.inciList, i, v2_num, v1_num);
//            break;
//        }
//    }
//}
//
//void printedge(int a_num, Vertices* v, Edge* e) {
//    Incidence* iH = NULL;
//
//
//    for (int i = 0; i < n; i++) {
//        if (v[i].num == a_num) {
//            iH = v[i].inciList;
//            break;
//        }
//    }
//
//    while (iH->next != NULL) {
//        iH = iH->next;
//        int printnum = e[iH->edgeIndex].v1 == a_num ? e[iH->edgeIndex].v2 : e[iH->edgeIndex].v1;
//        printf("%d ", printnum);
//    }
//    printf("\n");
//}
//
//void DFS(Vertices* vertice, Edge* edge, int startVertice) {
//    for (int i = 0; i < n; i++) vertice[i].isFresh = true;
//    for (int i = 0; i < m; i++) edge[i].isFresh = true;
//
//    for (int i = startVertice - 1; i < n; i++) 
//        if (vertice[i].isFresh)
//        {
//            printf("%d\n", vertice[i].num);
//            rDFS(vertice, &vertice[i], edge);
//        }
//
//    for (int i = 0; i < startVertice - 1; i++) 
//        if (vertice[i].isFresh)
//        {
//            printf("%d\n", vertice[i].num);
//            rDFS(vertice, &vertice[i], edge);
//        }
//}
//
//void rDFS(Vertices* vertice, Vertices* startVertice, Edge* edge) {
//    startVertice->isFresh = false;
//    
//    Incidence* inciList = startVertice->inciList;
//
//    while (inciList->next != NULL) {
//        inciList = inciList->next;  
//        if (edge[inciList->edgeIndex].isFresh) {
//            edge[inciList->edgeIndex].isFresh = false;
//
//            int opposeNodeNum = startVertice->num == edge[inciList->edgeIndex].v1 ? edge[inciList->edgeIndex].v2 : edge[inciList->edgeIndex].v1;
//            Vertices* opposeVertice = NULL;
//            for (int i = 0; i < n; i++) if (opposeNodeNum == vertice[i].num) opposeVertice = &vertice[i];
//            
//            if (opposeVertice->isFresh) {
//                edge[inciList->edgeIndex].treeOrBack = true;
//                printf("%d\n", opposeVertice->num);
//                rDFS(vertice, opposeVertice, edge);
//            }
//            else edge[inciList->edgeIndex].treeOrBack = false;
//        }
//    }
//
//}
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Vertice {
	int name;
	bool isFresh;
	struct InciList* inciList;
}Vertice;

typedef struct InciList {
	struct InciList* next;
	int edgeIdx;
}InciList;

typedef struct Edge {
	int v1Idx;
	int v2Idx;
	bool isFresh;
}Edge;

typedef struct Graph {
	struct Vertice* vertice;
	struct Edge* edge;
	int verticeNum;
	int edgeNum;
	int startIdx;
}Graph;

Graph initGraph();
InciList* getInciList(int edgeIdx);
void addInciList(Graph G, int verticeIdx, int edgeIdx);

void DFS(Graph G);
void rDFS(Graph G, Vertice* w);

int main() {
	Graph G = initGraph();
	DFS(G);
}

Graph initGraph() {
	Graph G;
	scanf("%d %d %d", &G.verticeNum, &G.edgeNum, &G.startIdx);

	G.vertice = (Vertice*)malloc(sizeof(Vertice) * G.verticeNum);
	for (int i = 0; i < G.verticeNum; i++) {
		G.vertice[i].name = i + 1;
		G.vertice[i].isFresh = true;
		G.vertice[i].inciList = getInciList(-1);
	}

	G.edge = (Edge*)malloc(sizeof(Edge) * G.edgeNum);
	int v1, v2;
	for (int i = 0; i < G.edgeNum; i++) {
		scanf("%d %d", &v1, &v2);
		v1--;
		v2--;
		if (v1 > v2) {
			int tmp = v1;
			v1 = v2;
			v2 = tmp;
		}

		G.edge[i].v1Idx = v1;
		G.edge[i].v2Idx = v2;
		G.edge[i].isFresh = true;

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
	iH->next - newInci;
}

void DFS(Graph G) {
	for (int i = G.startIdx - 1; i < G.verticeNum; i++) {
		if (G.vertice[i].isFresh) {
			printf("%d\n", i + 1);
			rDFS(G, &G.vertice[i]);
		}
	}

	for (int i = 0; i < G.startIdx - 1; i++) {
		if (G.vertice[i].isFresh) {
			printf("%d\n", i + 1);
			rDFS(G, &G.vertice[i]);
		}
	}
}

void rDFS(Graph G, Vertice* w) {
	w->isFresh = false;

	InciList* iH = w->inciList;
	while (iH->next != NULL) {
		iH = iH->next;
		if (G.edge[iH->edgeIdx].isFresh) {
			G.edge[iH->edgeIdx].isFresh = false;
			Vertice* oppose = &G.vertice[G.edge[iH->edgeIdx].v1Idx];
			if (w == oppose) oppose = &G.vertice[G.edge[iH->edgeIdx].v2Idx];

			if (oppose->isFresh) {
				printf("%d\n", oppose->name);
				rDFS(G, oppose);
			}
		}
	}
}