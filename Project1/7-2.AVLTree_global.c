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

int findElement(AVLTree* tree, int key);	// ���� Ʈ������ Ű key�� ������ ��带 ã�� �� ��忡 ����� ���Ҹ� ��ȯ
void insertItem(AVLTree* tree, int key);	// ���� Ʈ���� key�� ������ �� ��带 �����ϰ� searchAndFixAfterInsertion �Լ� ȣ��
AVLTree* treeSearch(AVLTree* node, int key);	// ���� Ʈ������ Ű key�� ������ ��带 ��ȯ

void searchAndFixAfterInsertion(AVLTree* node);	// �����˻縦 �����ϰ� �ұ����� ������ ������ ���� ���̱��� �Ӽ��� ȸ��
bool updateHeight(AVLTree* node);	// ��� node�� ���̸� (�ʿ��ϸ�) ������ �� ���� ���θ� ��ȯ
bool isBalanced(AVLTree* node);	// ��� node�� ���̱��� ���θ� ��ȯ
AVLTree* restructure(AVLTree* x, AVLTree* y, AVLTree* z);	// 3-��� ������ ������ �� (���ŵ�) 3-����� ��Ʈ�� ��ȯ

bool isExternal(AVLTree* node);	// ��� node�� �ܺγ������ ���θ� ��ȯ
bool isInternal(AVLTree* node);	// ��� node�� ���γ������ ���θ� ��ȯ
AVLTree* sibling(AVLTree* node);	// ��� node�� ������ȸ �İ��ڸ� ��ȯ
AVLTree* inOrderSucc(AVLTree* node);	// ��� node�� ���� ��带 ��ȯ

void expandExternal(AVLTree* node);	// ��� Ȯ��

void printTree(AVLTree* node); // Ʈ���� ������ȸ�� ���
void freeTree(AVLTree* tree);	// Ʈ�� �޸� ����

void main() {
	// Ʈ�� �ʱ�ȭ
	root = (AVLTree*)malloc(sizeof(AVLTree));
	root->parent = root->leftChild = root->rightChild = NULL;

	////////////////////////////////////////////////////////////

	// ���α׷� ����
	int key, element;
	char cmd;

	while (1) {
		scanf("%c", &cmd);
		switch (cmd)
		{
		case 'q':	// q�� �ԷµǸ� Ʈ���� �޸𸮸� �����ϰ� ���α׷� ����
			freeTree(root);

			return;
		case 'i':	// i�� �ԷµǸ� ��� ����
			scanf("%d", &key);	
			insertItem(root, key);

			break;
		case 's':	// s�� �ԷµǸ� ��� Ž��
			scanf("%d", &key);
			element = findElement(root, key);

			if (element == -1) printf("X\n");	// �ش��ϴ� ��尡 ������ X ���
			else printf("%d\n", element);		// �ش��ϴ� ��尡 ������ value ���

			break;
		case 'p':	// p�� �ԷµǸ� ��� ���
			printTree(root);	// ������ȸ�� Ʈ�� ���
			printf("\n");

			break;
		default:
			break;
		}
	}
}

int findElement(AVLTree* tree, int key) {
	// ���� Ʈ������ Ű key�� ������ ��带 ã�� �� ��忡 ����� ���Ҹ� ��ȯ
	AVLTree* node = treeSearch(tree, key);

	if (isExternal(node)) return -1;
	else return node->key;
}

void insertItem(AVLTree* node, int k) {
	// ���� Ʈ���� key�� ������ �� ��带 �����ϰ� searchAndFixAfterInsertion �Լ� ȣ��
	AVLTree* p = treeSearch(node, k);

	if (isInternal(p)) return;
	else {
		p->key = k;
		expandExternal(p);
		searchAndFixAfterInsertion(p);
	}
}

AVLTree* treeSearch(AVLTree* node, int k) {
	// ���� Ʈ������ Ű key�� ������ ��带 ��ȯ
	if (isExternal(node)) return node;

	if (node->key == k) return node;
	else if (node->key > k) return treeSearch(node->leftChild, k);
	else return treeSearch(node->rightChild, k);
}

void searchAndFixAfterInsertion(AVLTree* node) {
	// �����˻縦 �����ϰ� �ұ����� ������ ������ ���� ���̱��� �Ӽ��� ȸ��
	AVLTree* x, * y, * z;

	node->leftChild->height = 0;
	node->rightChild->height = 0;
	node->height = 1;

	if (node->parent == NULL) return;	// �ش� ��尡 ��Ʈ����̸� �Լ� ����

	z = node->parent;	// �ش� ����� ��Ʈ ��带 z�� ����
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL) return;	// ��Ʈ��忡 �����ϸ� �ݺ��� ����
		z = z->parent;	// ���ǿ� �����ϴ� ���� �θ���� ����
	}
	if (isBalanced(z)) return;	// ��Ʈ��忡�� ������ ������ �Լ� ����

	// z�� ���� �ڽ� ��带 y�� ����
	if (z->leftChild->height > z->rightChild->height) y = z->leftChild;	
	else y = z->rightChild;

	// y�� ���� �ڽ� ��带 x�� ����
	if (y->leftChild->height > y->rightChild->height) x = y->leftChild;
	else x = y->rightChild;

	restructure(x, y, z);	// x, y, z�� ���� ��� ���� ����
	return;
}

bool updateHeight(AVLTree* node) {
	// ��� node�� ���̸� (�ʿ��ϸ�) ������ �� ���� ���θ� ��ȯ
	int height = ((node->leftChild->height) > (node->rightChild->height)) ? (node->leftChild->height + 1) : (node->rightChild->height + 1);

	if (height != node->height) {
		node->height = height;
		return true;
	}
	else return false;
}

bool isBalanced(AVLTree* node) {
	// ��� node�� ���̱��� ���θ� ��ȯ
	int value = node->leftChild->height - node->rightChild->height;

	if ((-1 <= value) && (value <= 1)) return true;	// ����-������ �ڽ� ����� ���� ���� -1 ~ 1 ������ ���
	else return false;		// ����-������ �ڽ� ����� ���� ���� -1 ~ 1 ���̰� �ƴ� ���
}

AVLTree* restructure(AVLTree* x, AVLTree* y, AVLTree* z) {
	// 3-��� ������ ������ �� (���ŵ�) 3-����� ��Ʈ�� ��ȯ

	AVLTree* a, * b, * c;
	AVLTree* T0, * T1, * T2, * T3;

	// x, y, z�� ������ȸ �湮������ ������ (a, b, c) ��� ��
	// x, y, z�� ��Ʈ���� ��� x, y, z�� ��Ʈ�� �ϴ� ��Ʈ���� ������ 4���� ��Ʈ������ ������ȸ �湮���� ������ (T0, T1, T2, T3) �̶�� ��

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

	// b ����� �θ� ����
	if (z->parent == NULL) {
		// z�� ��Ʈ����� ��
		root = b;
		b->parent = NULL;
	}
	else if (z->parent->leftChild == z) {
		// z�� ���� �ڽ��� ��
		z->parent->leftChild = b;
		b->parent = z->parent;
	}
	else if (z->parent->rightChild == z) {
		// z�� ������ �ڽ��� ��
		z->parent->rightChild = b;
		b->parent = z->parent;
	}

	// z�� ��Ʈ�� �ϴ� ��Ʈ���� b�� ��Ʈ�� �ϴ� ��Ʈ���� ��ü�Ѵ�.
	// T0�� T1�� ���� a�� ���� �� ������ ��Ʈ���� �����.
	a->leftChild = T0;
	a->rightChild = T1;
	T0->parent = T1->parent = a;
	updateHeight(a);

	// T2�� T3�� ���� c�� ���� �� ������ ��Ʈ���� �����.
	c->leftChild = T2;
	c->rightChild = T3;
	T2->parent = T3->parent = c;
	updateHeight(c);

	// a�� c�� ���� b�� ���� �� ������ �ڽ����� �����.
	b->leftChild = a;
	b->rightChild = c;
	a->parent = c->parent = b;
	updateHeight(b);

	return b;
}

bool isExternal(AVLTree* node) {
	// ��� node�� �ܺγ������ ���θ� ��ȯ
	if ((node->leftChild == NULL) && (node->rightChild == NULL)) return true;
	else return false;
}

bool isInternal(AVLTree* node) {
	// ��� node�� ���γ������ ���θ� ��ȯ
	if ((node->leftChild != NULL) || (node->rightChild != NULL)) return true;
	else return false;
}

AVLTree* sibling(AVLTree* node) {
	// ��� node�� ���� ��带 ��ȯ
	if (node->parent == NULL) return;

	if (node->parent->leftChild == node) return node->parent->rightChild;
	else return node->parent->leftChild;
}

AVLTree* inOrderSucc(AVLTree* node) {
	// ��� node�� ������ȸ �İ��ڸ� ��ȯ
	node = node->rightChild;
	if (isExternal(node)) return;

	while (isInternal(node->leftChild)) node = node->leftChild;

	return node;
}

void expandExternal(AVLTree* node) {
	// ��� Ȯ��
	AVLTree* leftnode = (AVLTree*)malloc(sizeof(AVLTree));	// ���� �ڽ� Ȯ��
	AVLTree* rightnode = (AVLTree*)malloc(sizeof(AVLTree));	// ������ �ڽ� Ȯ��

	// ���� �ڽ� ����
	leftnode->leftChild = NULL;
	leftnode->rightChild = NULL;
	leftnode->height = 0;
	leftnode->parent = node;

	// ������ �ڽ� ����
	rightnode->leftChild = NULL;
	rightnode->rightChild = NULL;
	rightnode->height = 0;
	rightnode->parent = node;

	// �ڽ� Ȯ��
	node->leftChild = leftnode;
	node->rightChild = rightnode;
	node->height = 1;

	return;
}

void printTree(AVLTree* tree) {
	// Ʈ���� ������ȸ�� ���
	if (isExternal(tree)) return;
	else {
		printf(" %d", tree->key);
		printTree(tree->leftChild);
		printTree(tree->rightChild);
	}
}

void freeTree(AVLTree* tree) {
	// Ʈ�� �޸� ����
	if (isExternal(tree)) return;
	else {
		freeTree(tree->leftChild);
		freeTree(tree->rightChild);
		free(tree);
	}
}