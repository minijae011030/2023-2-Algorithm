#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int findHashIndex(int m, int id);
int insertIDtoHashTable(int* arr, int m, int id);
void findIDtoHashTable(int* arr, int m, int id);

int main() {
	int m, n, id;
	char cmd;
	scanf("%d %d", &m, &n);

	int* arr = (int*)malloc(sizeof(int) * m);
	for (int i = 0; i < m; i++) arr[i] = 0;

	while (1) {
		scanf("%c", &cmd);
		switch (cmd)
		{
		case 'i':
			scanf("%d", &id);
			printf("%d\n", insertIDtoHashTable(arr, m, id));
			break;
		case 's':
			scanf("%d", &id);
			findIDtoHashTable(arr, m, id);
			break;
		case 'e':
			return;
		default:
			break;
		}
	}
}

int findHashIndex(int m, int id) {
	return id % m;
}

int insertIDtoHashTable(int* arr, int m, int id) {
	int idx = findHashIndex(m, id);

	if (arr[idx] == 0) {
		arr[idx] = id;
		return idx;
	}
	else {
		while (1) {
			printf("C");
			idx++;
			if (idx == m) idx = 0;
			if (arr[idx] == 0) {
				arr[idx] = id;
				return idx;
			}
		}
	}
}

void findIDtoHashTable(int* arr, int m, int id) {
	for (int i = 0; i < m; i++) {
		if (arr[i] == id) {
			printf("%d %d\n", i, id);
			return;
		}
	}
	printf("-1\n");
	return;
}