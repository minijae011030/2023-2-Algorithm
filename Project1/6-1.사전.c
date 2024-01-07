#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//int maxindex = NULL;
//
//int findElement(int* arr, int n, int k);
//int rFE(int* arr, int k, int l, int r);
//
//void main() {
//
//	int n, k, * arr;
//
//	scanf("%d %d", &n, &k);
//
//	arr = (int*)malloc(sizeof(int) * n);
//
//	for (int i = 0; i < n; i++) {
//		scanf("%d", &arr[i]);
//	}
//
//	if (findElement(arr, n, k) == -1) {
//		if (maxindex == NULL)
//		{
//			printf(" %d\n", findElement(arr, n, k));
//		}
//		else
//		{
//			printf(" %d\n", maxindex);
//		}
//	}
//	else {
//		printf(" %d\n", findElement(arr, n, k));
//	}
//
//	free(arr);
//}
//
//int findElement(int* arr, int n, int k) {
//	return rFE(arr, k, 0, n - 1);
//}
//int rFE(int* arr, int k, int l, int r) {
//	int mid;
//
//	if (l > r) {
//		return -1;
//	}
//
//	mid = (l + r) / 2;
//
//	if (k == arr[mid]) {
//		return mid;
//	}
//	else if (k < arr[mid]) {
//		return rFE(arr, k, l, mid - 1);
//	}
//	else {
//		if (maxindex == NULL) {
//			maxindex = mid;
//		}
//		else if (arr[maxindex] < arr[mid]) {
//			maxindex = mid;
//		}
//		return rFE(arr, k, mid + 1, r);
//	}
//}
//
//

int findElement(int* arr, int l, int r, int k);
int rFE(int* arr, int l, int r, int k);

int main() {
	int n, k;
	scanf("%d %d", &n, &k);

	int* arr;
	arr = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	printf(" %d", findElement(arr, 0, n - 1, k));

}

int findElement(int* arr, int l, int r, int k) {
	rFE(arr, l, r, k);
}

int  rFE(int* arr, int l, int r, int k) {
	if (l > r) {
		return -1;
	}

	int mid = (l + r) / 2;

	if (k == arr[mid]) {
		return mid;
	} else if (arr[mid] < k) {
		rFE(arr, mid + 1, r, k);
	} else {
		rFE(arr, l, mid + 1, k);
	}
}