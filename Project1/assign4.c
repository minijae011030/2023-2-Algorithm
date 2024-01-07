#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int findHashIdx(int m, int n);	// �ؽ����̺� �ε��� �����ϴ� �Լ�
int insertNumbertoHashTable(int* arr, int m, int n);	// �ؽ����̺� Ű�� �����ϴ� �Լ�
int deleteNumbertoHashTable(int* arr, int m, int n);	// �ؽ����̺��� Ű�� �����ϴ� �Լ�
int searchNumbertoHashTable(int* arr, int m, int n);	// �ؽ����̺��� Ű�� Ž���ϴ� �Լ�

int main() {
	int m, n;
	char cmd;
	scanf("%d", &m);	// �ؽ����̺� ũ�� �Է�

	int* arr = (int*)malloc(sizeof(int) * m);	// �ؽ����̺� �����Ҵ�
	for (int i = 0; i < m; i++) arr[i] = 0;	// empty sell�� �ʱ�ȭ

	while (1) {
		scanf("%c", &cmd);	// ��ɾ� �Է�
		switch (cmd)
		{
		case 'i':
			scanf("%d", &n);	// Ű �Է�
			printf("%d\n", insertNumbertoHashTable(arr, m, n));	// �ؽ����̺� Ű ����
			break;
		case 'd':
			scanf("%d", &n);	// Ű �Է�
			printf("%d\n", deleteNumbertoHashTable(arr, m, n));	// �ؽ����̺��� Ű ����
			break;
		case 's':
			scanf("%d", &n);	// Ű �Է�
			printf("%d\n", searchNumbertoHashTable(arr, m, n));	// �ؽ����̺��� Ű Ž��
			break;
		case 'e':
			free(arr);	// �ؽ����̺� �޸� ���� �� ���α׷� ����
			return;
		default:
			break;
		}
	}
}

int findHashIdx(int m, int n) {
	return n % m;
}

int insertNumbertoHashTable(int* arr, int m, int n) {
	int idx = findHashIdx(m, n);
	int prevIdx = (idx == 0 ? m - 1 : idx - 1);
	//printf("idx: %d, prevIdx: %d\n", idx, prevIdx);

	while (1) {
		if (arr[idx] == 0 || arr[idx] == -1)	// �� ��, ��Ȱ��ȭ ��
		{
			arr[idx] = n;	// Ű ����
			return idx;
		}
		printf("C");	// �浹
		if (idx == prevIdx && arr[idx] > 0) return -1;	// �� ������ ���� ��
		idx++;
		if (idx == m) idx = 0;	
	}
}

int deleteNumbertoHashTable(int* arr, int m, int n) {
	int idx = findHashIdx(m, n);
	int prevIdx = (idx == 0 ? m - 1 : idx - 1);

	while (1) {
		if (arr[idx] == 0) return -1;	// �� ��
		if (arr[idx] == n) {	// Ű �߰�
			arr[idx] = -1;
			return idx;
		}
		printf("C");	// �浹
		if (idx == prevIdx && arr[idx] != n) return -1;	// �� ���Ҵµ� ��尡 ���� ��
			
		idx++;
		if (idx == m) idx = 0;
	}
}

int searchNumbertoHashTable(int* arr, int m, int n) {
	int idx = findHashIdx(m, n);
	int prevIdx = (idx == 0 ? m - 1 : idx - 1);

	while (1) {
		if (arr[idx] == 0) return -1;	// �� �ε��� �߰�
		
		if (arr[idx] == n) return idx;	// Ű �߰�

		printf("C");	// �浹
		if (idx == prevIdx && arr[idx] != n) return -1;	// ������ �� ������ ��

		idx++;
		if (idx == m) idx = 0;
	}
}
