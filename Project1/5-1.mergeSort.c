#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//typedef struct node {
//	int data;
//	struct node* next;
//} NODE;
//
//void partition(NODE* L, NODE** L1, NODE** L2, int n);	// 단일연결리스트를 두 개의 부리스트로 분할
//NODE* merge(NODE** L1, NODE** L2);	// 두개의 부 리스트 합병
//void mergeSort(NODE** L, int n);	// 단일연결리스트의 원소들을 합병정렬
//
//void addList(NODE** L, int value);	// 단일연결리스트에 노듸 추가
//void printList(struct node* L);	// 단일연결리스트 출력
//void deleteList(struct node* L);	// 단일연결리스트 메모리 해제
//
//void main() {
//	int n, value;
//	NODE* L = NULL;
//
//	scanf("%d", &n);
//
//	for (int i = 0; i < n; i++) {
//		scanf("%d", &value);
//		addList(&L, value);
//	}
//
//	mergeSort(&L, n);
//	printList(L);
//	deleteList(L);
//
//	return;
//}
//
//void partition(NODE* L, NODE** L1, NODE** L2, int n) {
//	NODE* p = L;
//	*L1 = L;
//
//	for (int i = 0; i < (n / 2) - 1; i++) {
//		p = p->next;
//	}
//
//	*L2 = p->next;
//	p->next = NULL;
//}
//
//NODE* merge(NODE** L1, NODE** L2) {
//	NODE* p, * L;
//	NODE* A = *L1;
//	NODE* B = *L2;
//
//	if (A->data <= B->data) {
//		L = A;
//		A = A->next;
//		p = L;
//	}
//	else {
//		L = B;
//		B = B->next;
//		p = L;
//	}
//
//	while ((A != NULL) && (B != NULL)) {
//		if (A->data <= B->data) {
//			p->next = A;
//			A = A->next;
//			p = p->next;
//		}
//		else {
//			p->next = B;
//			B = B->next;
//			p = p->next;
//		}
//	}
//
//	while (A != NULL) {
//		p->next = A;
//		p = A;
//		A = A->next;
//	}
//
//	while (B != NULL) {
//		p->next = B;
//		p = B;
//		B = B->next;
//	}
//
//	return L;
//}
//
//void mergeSort(NODE** L, int n) {
//	NODE* L1, * L2, * p = *L;
//
//	if (n > 1) {
//		partition(p, &L1, &L2, n);
//
//		if ((n % 2) == 0) {
//			mergeSort(&L1, n / 2);
//			mergeSort(&L2, n / 2);
//		}
//		else {
//			mergeSort(&L1, n / 2);
//			mergeSort(&L2, (n / 2) + 1);
//		}
//
//		*L = merge(&L1, &L2);
//	}
//}
//
//void addList(NODE** L, int value) {
//	NODE* p = *L;
//
//	NODE* newnode = (NODE*)malloc(sizeof(NODE));
//	newnode->data = value;
//	newnode->next = NULL;
//
//	if (*L == NULL) {
//		*L = newnode;
//	}
//	else {
//		while (p->next != NULL) {
//			p = p->next;
//		}
//		p->next = newnode;
//	}
//}
//
//void printList(struct node* L) {
//	struct node* p = L;
//
//	while (p != NULL) {
//		printf(" %d", p->data);
//		p = p->next;
//	}
//
//	printf("\n");
//}
//
//void deleteList(struct node* L) {
//	struct node* p = L;
//
//	while (p != NULL) {
//		L = L->next;
//		free(p);
//		p = L;
//	}
//}

typedef struct Node {
	int key;
	struct Node* next;
}Node; 

void addNode(Node** H, int key);
void partition(Node* H, int k);
Node* merge(Node* L1, Node* L2);
void mergeSort(Node* H, int n);
int main() {
	int n, key;
	scanf("%d", &n);

	Node* H = NULL;

	for (int i = 0; i < n; i++) {
		scanf("%d", &key);
		addNode(&H, key);
	}


	for (int i = 0; i < n; i++) {
		printf("%d ", H->key);
		H = H->next;
	}

}

void addNode(Node** L, int value) {
	Node* p = *L;

	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->key = value;
	newnode->next = NULL;

	if (*L == NULL) {
		*L = newnode;
	}
	else {
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = newnode;
	}
}

void partition(Node* H, Node** L1, Node** L2, int k) {
	*L1 = H;
	Node* p = H;
	for (int i = 0; i < (k / 2) - 1; i++) {
		p = p->next;
	}
	*L2 = p->next;
	p->next = NULL;
}



void mergeSort(Node* H, int n) {
	Node* L1 = NULL, * L2 = NULL;
	if (n > 1) {
		partition(H, L1, L2, n);
		mergeSort(L1, n);
		mergeSort(L2, n);
		H = merge(L1, L2);
	}
}