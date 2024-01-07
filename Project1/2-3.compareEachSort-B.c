#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

void selectionSort(int* arr, int n);	// 선택정렬 알고리즘
void insertionSort(int* arr, int n);	// 삽입정렬 알고리즘

int main(void) {
	int n;
	scanf("%d", &n);
	int* arr1, * arr2;
	arr1 = (int*)malloc(sizeof(int*) * n);
	arr2 = (int*)malloc(sizeof(int*) * n);

	for (int i = 0; i < n; i++) {
		long long a = ((((long)rand() << 15) | rand()) % 1000000) + 1;	// 난수 발생
		arr1[i] = a;
		arr2[i] = a;
	}

	insertionSort(arr1, n);
	insertionSort(arr2, n);

	// 선택정렬 실행시간 계산
	LARGE_INTEGER ticksPerSec1;
	LARGE_INTEGER start1, end1, diff1;

	QueryPerformanceFrequency(&ticksPerSec1);
	QueryPerformanceCounter(&start1);
	selectionSort(arr1, n);
	QueryPerformanceCounter(&end1);

	diff1.QuadPart = end1.QuadPart - start1.QuadPart;
	printf("selctionSort time\n%.12f sec\n\n", ((double)diff1.QuadPart / (double)ticksPerSec1.QuadPart));

	// 삽입정렬 실행시간 계산
	LARGE_INTEGER ticksPerSec2;
	LARGE_INTEGER start2, end2, diff2;

	QueryPerformanceFrequency(&ticksPerSec2);
	QueryPerformanceCounter(&start2);
	insertionSort(arr2, n);
	QueryPerformanceCounter(&end2);

	diff2.QuadPart = end2.QuadPart - start2.QuadPart;
	printf("insertionSort time\n%.12f sec\n\n", ((double)diff2.QuadPart / (double)ticksPerSec2.QuadPart));

	// 메모리 해제
	free(arr1);
	free(arr2);

	return 0;
}

void selectionSort(int* arr, int n) {
	for (int pass = 0; pass < n - 2; pass++) {
		int minLoc = pass;
		for (int j = pass + 1; j < n - 1; j++) {
			if (arr[j] < arr[minLoc]) {
				minLoc = j;
			}
			int tmp = arr[pass];
			arr[pass] = arr[minLoc];
			arr[minLoc] = tmp;
		}
	}

	return;
}

void insertionSort(int* arr, int n) {
	for (int pass = 1; pass < n - 1; pass++) {
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