#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 이진 트리 노드 구조체 
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data); // 새로운 노드 생성
Node* createNode2(); // 새로운 노드 생성

Node* initNode(Node* root, int data, int left, int right);    // 이진 트리 초기화
Node* searchNode(Node* root, int findNode);    // 이진 트리에서 노드를 찾음
void printNode(Node* root, char findRoot[101]);
int main() {
    int n, s;
    scanf("%d", &n);

    Node* root = NULL;

    for (int i = 0; i < n; i++) {
        int node, left, right;
        scanf("%d %d %d", &node, &left, &right);

        if (root == NULL) {
            root = initNode(root, node, left, right);
        }
        else {
            Node* tmp = createNode2();
            tmp = searchNode(root, node);
            printf("%d %d %d\n", tmp->data, tmp->left->data, tmp->right->data);
        }
    }

    scanf("%d", &s);

    for (int i = 0; i < s; i++) {
        char path[101];
        scanf("%s", path);
        printNode(root, path);
        printf("\n");
    } 

    return 0;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* createNode2() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* initNode(Node* root, int data, int left, int right) {
    Node* newNode = createNode(data);
    if (left > 0) {
        Node* leftNode = createNode(left);
        newNode->left = leftNode;
    }
    if (right > 0) {
        Node* rightNode = createNode(right);
        newNode->right = rightNode;
    }

    return newNode;
}

Node* searchNode(Node* root, int findNode) {
    if (root) {
        if (findNode == root->data) {
            printf("find node\n");
            return root;
        }
        else if (findNode > root->data) {
            printf("go right\n");
            searchNode(root->right, findNode);
        }
        else {
            printf("go left\n");
            searchNode(root->left, findNode);
        }
    }
}

void printNode(Node* root, char findRoot[101]) {
    for (int i = 0; i < 101; i++) {
        if (findRoot[i] == '\n') {
            return;
        }
        else if (findRoot[i] == 'L') {
            root = root->left;
            printf(" %d", root->data);
        }
        else if (findRoot[i] == 'R') {
            root = root->right;
            printf(" %d", root->data);
        }
    }
}