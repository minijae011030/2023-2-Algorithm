#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct AVLTree {
	int key;
	int height;
	struct AVLTree* leftChild;
	struct AVLTree* rightChild;
	struct AVLTree* parent;
}AVLTree;

AVLTree* root;

int findElement(AVLTree* tree, int key);	// 현재 트리에서 키 key를 저장한 노드를 찾아 그 노드에 저장된 원소를 반환
void insertItem(AVLTree* tree, int key);	// 현재 트리에 key를 저장한 새 노드를 삽입하고 searchAndFixAfterInsertion 함수 호출
AVLTree* treeSearch(AVLTree* node, int key);	// 현재 트리에서 키 key를 저장한 노드를 반환

void searchAndFixAfterInsertion(AVLTree* node);	// 균형검사를 수행하고 불균형이 있으면 개조를 통해 높이균형 속성을 회복
bool updateHeight(AVLTree* node);	// 노드 node의 높이를 (필요하면) 갱신한 후 갱신 여부를 반환
bool isBalanced(AVLTree* node);	// 노드 node의 높이균형 여부를 반환
AVLTree* restructure(AVLTree* x, AVLTree* y, AVLTree* z);	// 3-노드 개조를 수행한 후 (갱신된) 3-노드의 루트를 반환

bool isExternal(AVLTree* node);	// 노드 node가 외부노드인지 여부를 반환
bool isInternal(AVLTree* node);	// 노드 node가 내부노드인지 여부를 반환
AVLTree* sibling(AVLTree* node);	// 노드 node의 중위순회 후계자를 반환
AVLTree* inOrderSucc(AVLTree* node);	// 노드 node의 형제 노드를 반환

void expandExternal(AVLTree* node);	// 노드 확장

void printTree(AVLTree* node); // 트리를 전위순회로 출력
void freeTree(AVLTree* tree);	// 트리 메모리 해제

void main() {
	// 트리 초기화
	root = (AVLTree*)malloc(sizeof(AVLTree));
	root->parent = root->leftChild = root->rightChild = NULL;

	////////////////////////////////////////////////////////////

	// 프로그램 실행
	int key, element;
	char cmd;

	while (1) {
		scanf("%c", &cmd);
		switch (cmd)
		{
		case 'q':	// q가 입력되면 트리의 메모리를 해제하고 프로그램 종료
			freeTree(root);

			return;
		case 'i':	// i가 입력되면 노드 삽입
			scanf("%d", &key);	
			insertItem(root, key);

			break;
		case 's':	// s가 입력되면 노드 탐색
			scanf("%d", &key);
			element = findElement(root, key);

			if (element == -1) printf("X\n");	// 해당하는 노드가 없으면 X 출력
			else printf("%d\n", element);		// 해당하는 노드가 있으면 value 출력

			break;
		case 'p':	// p가 입력되면 노드 출력
			printTree(root);	// 전위순회로 트리 출력
			printf("\n");

			break;
		default:
			break;
		}
	}
}

int findElement(AVLTree* tree, int key) {
	// 현재 트리에서 키 key를 저장한 노드를 찾아 그 노드에 저장된 원소를 반환
	AVLTree* node = treeSearch(tree, key);

	if (isExternal(node)) return -1;
	else return node->key;
}

void insertItem(AVLTree* node, int k) {
	// 현재 트리에 key를 저장한 새 노드를 삽입하고 searchAndFixAfterInsertion 함수 호출
	AVLTree* p = treeSearch(node, k);

	if (isInternal(p)) return;
	else {
		p->key = k;
		expandExternal(p);
		searchAndFixAfterInsertion(p);
	}
}

AVLTree* treeSearch(AVLTree* node, int k) {
	// 현재 트리에서 키 key를 저장한 노드를 반환
	if (isExternal(node)) return node;

	if (node->key == k) return node;
	else if (node->key > k) return treeSearch(node->leftChild, k);
	else return treeSearch(node->rightChild, k);
}

void searchAndFixAfterInsertion(AVLTree* node) {
	// 균형검사를 수행하고 불균형이 있으면 개조를 통해 높이균형 속성을 회복
	AVLTree* x, * y, * z;

	node->leftChild->height = 0;
	node->rightChild->height = 0;
	node->height = 1;

	if (node->parent == NULL) return;	// 해당 노드가 루트노드이면 함수 종료

	z = node->parent;	// 해당 노드의 루트 노드를 z로 설정
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL) return;	// 루트노드에 접근하면 반복문 종료
		z = z->parent;	// 조건에 만족하는 동안 부모노드로 접근
	}
	if (isBalanced(z)) return;	// 루트노드에서 균형이 맞으면 함수 종료

	// z의 높은 자식 노드를 y로 설정
	if (z->leftChild->height > z->rightChild->height) y = z->leftChild;	
	else y = z->rightChild;

	// y의 높은 자식 노드를 x로 설정
	if (y->leftChild->height > y->rightChild->height) x = y->leftChild;
	else x = y->rightChild;

	restructure(x, y, z);	// x, y, z에 대한 노드 개조 수행
	return;
}

bool updateHeight(AVLTree* node) {
	// 노드 node의 높이를 (필요하면) 갱신한 후 갱신 여부를 반환
	int height = ((node->leftChild->height) > (node->rightChild->height)) ? (node->leftChild->height + 1) : (node->rightChild->height + 1);

	if (height != node->height) {
		node->height = height;
		return true;
	}
	else return false;
}

bool isBalanced(AVLTree* node) {
	// 노드 node의 높이균형 여부를 반환
	int value = node->leftChild->height - node->rightChild->height;

	if ((-1 <= value) && (value <= 1)) return true;	// 왼쪽-오른쪽 자식 노드의 높이 차가 -1 ~ 1 사이인 경우
	else return false;		// 왼쪽-오른쪽 자식 노드의 높이 차가 -1 ~ 1 사이가 아닌 경우
}

AVLTree* restructure(AVLTree* x, AVLTree* y, AVLTree* z) {
	// 3-노드 개조를 수행한 후 (갱신된) 3-노드의 루트를 반환

	AVLTree* a, * b, * c;
	AVLTree* T0, * T1, * T2, * T3;

	// x, y, z의 중위순회 방문순서의 나열을 (a, b, c) 라고 함
	// x, y, z의 부트리들 가운데 x, y, z를 루트로 하는 부트리를 제외한 4개의 부트리들의 중위순회 방문순서 나열을 (T0, T1, T2, T3) 이라고 함

	if ((z->key < y->key) && (y->key < x->key)) {	// x > y > z
		a = z, b = y, c = x;
		T0 = a->leftChild, T1 = b->leftChild, T2 = c->leftChild, T3 = c->rightChild;
	}
	else if ((x->key < y->key) && (y->key < z->key)) {	// x < y < z
		a = x, b = y, c = z;
		T0 = a->leftChild, T1 = a->rightChild, T2 = b->rightChild, T3 = c->rightChild;
	}
	else if ((z->key < x->key) && (x->key < y->key)) {	// z < x < y
		a = z, b = x, c = y;
		T0 = a->leftChild, T1 = b->leftChild, T2 = b->rightChild, T3 = c->rightChild;
	}
	else {	// z > x > y
		a = y, b = x, c = z;
		T0 = a->leftChild, T1 = b->leftChild, T2 = b->rightChild, T3 = c->rightChild;
	}

	// b 노드의 부모 변경
	if (z->parent == NULL) {
		// z가 루트노드일 때
		root = b;
		b->parent = NULL;
	}
	else if (z->parent->leftChild == z) {
		// z가 왼쪽 자식일 때
		z->parent->leftChild = b;
		b->parent = z->parent;
	}
	else if (z->parent->rightChild == z) {
		// z가 오른쪽 자식일 때
		z->parent->rightChild = b;
		b->parent = z->parent;
	}

	// z를 루트로 하는 부트리를 b를 루트로 하는 부트리로 대체한다.
	// T0과 T1를 각각 a의 왼쪽 및 오른쪽 부트리로 만든다.
	a->leftChild = T0;
	a->rightChild = T1;
	T0->parent = T1->parent = a;
	updateHeight(a);

	// T2와 T3을 각각 c의 왼쪽 및 오른쪽 부트리로 만든다.
	c->leftChild = T2;
	c->rightChild = T3;
	T2->parent = T3->parent = c;
	updateHeight(c);

	// a와 c를 각각 b의 왼쪽 및 오른쪽 자식으로 만든다.
	b->leftChild = a;
	b->rightChild = c;
	a->parent = c->parent = b;
	updateHeight(b);

	return b;
}

bool isExternal(AVLTree* node) {
	// 노드 node가 외부노드인지 여부를 반환
	if ((node->leftChild == NULL) && (node->rightChild == NULL)) return true;
	else return false;
}

bool isInternal(AVLTree* node) {
	// 노드 node가 내부노드인지 여부를 반환
	if ((node->leftChild != NULL) || (node->rightChild != NULL)) return true;
	else return false;
}

AVLTree* sibling(AVLTree* node) {
	// 노드 node의 형제 노드를 반환
	if (node->parent == NULL) return;

	if (node->parent->leftChild == node) return node->parent->rightChild;
	else return node->parent->leftChild;
}

AVLTree* inOrderSucc(AVLTree* node) {
	// 노드 node의 중위순회 후계자를 반환
	node = node->rightChild;
	if (isExternal(node)) return;

	while (isInternal(node->leftChild)) node = node->leftChild;

	return node;
}

void expandExternal(AVLTree* node) {
	// 노드 확장
	AVLTree* leftnode = (AVLTree*)malloc(sizeof(AVLTree));	// 왼쪽 자식 확장
	AVLTree* rightnode = (AVLTree*)malloc(sizeof(AVLTree));	// 오른쪽 자식 확장

	// 왼쪽 자식 설정
	leftnode->leftChild = NULL;
	leftnode->rightChild = NULL;
	leftnode->height = 0;
	leftnode->parent = node;

	// 오른쪽 자식 설정
	rightnode->leftChild = NULL;
	rightnode->rightChild = NULL;
	rightnode->height = 0;
	rightnode->parent = node;

	// 자식 확장
	node->leftChild = leftnode;
	node->rightChild = rightnode;
	node->height = 1;

	return;
}

void printTree(AVLTree* tree) {
	// 트리를 전위순회로 출력
	if (isExternal(tree)) return;
	else {
		printf(" %d", tree->key);
		printTree(tree->leftChild);
		printTree(tree->rightChild);
	}
}

void freeTree(AVLTree* tree) {
	// 트리 메모리 해제
	if (isExternal(tree)) return;
	else {
		freeTree(tree->leftChild);
		freeTree(tree->rightChild);
		free(tree);
	}
}