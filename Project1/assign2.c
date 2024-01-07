#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 이진 트리 노드 구조체 
typedef struct Node {
	struct Node* left;
	struct Node* right;
	struct Node* parent;
	int data;
} Node;

Node* insertItem(Node* H, int key);	// 키를 힙에 삽입하고 0을 인쇄하는 함수
Node* removeMax(Node* first_node, Node* H);	// 키를 힙에서 삭제하고 반환된 키를 인쇄하는 함수

Node* advanceLast(Node* H);	// 삽입 노드를 찾는 함수
Node* retreatLast(Node* root, Node* H);	// 마지막 노드를 갱신하는 함수

void upHeap(Node *H);	// 저장된 키를 크기에 맞는 위치로 상향 이동
void downHeap(Node *root);	// 저장된 키를 크기에 맞는 위치로 하향 이동

void expandExternal(Node* H);	// 노드 확장하는 함수
void reduceExternal(Node* H);	// 노드 축소하는 함수
void freeTree(Node* H);	// 메모리 해제하는 함수

int getHieght(Node* root);	// 트리의 높이를 계산하는 함수
void levelTravel(Node* root);	// 레벨 순회 함수
void printHeap(Node* H, int level);	// 힙의 내용을 인쇄하는 함수 -> 이진트리의 레벨순서로 인쇄

int main() {
	char cmd;
	int key;

	Node* H = NULL, *root = NULL;

	while (1) {
		scanf("%c", &cmd);	// 명령어 입력
		
		switch (cmd)
		{
		case 'i':	// i 입력 시 insertItem 함수 실행해 이진트리에 노드 삽입
			scanf("%d", &key);	// key 입력 받음

			if (H) {
				H = insertItem(H, key);
			}
			else {	// 이진트리가 생성되지 않았을 때 루트 생성
				H = (Node*)malloc(sizeof(Node));
				root = H;

				H->parent = NULL;
				H->data = key;
				printf("0\n");
				expandExternal(H);
			}

			getchar();
			break;

		case 'd':	// d 입력 시 removeMax 함수 실행해 가장 큰 원소 제거
			H = removeMax(root, H);
			break;
				
		case 'p':	// p 입력 시 이진트리를 출력하는 함수 실행
			levelTravel(root);
			printf("\n");
			break;

		case 'q':	// q 입력 시 이진트리의 메모리를 해제하고 프로그램 종료
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
	H = advanceLast(H);	// 삽입할 위치 설정

	H->data = key;	// 노드 데이터 설정

	expandExternal(H);	// 노드 확장
	Node* newLastNode = H;	// 삽입 위치를 새 노드 변수에 저장
	upHeap(H);	// 삽입한 노드의 데이터를 upHeap 함수를 이용해 자리에 맞는 위치로 상향 이동

	printf("0\n");
	return newLastNode;	// 삽입 위치 리턴
}
Node* removeMax(Node* root, Node* H) {
	// 마지막 노드의 데이터와 루트 노드의 데이터 swap
	int tmp = root->data;
	root->data = H->data;
	H->data = tmp;

	printf("%d\n", H->data);

	Node* newLastNode = retreatLast(root, H);	// 마지막 노드를 새 노드 변수로 갱신
	reduceExternal(H);	// 가장 큰 데이터를 가진 노드를 연결 해제

	if (root->data != NULL) {
		downHeap(root);	// 루트 데이터를 downHeap 함수를 이용해 자리에 맞는 위치로 하향 이동
	}

	return newLastNode;
}

Node* advanceLast(Node* H) {
	// 현재 노드가 오른쪽 자식인 동안, 부모 노드로 이동
	while (H->parent != NULL && H->parent->right == H) {
		H = H->parent;	// 부모 노드로 이동
	}

	// 현재 노드가 왼쪽 자식일 때, 형제 노드로 이동
	if (H->parent != NULL && H->parent->left == H) {	// 현재 노드가 루트 노드가 아니면서 현재 노드가 왼쪽 자식일 떄
		H = H->parent->right;	// 형제 노드로 이동
	}

	while (1) {
		// 현재 노드가 내부노드인 동안, 왼쪽 자식으로 이동
		if (H->left == NULL) {	// 외부 노드로 접근하면 break
			break;
		}
		H = H->left;	// 왼쪽 자식으로 이동
	}

	return H;
}
Node* retreatLast(Node* root, Node* H) {
	// 현재 노드가 왼쪽 자식인 동안, 부모 노드로 이동
	while (H != root && H->parent->left == H) {
		H = H->parent;	// 부모 노드로 이동
	}

	// 현재 노드가 오른쪽 자식일 때, 형제 노드로 이동
	if (H != root && H->parent->right == H) {	// 현재 노드가 루트 노드가 아니면서 현재 노드가 오른쪽 자식일 때 
		H = H->parent->left;	// 형제 노드로 이동
	}

	while (1) {
		// 현재 노드가 내부노드인 동안, 오른쪽 자식으로 이동
		if (H->left->left == NULL || H->right->left == NULL) {	// 외부 노드로 접근하면 break
			break;
		}
		H = H->right;	// 오른쪽 자식으로 이동
	}
	return H;
}

void upHeap(Node* H) {
	// 루트 노드에 접근하면 종료
	if (H->parent == NULL) {
		return;
	}

	// 현재 노드의 데이터가 부모 노드의 데이터보다 작으면 종료
	if (H->data <= H->parent->data) {
		return;
	}

	// 부모 노드의 데이터와 현재 노드의 데이터 swap
	int tmp = H->parent->data;
	H->parent->data = H->data;
	H->data = tmp;

	upHeap(H->parent);	// 부모 노드로 올라가 upHeap 수행
}
void downHeap(Node* H) {
	// 현재 노드가 외부노드이면 종료
	if (H->left->left == NULL && H->right->left == NULL) {
		return;
	}

	Node* bigger = H->left;	// 현재 노드의 왼쪽 노드를 biggerr로 설정

	if (H->right->left != NULL) {	// 현재 노드의 왼쪽 노드가 빈 노드가 아닐 때
		if (H->right->data > bigger->data) {	// 오른쪽 노드의 데이터가 bigger 노드의 데이터보다 클 때
			bigger = H->right;	// bigger 노드를 오른쪽 노드로 변경
		}
	}

	if (H->data >= bigger->data) {	// 현재 노드의 데이터가 bigger노드의 데이터보다 클 때 downHeap 종료
		return;
	}

	// 현재 노드의 데이터와 bigger노드의 데이터 swap
	int tmp = H->data;
	H->data = bigger->data;
	bigger->data = tmp;

	downHeap(bigger);	// 형제 노드 중 값이 큰 노드로 내려가 downHeap 수행
}

void expandExternal(Node* H) {
	// 자식 노드 생성
	Node* left = (Node*)malloc(sizeof(Node));
	Node* right = (Node*)malloc(sizeof(Node));

	// 왼쪽 자식 노드 설정
	left->left = NULL;
	left->right = NULL;
	left->data = NULL;
	left->parent = H;

	// 오른쪽 자식 노드 설정
	right->left = NULL;
	right->right = NULL;
	right->data = NULL;
	right->parent = H;

	// 현재 노드의 자식 노드로 연결
	H->left = left;
	H->right = right;
}
void reduceExternal(Node* H) {
	// 부모 노드 데이터를 제외하고 NULL로 변경
	H->data = H->left = H->right = NULL;
}
void freeTree(Node* H) {
	// 이진 트리의 메모리 해제
	if (H == NULL) {
		return;
	}
	freeTree(H->left);
	freeTree(H->right);
	free(H);
}

int getHieght(Node* root) {
	if (root == NULL) {	// 이진 트리가 비었다면 0 반환
		return 0;
	}
	int leftHeight = getHieght(root->left);
	int rightHeight = getHieght(root->right);
	
	// 왼쪽 트리와 오른쪽 트리 중 더 큰 높이에 1을 더해 리턴
	return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
}
void levelTravel(Node* root) {
	int height = getHieght(root);
	// 루트 노드부터 시작해 레벨 별로 노드 데이터를 출력하는 함수 실행
	for (int i = 1; i <= height; i++) {	
		printHeap(root, i);
	}
}
void printHeap(Node* H, int level) {
	if (H->left == NULL) {	// 외부 노드이면 종료
		return;
	}
	if (level == 1) {	// 루트 노드일 때
		printf(" %d", H->data);
	}
	else if (level > 1) {	// 루트 노드가 아닐 때
		printHeap(H->left, level - 1);
		printHeap(H->right, level - 1);
	}
}