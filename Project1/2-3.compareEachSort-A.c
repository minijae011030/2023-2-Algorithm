#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

void calcSelectionSortRunTime(int arr[], int n);	// ���� ���� ���� �ð� ��� �Լ�
void calcInsertionSortRunTime(int arr[], int n);	// ���� ���� ���� �ð� ��� �Լ�

void selectionSort(int arr[], int n);	// �������� �˰���
void insertionSort(int arr[], int n);	// �������� �˰���
void reverseSort(int arr[], int n); // ���� ���� �˰���

int main(void) {
	for (int n = 10000; n <= 100000; n += 10000) {
		int* arr1, * arr2;
		arr1 = (int*)malloc(sizeof(int*) * n);
		arr2 = (int*)malloc(sizeof(int*) * n);
		//arr3 = (int*)malloc(sizeof(int*) * n);

		for (int i = 0; i < n; i++) {
			long long a = ((((long)rand() << 15) | rand()) % 1000000) + 1;	// ���� �߻�
			arr1[i] = a;
			arr2[i] = a;
			//arr3[i] = a;
		}
		printf("n = %d\n", n);

		/*selectionSort(arr2, n);

		selectionSort(arr3, n);
		reverseSort(arr3, n);

		printf("arr1 ");
		calcSelectionSortRunTime(arr1, n);
		
		
		printf("arr2 ");
		calcSelectionSortRunTime(arr2, n);

		printf("arr3 ");
		calcSelectionSortRunTime(arr3, n);*/


		// ����
		printf("������ �Է�\n");

		// �������� ����ð� ���
		calcSelectionSortRunTime(arr1, n);
		// �������� ����ð� ���
		calcInsertionSortRunTime(arr2, n);

		// ����
		printf("������ �Է�\n");
		selectionSort(arr1, n);
		selectionSort(arr2, n);

		// �������� ����ð� ���
		calcSelectionSortRunTime(arr1, n);
		// �������� ����ð� ���
		calcInsertionSortRunTime(arr2, n);

		// ����
		printf("������ �Է�\n");
		reverseSort(arr1, n);
		reverseSort(arr2, n);

		// �������� ����ð� ���
		calcSelectionSortRunTime(arr1, n);
		// �������� ����ð� ���
		calcInsertionSortRunTime(arr2, n);

		// �޸� ����
		free(arr1);
		free(arr2);
	}

	return 0;
}

void calcSelectionSortRunTime(int arr[], int n) {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	selectionSort(arr, n);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("selectionSort: %.5f sec\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
}

void calcInsertionSortRunTime(int arr[], int n) {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	insertionSort(arr, n);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("insertionSort: %.5f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
}

void selectionSort(int arr[], int n) {
	int indexMin = 0, tmp = 0;
	for (int i = 0; i < n - 1; i++) {
		indexMin = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[indexMin]) {
				indexMin = j;
			}
		}

		tmp = arr[indexMin];
		arr[indexMin] = arr[i];
		arr[i] = tmp;

	}

	return;

}

void insertionSort(int arr[], int n) {
	for (int pass = 1; pass < n; pass++) {
		int save = arr[pass];
		int j = pass - 1;
		while ((j >= 0) && (arr[j] > save)) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = save;
	}

	return;
}

void reverseSort(int arr[], int n) {
	int i = 0;
	for (int j = 1; j < n; j++) {
		int tmp = arr[j];
		i = j - 1;

		while (i >= 0 && arr[i] < tmp) {
			arr[i + 1] = arr[i];
			i--;
		}
		arr[i + 1] = tmp;

	}
;
	return;
}
