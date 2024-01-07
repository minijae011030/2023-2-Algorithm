//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//
//typedef struct Vertice {
//	struct IncidenceList* incidenceListHead;
//	int node;
//}Vertice;
//
//typedef struct IncidenceList {
//	struct IncidenceList* next;
//	int edgeIdx;
//}IncidenceList;
//
//typedef struct Edge {
//	int prevVertice;
//	int nextVertice;
//	int weight;
//}Edge;
//
//typedef struct List {
//	int weight;
//	int node;
//}List;
//
//Edge* setEdge(Edge* edge, int weight, Vertice* v1, Vertice* v2);
//void addIncidenceList(Edge* edge, Vertice* v1, Vertice* v2);
//void searchIncidenceNode(Edge* edge, Vertice* vertice);
//void swapLists(List* a, List* b);
//void modifyNode(Vertice* vertice, Edge* edge, int v1, int n2, int weight);
//
//int main() {
//	Vertice vertice[7];
//	Edge edge[21];
//
//	for (int i = 0; i < 21; i++) edge[i].weight = 0;
//	
//
//	for (int i = 1; i < 7; i++) {
//		vertice[i].node = i;
//
//		IncidenceList* incidencelist = (IncidenceList*)malloc(sizeof(IncidenceList));
//		incidencelist->next = NULL;
//
//		vertice[i].incidenceListHead = incidencelist;
//	}
//
//	edge[0] = *setEdge(&edge[0], 1, &vertice[1], &vertice[2]);
//	addIncidenceList(&edge[0], &vertice[1], &vertice[2]);
//
//	edge[1] = *setEdge(&edge[1], 1, &vertice[1], &vertice[3]);
//	addIncidenceList(&edge[0], &vertice[1], &vertice[3]);
//
//	edge[2] = *setEdge(&edge[2], 1, &vertice[1], &vertice[4]);
//	addIncidenceList(&edge[0], &vertice[1], &vertice[4]);
//
//	edge[3] = *setEdge(&edge[3], 2, &vertice[1], &vertice[6]);
//	addIncidenceList(&edge[0], &vertice[1], &vertice[6]);
//
//	edge[4] = *setEdge(&edge[4], 1, &vertice[2], &vertice[3]);
//	addIncidenceList(&edge[0], &vertice[2], &vertice[3]);
//
//	edge[5] = *setEdge(&edge[5], 4, &vertice[3], &vertice[5]);
//	addIncidenceList(&edge[0], &vertice[3], &vertice[5]);
//
//	edge[6] = *setEdge(&edge[6], 4, &vertice[5], &vertice[5]);
//	addIncidenceList(&edge[0], &vertice[5], &vertice[5]);
//
//	edge[7] = *setEdge(&edge[7], 3, &vertice[5], &vertice[6]);
//	addIncidenceList(&edge[0], &vertice[5], &vertice[6]);
//
//	//////////////////////////////////////////////////////////
//
//	char cmd;
//	int node;
//	int n1, n2, newWeight;
//
//	while (1) {
//		scanf("%c", &cmd);
//		switch (cmd)
//		{
//		case 'q':
//			return;
//		case 'a':
//			scanf("%d", &node);
//			if (node >= 1 && node <= 6) searchIncidenceNode(&edge[0], &vertice[node]);
//			else printf("-1");
//			printf("\n");
//			break;
//		case 'm':
//			scanf("%d %d %d", &n1, &n2, &newWeight);
//			if ((n1 >= 1 && n1 <= 6) && (n2 >= 1 && n2 <= 6)) modifyNode(&vertice[0], &edge[0], n1, n2, newWeight);
//			else printf("-1\n");
//			break;
//		default:
//			break;
//		}
//	}
//}
//
//Edge* setEdge(Edge* edge, int weight, Vertice* v1, Vertice* v2) {
//	edge->prevVertice = v1->node;
//	edge->nextVertice = v2->node;
//
//	edge->weight = weight;
//	return edge;
//}
//
//void addIncidenceList(Edge* edge, Vertice* v1, Vertice* v2) {
//	// 인접 리스트에 노드를 추가하는 함수
//	IncidenceList* p = v1->incidenceListHead;	// v1의 인접리스트 헤드
//	IncidenceList* q = v2->incidenceListHead;	// v2의 인접리스트 헤드
//
//	int edgeIdx = 0;
//	for (int i = 0; i < 21; i++) {	// 간선 리스트의 마지막에 도달할 때까지 반복문 실행
//		if (edge[i].weight == 0) {
//			break;
//		}
//		edgeIdx++;
//	}
//	edgeIdx--;
//
//	IncidenceList* newIncidenceList1 = (IncidenceList*)malloc(sizeof(IncidenceList));
//	IncidenceList* newIncidenceList2 = (IncidenceList*)malloc(sizeof(IncidenceList));
//
//	// 새로운 인접 리스트 노드 생성
//	newIncidenceList1->edgeIdx = newIncidenceList2->edgeIdx = edgeIdx;	// 인접 리스트 노드의 간선 인덱스 설정
//	newIncidenceList1->next = newIncidenceList2->next = NULL;	// 인접 리스트 노드의 다음 노드 설정
//
//	// 인접 리스트 v1의 마지막까지 이동
//	while (p->next != NULL) p = p->next;
//	while (q->next != NULL) q = q->next;
//	p->next = newIncidenceList1;	// 리스트 마지막에 새 인접 리스트 노드 삽입
//	if (v1 != v2) q->next = newIncidenceList2;	// 루프가 아닌 경우
//}
//
//void searchIncidenceNode(Edge* edge, Vertice* vertice) {
//	// 노드 번호의 오름차순으로 인접노드, 가중치 쌍을 순서대로 출력하는 함수
//	IncidenceList* p = vertice->incidenceListHead->next;
//	List list[6];
//	for (int i = 0; i < 6; i++) {
//		list[i].node = 0;
//		list[i].weight = 0;
//	}
//	int i = 0;
//	while (1) {	// 인접리스트의 마지막에 도달할 때까지 반복문 실행
//		if (p == NULL) break;
//
//		// 입력된 노드와 같지 않은 노드, 가중치를 출력
//		if (edge[p->edgeIdx].prevVertice != vertice->node) {
//			list[i].node = edge[p->edgeIdx].prevVertice;
//			list[i].weight = edge[p->edgeIdx].weight;
//
//			i++;
//		}
//		if (edge[p->edgeIdx].nextVertice != vertice->node) {
//			list[i].node = edge[p->edgeIdx].nextVertice;
//			list[i].weight = edge[p->edgeIdx].weight;
//
//			i++;
//		}
//
//		// 루프인 경우
//		if (edge[p->edgeIdx].prevVertice == edge[p->edgeIdx].nextVertice) {
//			list[i].node = edge[p->edgeIdx].prevVertice;
//			list[i].weight = edge[p->edgeIdx].weight;
//			i++;
//		}
//
//		p = p->next;	// 다음 인접 노드로 이동
//	}
//
//	for (int i = 0; i < 5; i++) {
//		for (int j = 0; j < 5 - i; j++) {
//			if (list[j].node > list[j + 1].node) {
//				swapLists(&list[j], &list[j + 1]);
//			}
//		}
//	}
//
//	for (int i = 0; i < 6; i++) {
//		if (list[i].node != 0) {
//			printf(" %d %d", list[i].node, list[i].weight);
//		}
//	}
//}
//
//void swapLists(List* a, List* b) {
//	List temp = *a;
//	*a = *b;
//	*b = temp;
//}
//
//void modifyNode(Vertice* vertice, Edge* edge, int v1, int v2, int weight) {
//	// 간선을 추가, 삭제하고 가중치를 수정하는 함수
//
//	// 간선 삭제
//	if (weight == 0){
//		// 인접 리스트 노드 삭제
//		// vertice 찾기
//		Vertice* vertice1 = NULL, * vertice2 = NULL;
//		for (int i = 0; i < 8; i++) {
//			if (vertice[i].node == v1) vertice1 = &vertice[i];
//			if (vertice[i].node == v2) vertice2 = &vertice[i];
//		}
//		// vertice의 incidence list 헤드 접근
//		IncidenceList* v1Incidence = vertice1->incidenceListHead;
//		IncidenceList* v2Incidence = vertice2->incidenceListHead;
//
//		// 삭제하려는 노드 접근
//		while (1) {
//			if (edge[v1Incidence->next->edgeIdx].prevVertice == v1 && edge[v1Incidence->next->edgeIdx].nextVertice == v2) break;
//			if (v1Incidence->next == NULL) return;
//			v1Incidence = v1Incidence->next;
//		}
//
//		while (1) {
//			if (edge[v2Incidence->next->edgeIdx].prevVertice == v1 && edge[v2Incidence->next->edgeIdx].nextVertice == v2) break;
//			if (v2Incidence->next == NULL) return;
//			v2Incidence = v2Incidence->next;
//		}
//
//		// vertice1 인접리스트 삭제
//		// 삭제하려는 incidence node가 맨 뒤인 경우
//		if (v1Incidence->next->next == NULL) v1Incidence->next = NULL;
//		// 삭제하려는 incidence node가 맨 뒤가 아닌 경우
//		else v1Incidence->next = v1Incidence->next->next;
//
//		if (vertice1 != vertice2) {
//			// vertice2 인접리스트 삭제
//			// 삭제하려는 incidence node가 맨 뒤인 경우
//			if (v2Incidence->next->next == NULL) v2Incidence->next = NULL;
//			// 삭제하려는 incidence node가 맨 뒤가 아닌 경우
//			else v2Incidence->next = v2Incidence->next->next;
//		}
//	}
//	else {
//		// 가중치 수정
//		int idx = 0;
//		for (int i = 0; i < 21; i++) {
//			if (edge[i].weight == 0) {
//				idx = i;
//				break;
//			}
//
//			if (edge[i].prevVertice == v1 && edge[i].nextVertice == v2) {
//				edge[i].weight = weight;
//				return;
//			}
//			else if (edge[i].prevVertice == v2 && edge[i].nextVertice == v1) {
//				edge[i].weight = weight;
//				return;
//			}
//		}
//
//		// 간선 추가
//		// vertices 리스트에서 찾기
//		Vertice* vertice1 = NULL, * vertice2 = NULL;
//		int vertice1Idx, vertice2Idx;
//		for (int i = 0; i < 8; i++) {
//			if (vertice[i].node == v1) {
//				vertice1 = &vertice[i];
//				vertice1Idx = i;
//			}
//			if (vertice[i].node == v2) { 
//				vertice2 = &vertice[i]; 
//				vertice2Idx = i; 
//			}
//		}
//
//		// edge 추가
//		edge[idx].prevVertice = vertice1Idx;
//		edge[idx].nextVertice = vertice2Idx;
//		edge[idx].weight = weight;
//
//		// incidence list 추가
//		IncidenceList* vertice1IncidenceNode = vertice1->incidenceListHead;
//		IncidenceList* vertice2IncidenceNode = vertice2->incidenceListHead;
//		
//		IncidenceList* newv1 = (IncidenceList*)malloc(sizeof(IncidenceList));
//		IncidenceList* newv2 = (IncidenceList*)malloc(sizeof(IncidenceList));
//		newv1->edgeIdx = newv2->edgeIdx = idx;
//		newv1->next = newv2->next = NULL;
//		
//		while (vertice1IncidenceNode->next != NULL) vertice1IncidenceNode = vertice1IncidenceNode->next;
//		while (vertice2IncidenceNode->next != NULL) vertice2IncidenceNode = vertice2IncidenceNode->next;
//
//		vertice1IncidenceNode->next = newv1;
//		if (vertice1IncidenceNode != vertice2IncidenceNode) vertice2IncidenceNode->next = newv2;
//	}
//}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct vertices {
    struct incidence* inciList;
    int num;
}vertices;

typedef struct incidence {
    int edgeIndex;
    struct incidence* next;
}incidence;

typedef struct edge {
    int v1;
    int v2;
    int weight;
}edge;

incidence* getIncidence(int e);
void addIncidenceList(incidence* iH, int edgeIndex);
void reduceIncidenceList(incidence* iH, int edgeIndex);
void insertEdge(int v1_num, int v2_num, int weight, edge* e, vertices* v);
void printedge(int a_num, vertices* v, edge* e);

int main(void) {
    vertices v[6];               //정점 구조체 배열
    edge e[21];

    for (int i = 0; i < 6; i++) {  //각각의 incidence 연결리스트에 헤더노드 달아줌
        v[i].num = i + 1;
        v[i].inciList = getIncidence(-1);
    }

    int k = 0;
    for (int i = 1; i <= 6; i++) {      //edge 구조체 배열을 초기 상태로 (모두 w=0)
        for (int j = i; j <= 6; j++) {
            e[k].v1 = i;
            e[k].v2 = j;
            e[k++].weight = 0;
        }
    }

    insertEdge(1, 2, 1, e, v);
    insertEdge(1, 3, 1, e, v);
    insertEdge(1, 4, 1, e, v);
    insertEdge(1, 6, 2, e, v);
    insertEdge(2, 3, 1, e, v);
    insertEdge(3, 5, 4, e, v);
    insertEdge(5, 5, 4, e, v);
    insertEdge(5, 6, 3, e, v);

    while (1) {
        char a;
        scanf("%c", &a);
        if (a == 'q') break;
        else if (a == 'm') {
            int a, b, m;
            scanf("%d %d %d", &a, &b, &m);
            insertEdge(a, b, m, e, v);
        }
        else if (a == 'a') {
            int a;
            scanf("%d", &a);
            printedge(a, v, e);
        }
        getchar();
    }
}

incidence* getIncidence(int e) {
    incidence* a = (incidence*)malloc(sizeof(incidence));
    a->edgeIndex = e;
    a->next = NULL;
    return a;
}

void addIncidenceList(incidence* iH, int edgeIndex) {
    while (iH->next != NULL && iH->next->edgeIndex < edgeIndex) {
        iH = iH->next;
    }
    incidence* a = getIncidence(edgeIndex);
    a->next = iH->next;
    iH->next = a;
    return;
}

void reduceIncidenceList(incidence* iH, int edgeIndex) {
    while (iH->next->edgeIndex != edgeIndex) {
        iH = iH->next;
    }
    incidence* tmp = iH->next;
    iH->next = tmp->next;
    free(tmp);
}

void insertEdge(int v1_num, int v2_num, int weight, edge* e, vertices* v) {
    if (v1_num > v2_num) {
        int tmp = v1_num;
        v1_num = v2_num;
        v2_num = tmp;
    }

    vertices v1 = { NULL,0 };
    vertices v2 = { NULL,0 };

    for (int i = 0; i < 6; i++) {
        if (v[i].num == v1_num) v1 = v[i];
        if (v[i].num == v2_num) v2 = v[i];
    }

    if (v1.num == 0 || v2.num == 0) { // 정점이 하나라도 존재하지 않으면 변화X
        printf("-1\n");
        return;
    }

    int i = 0;
    int prevWeight = 0;
    for (i = 0; i < 21; i++) {
        if (e[i].v1 == v1_num && e[i].v2 == v2_num) {
            prevWeight = e[i].weight;
            e[i].weight = weight;
            break;
        }
    }

    if (weight == 0) {
        if (v1_num != v2_num) reduceIncidenceList(v1.inciList, i);
        reduceIncidenceList(v2.inciList, i);
    }
    else if (!prevWeight) {
        if (v1_num != v2_num)addIncidenceList(v1.inciList, i);
        addIncidenceList(v2.inciList, i);
    }
}

void printedge(int a_num, vertices* v, edge* e) {
    if (a_num < 1 || a_num>6) {
        printf("-1\n");
        return;
    }

    incidence* iH = v[a_num - 1].inciList->next;
    while (iH != NULL) {
        int printnum = e[iH->edgeIndex].v1 == a_num ? e[iH->edgeIndex].v2 : e[iH->edgeIndex].v1;
        printf("%d %d ", printnum, e[iH->edgeIndex].weight);
        iH = iH->next;
    }
    printf("\n");
}