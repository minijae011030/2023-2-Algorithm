#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ���� Ʈ�� ��� ����ü 
typedef struct Node {
	struct Node* left;
	struct Node* right;
	struct Node* parent;
	int data;
} Node;

Node* insertItem(Node* H, int key);	// Ű�� ���� �����ϰ� 0�� �μ��ϴ� �Լ�
Node* removeMax(Node* first_node, Node* H);	// Ű�� ������ �����ϰ� ��ȯ�� Ű�� �μ��ϴ� �Լ�

Node* advanceLast(Node* H);	// ���� ��带 ã�� �Լ�
Node* retreatLast(Node* root, Node* H);	// ������ ��带 �����ϴ� �Լ�

void upHeap(Node *H);	// ����� Ű�� ũ�⿡ �´� ��ġ�� ���� �̵�
void downHeap(Node *root);	// ����� Ű�� ũ�⿡ �´� ��ġ�� ���� �̵�

void expandExternal(Node* H);	// ��� Ȯ���ϴ� �Լ�
void reduceExternal(Node* H);	// ��� ����ϴ� �Լ�
void freeTree(Node* H);	// �޸� �����ϴ� �Լ�

int getHieght(Node* root);	// Ʈ���� ���̸� ����ϴ� �Լ�
void levelTravel(Node* root);	// ���� ��ȸ �Լ�
void printHeap(Node* H, int level);	// ���� ������ �μ��ϴ� �Լ� -> ����Ʈ���� ���������� �μ�

int main() {
	char cmd;
	int key;

	Node* H = NULL, *root = NULL;

	while (1) {
		scanf("%c", &cmd);	// ��ɾ� �Է�
		
		switch (cmd)
		{
		case 'i':	// i �Է� �� insertItem �Լ� ������ ����Ʈ���� ��� ����
			scanf("%d", &key);	// key �Է� ����

			if (H) {
				H = insertItem(H, key);
			}
			else {	// ����Ʈ���� �������� �ʾ��� �� ��Ʈ ����
				H = (Node*)malloc(sizeof(Node));
				root = H;

				H->parent = NULL;
				H->data = key;
				printf("0\n");
				expandExternal(H);
			}

			getchar();
			break;

		case 'd':	// d �Է� �� removeMax �Լ� ������ ���� ū ���� ����
			H = removeMax(root, H);
			break;
				
		case 'p':	// p �Է� �� ����Ʈ���� ����ϴ� �Լ� ����
			levelTravel(root);
			printf("\n");
			break;

		case 'q':	// q �Է� �� ����Ʈ���� �޸𸮸� �����ϰ� ���α׷� ����
			if (root) {
				freeTree(root);
			}
			return;

		default:
			break;
		}
	}
}

Node* insertItem(Node* H, int key) {
	H = advanceLast(H);	// ������ ��ġ ����

	H->data = key;	// ��� ������ ����

	expandExternal(H);	// ��� Ȯ��
	Node* newLastNode = H;	// ���� ��ġ�� �� ��� ������ ����
	upHeap(H);	// ������ ����� �����͸� upHeap �Լ��� �̿��� �ڸ��� �´� ��ġ�� ���� �̵�

	printf("0\n");
	return newLastNode;	// ���� ��ġ ����
}
Node* removeMax(Node* root, Node* H) {
	// ������ ����� �����Ϳ� ��Ʈ ����� ������ swap
	int tmp = root->data;
	root->data = H->data;
	H->data = tmp;

	printf("%d\n", H->data);

	Node* newLastNode = retreatLast(root, H);	// ������ ��带 �� ��� ������ ����
	reduceExternal(H);	// ���� ū �����͸� ���� ��带 ���� ����

	if (root->data != NULL) {
		downHeap(root);	// ��Ʈ �����͸� downHeap �Լ��� �̿��� �ڸ��� �´� ��ġ�� ���� �̵�
	}

	return newLastNode;
}

Node* advanceLast(Node* H) {
	// ���� ��尡 ������ �ڽ��� ����, �θ� ���� �̵�
	while (H->parent != NULL && H->parent->right == H) {
		H = H->parent;	// �θ� ���� �̵�
	}

	// ���� ��尡 ���� �ڽ��� ��, ���� ���� �̵�
	if (H->parent != NULL && H->parent->left == H) {	// ���� ��尡 ��Ʈ ��尡 �ƴϸ鼭 ���� ��尡 ���� �ڽ��� ��
		H = H->parent->right;	// ���� ���� �̵�
	}

	while (1) {
		// ���� ��尡 ���γ���� ����, ���� �ڽ����� �̵�
		if (H->left == NULL) {	// �ܺ� ���� �����ϸ� break
			break;
		}
		H = H->left;	// ���� �ڽ����� �̵�
	}

	return H;
}
Node* retreatLast(Node* root, Node* H) {
	// ���� ��尡 ���� �ڽ��� ����, �θ� ���� �̵�
	while (H != root && H->parent->left == H) {
		H = H->parent;	// �θ� ���� �̵�
	}

	// ���� ��尡 ������ �ڽ��� ��, ���� ���� �̵�
	if (H != root && H->parent->right == H) {	// ���� ��尡 ��Ʈ ��尡 �ƴϸ鼭 ���� ��尡 ������ �ڽ��� �� 
		H = H->parent->left;	// ���� ���� �̵�
	}

	while (1) {
		// ���� ��尡 ���γ���� ����, ������ �ڽ����� �̵�
		if (H->left->left == NULL || H->right->left == NULL) {	// �ܺ� ���� �����ϸ� break
			break;
		}
		H = H->right;	// ������ �ڽ����� �̵�
	}
	return H;
}

void upHeap(Node* H) {
	// ��Ʈ ��忡 �����ϸ� ����
	if (H->parent == NULL) {
		return;
	}

	// ���� ����� �����Ͱ� �θ� ����� �����ͺ��� ������ ����
	if (H->data <= H->parent->data) {
		return;
	}

	// �θ� ����� �����Ϳ� ���� ����� ������ swap
	int tmp = H->parent->data;
	H->parent->data = H->data;
	H->data = tmp;

	upHeap(H->parent);	// �θ� ���� �ö� upHeap ����
}
void downHeap(Node* H) {
	// ���� ��尡 �ܺγ���̸� ����
	if (H->left->left == NULL && H->right->left == NULL) {
		return;
	}

	Node* bigger = H->left;	// ���� ����� ���� ��带 biggerr�� ����

	if (H->right->left != NULL) {	// ���� ����� ���� ��尡 �� ��尡 �ƴ� ��
		if (H->right->data > bigger->data) {	// ������ ����� �����Ͱ� bigger ����� �����ͺ��� Ŭ ��
			bigger = H->right;	// bigger ��带 ������ ���� ����
		}
	}

	if (H->data >= bigger->data) {	// ���� ����� �����Ͱ� bigger����� �����ͺ��� Ŭ �� downHeap ����
		return;
	}

	// ���� ����� �����Ϳ� bigger����� ������ swap
	int tmp = H->data;
	H->data = bigger->data;
	bigger->data = tmp;

	downHeap(bigger);	// ���� ��� �� ���� ū ���� ������ downHeap ����
}

void expandExternal(Node* H) {
	// �ڽ� ��� ����
	Node* left = (Node*)malloc(sizeof(Node));
	Node* right = (Node*)malloc(sizeof(Node));

	// ���� �ڽ� ��� ����
	left->left = NULL;
	left->right = NULL;
	left->data = NULL;
	left->parent = H;

	// ������ �ڽ� ��� ����
	right->left = NULL;
	right->right = NULL;
	right->data = NULL;
	right->parent = H;

	// ���� ����� �ڽ� ���� ����
	H->left = left;
	H->right = right;
}
void reduceExternal(Node* H) {
	// �θ� ��� �����͸� �����ϰ� NULL�� ����
	H->data = H->left = H->right = NULL;
}
void freeTree(Node* H) {
	// ���� Ʈ���� �޸� ����
	if (H == NULL) {
		return;
	}
	freeTree(H->left);
	freeTree(H->right);
	free(H);
}

int getHieght(Node* root) {
	if (root == NULL) {	// ���� Ʈ���� ����ٸ� 0 ��ȯ
		return 0;
	}
	int leftHeight = getHieght(root->left);
	int rightHeight = getHieght(root->right);
	
	// ���� Ʈ���� ������ Ʈ�� �� �� ū ���̿� 1�� ���� ����
	return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
}
void levelTravel(Node* root) {
	int height = getHieght(root);
	// ��Ʈ ������ ������ ���� ���� ��� �����͸� ����ϴ� �Լ� ����
	for (int i = 1; i <= height; i++) {	
		printHeap(root, i);
	}
}
void printHeap(Node* H, int level) {
	if (H->left == NULL) {	// �ܺ� ����̸� ����
		return;
	}
	if (level == 1) {	// ��Ʈ ����� ��
		printf(" %d", H->data);
	}
	else if (level > 1) {	// ��Ʈ ��尡 �ƴ� ��
		printHeap(H->left, level - 1);
		printHeap(H->right, level - 1);
	}
}