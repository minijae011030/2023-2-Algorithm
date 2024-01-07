#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BinarySearchTree {
	struct BinarySearchTree* parent;
	struct BinarySearchTree* leftChild;
	struct BinarySearchTree* rightChild;
	int key;
}BinarySearchTree;

int findElement(BinarySearchTree* tree, int key);	// ���� Ʈ������ Ű key�� ������ ��带 ã�� �� ��忡 ����� ���Ҹ� ��ȯ
void insertItem(BinarySearchTree* tree, int key);	// ���� Ʈ���� Ű key�� ������ �� ��带 ����
BinarySearchTree* treeSearch(BinarySearchTree* node, int key);	// ���� Ʈ������ Ű key�� ������ ��带 ��ȯ
int removeElement(BinarySearchTree* tree, int key);	// ���� Ʈ������ Ű key�� ������ ��带 ������ �� ���Ҹ� ��ȯ

bool isExternal(BinarySearchTree* node);	// ��� node�� �ܺγ������ ���θ� ��ȯ
bool isInternal(BinarySearchTree* node);	// ��� node�� ���γ������ ���θ� ��ȯ
BinarySearchTree* inOrderSucc(BinarySearchTree* node);	// ��� node�� ������ȸ �İ��ڸ� ��ȯ

void expandExternal(BinarySearchTree* node);	// ��� Ȯ��
BinarySearchTree* reduceExternal(BinarySearchTree* root, BinarySearchTree* node);	// ��� ���

BinarySearchTree* sibling(BinarySearchTree* node);	// ��� node�� ���� ��带 ��ȯ
void printTree(BinarySearchTree* node); // Ʈ���� ������ȸ�� ���

void freeTree(BinarySearchTree* tree);	// Ʈ�� �޸� ����

int main() {
	// 1��
	BinarySearchTree* tree = NULL, * root = NULL;
	tree = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
	tree->parent = NULL;
	tree->key = NULL;
	root = tree;
	int key, element = 0;
	char cmd;

	while (1) {
		scanf("%c", &cmd);
		switch (cmd)
		{
		case 'q':
			freeTree(root);
			return;
		case 'i':
			scanf("%d", &key);
			if (tree->key != NULL) insertItem(tree, key);
			else {
				tree->parent = NULL;
				tree->key = key;

				expandExternal(tree);
			}
			break;
		case 'd':
			scanf("%d", &key);
			element = removeElement(root, key);

			if (element == -1) printf("X\n");
			else printf("%d\n", element);
			break;
		case 's':
			scanf("%d", &key);
			element = findElement(tree, key);

			if (element == -1) printf("X\n");
			else printf("%d\n", element);

			break;
		case 'p':
			printTree(root);
			printf("\n");

			break;
		;		default:
			break;
		}
	}
}

int findElement(BinarySearchTree* tree, int key) {
	BinarySearchTree* node = treeSearch(tree, key);

	if (isExternal(node)) return -1;
	else return node->key;
}

void insertItem(BinarySearchTree* tree, int key) {
	BinarySearchTree* node = treeSearch(tree, key);

	if (isInternal(node)) return;
	else {
		node->key = key;
		expandExternal(node);
		return;
	}
}

BinarySearchTree* treeSearch(BinarySearchTree* node, int key) {
	if (isExternal(node)) return node;

	if (node->key == key) return node;
	else if (key < node->key) return treeSearch(node->leftChild, key);
	else return treeSearch(node->rightChild, key);
}

int removeElement(BinarySearchTree* root, int key) {
	BinarySearchTree* node = treeSearch(root, key);

	int k = node->key;
	if (isExternal(node)) return -1;

	if (node == root && (node->leftChild->key == NULL && node->rightChild->key == NULL)) node->key = NULL;
	else {
		BinarySearchTree* leftNode = node->leftChild;

		if (!isExternal(leftNode)) leftNode = node->rightChild;

		if (isExternal(leftNode)) reduceExternal(root, leftNode);
		else {
			BinarySearchTree* y = inOrderSucc(node);
			leftNode = y->leftChild;
			node->key = y->key;
			reduceExternal(root, leftNode);
		}
	}

	return k;
}

bool isExternal(BinarySearchTree* node) {
	if (node->leftChild == NULL && node->rightChild == NULL) return true;
	else return false;
}

bool isInternal(BinarySearchTree* node) {
	if (node->leftChild != NULL || node->rightChild != NULL) return true;
	else return false;
}

BinarySearchTree* inOrderSucc(BinarySearchTree* node) {
	node = node->rightChild;

	if (isExternal(node)) return NULL;

	while (isInternal(node->leftChild)) node = node->leftChild;

	return node;
}

void expandExternal(BinarySearchTree* node) {
	BinarySearchTree* leftChild = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
	BinarySearchTree* rightChild = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));

	leftChild->leftChild = NULL;
	leftChild->rightChild = NULL;
	leftChild->key = NULL;
	leftChild->parent = node;

	rightChild->leftChild = NULL;
	rightChild->rightChild = NULL;
	rightChild->key = NULL;
	rightChild->parent = node;

	node->leftChild = leftChild;
	node->rightChild = rightChild;
}

BinarySearchTree* reduceExternal(BinarySearchTree* root, BinarySearchTree* node) {
	BinarySearchTree* nodeParent = node->parent;
	BinarySearchTree* nodeSibling = sibling(node);

	if (nodeParent->parent == NULL) {
		root = nodeSibling;
		nodeSibling->parent = NULL;
	}
	else {
		BinarySearchTree* g = nodeParent->parent;
		nodeSibling->parent = g;

		if (nodeParent == g->leftChild) g->leftChild = nodeSibling;
		else g->rightChild = nodeSibling;
	}

	free(node);
	free(nodeParent);

	return nodeSibling;
}

BinarySearchTree* sibling(BinarySearchTree* node) {
	if (node->parent == NULL) return NULL;

	if (node->parent->leftChild == node) return node->parent->rightChild;
	else return node->parent->leftChild;
}

void printTree(BinarySearchTree* node) {
	if (isExternal(node) || node->key == NULL) return;
	if (node != NULL) printf(" %d", node->key);

	printTree(node->leftChild);
	printTree(node->rightChild);
}

void freeTree(BinarySearchTree* tree) {
	if (tree == NULL) return;

	freeTree(tree->leftChild);
	freeTree(tree->rightChild);
	free(tree);
}
