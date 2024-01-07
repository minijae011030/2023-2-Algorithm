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

int findElement(BinarySearchTree* tree, int key);	// 현재 트리에서 키 key를 저장한 노드를 찾아 그 노드에 저장된 원소를 반환
void insertItem(BinarySearchTree* tree, int key);	// 현재 트리에 키 key를 저장한 새 노드를 삽입
BinarySearchTree* treeSearch(BinarySearchTree* node, int key);	// 현재 트리에서 키 key를 저장한 노드를 반환
int removeElement(BinarySearchTree* tree, int key);	// 현재 트리에서 키 key를 저장한 노드를 삭제한 후 원소를 반환

bool isExternal(BinarySearchTree* node);	// 노드 node가 외부노드인지 여부를 반환
bool isInternal(BinarySearchTree* node);	// 노드 node가 내부노드인지 여부를 반환
BinarySearchTree* inOrderSucc(BinarySearchTree* node);	// 노드 node의 중위순회 후계자를 반환

void expandExternal(BinarySearchTree* node);	// 노드 확장
BinarySearchTree* reduceExternal(BinarySearchTree* root, BinarySearchTree* node);	// 노드 축소

BinarySearchTree* sibling(BinarySearchTree* node);	// 노드 node의 형제 노드를 반환
void printTree(BinarySearchTree* node); // 트리를 전위순회로 출력

void freeTree(BinarySearchTree* tree);	// 트리 메모리 해제

int main() {
	// 1번
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
