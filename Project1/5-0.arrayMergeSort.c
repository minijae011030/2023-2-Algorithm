#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int* B, size;
void mergeSort(int* A);
void rMergeSort(int* A, int left, int right);
void merge(int* A, int left, int mid, int right);

int main() {
	int n;
	scanf("%d", &n);
	getchar();
	size = n;

	int *A = (int*)malloc(sizeof(int*) * n);
	B = (int*)malloc(sizeof(int*) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}

	mergeSort(A);

	for (int i = 0; i < n; i++) {
		printf("%d ", A[i]);
	}

}

void mergeSort(int* A) {
	rMergeSort(A, 0, size - 1);
	return;
}

void rMergeSort(int* A, int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;

		rMergeSort(A, left, mid);
		rMergeSort(A, mid + 1, right);

		merge(A, left, mid, right);
	}
	return;
}

void merge(int* A, int left, int mid, int right) {
	int i = left, k = left;
	int j = mid + 1;

	while (i <= mid && j <= right) {
		if (A[i] <= A[j]) {
			B[k++] = A[i++];
		}
		else {
			B[k++] = A[j++];
		}
	}

	while (i <= mid) {
		B[k++] = A[i++];
	}

	while (j <= right) {
		B[k++] = A[j++];
	}

	for (k = left; k <= right; k++) {
		A[k] = B[k];
	}
	return;
}