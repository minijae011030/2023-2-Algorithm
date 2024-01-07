#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void inPlaceQuickSort(int* arr, int left, int right);
int findPivot(int* arr, int left, int right);	// pivot의 위치를 정하는 함수
void inPlacePartition(int* arr, int left, int right, int k);

int main() {
	int n, *arr;
	scanf("%d", &n);

	arr = (int*)malloc(sizeof(int) * (n + 1));

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	inPlaceQuickSort(arr, 0, n - 1);

	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}

	free(arr);
}

void inPlaceQuickSort(int* arr, int left, int right) {
	int pivot = findPivot(arr, left, right);
	printf("%d\n", pivot);
	inPlacePartition(arr, left, right, pivot);

	return;
}
int findPivot(int* arr, int left, int right) {
	printf("range: %d~%d\n", left, right);
	int pivot = rand() % (right + 1 - left) + left;

	return pivot;
}
void inPlacePartition(int* arr, int left, int right, int k) {
	int pivot = arr[k], pivot_pos = 0;

	int tmp = arr[k];
	arr[k] = arr[left];
	arr[left] = tmp;

	for (int i = left + 1; i <= right; i++) {
		if (arr[i] == pivot) {
			pivot_pos++;
			int tmp = arr[pivot_pos];
			arr[pivot_pos] = arr[i];
			arr[i] = tmp;
		}
	}

	////////////////////////////////////

	int i = pivot_pos + 1, j = right;

	while (i <= j) {
		while (i <= j && arr[i] <= pivot) {
			i++;
		}

		while (j >= i && arr[j] >= pivot) {
			j--;
		}

		if (i < j) {
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	return;
}

