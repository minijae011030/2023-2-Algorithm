#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int minindex = -1;

int findElement(int* arr, int n, int k);

void main() {
	int n, k, * arr;
	scanf("%d %d", &n, &k);

	arr = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	if (findElement(arr, n, k) == -1) {
		if (minindex == -1)
		{
			printf(" %d\n", n);
		}
		else
		{
			printf(" %d\n", minindex);
		}
	}
	else {
		printf(" %d\n", findElement(arr, n, k));
	}

	free(arr);
}

int findElement(int* arr, int n, int k) {
	int mid, l = 0, r = n - 1;

	while (1) {
		if (l > r) {
			return -1;
		}

		mid = (l + r) / 2;

		if (arr[mid] == k) {
			return mid;
		}
		else if (arr[mid] > k) {
			if (minindex == -1) {
				minindex = mid;
			}
			else if (arr[minindex] > arr[mid]) {
				minindex = mid;
			}
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
}
