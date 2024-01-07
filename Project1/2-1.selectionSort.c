#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, indexMin = 0;
	scanf("%d", &n);

	int* arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	/*for (int i = 0; i < n - 1; i++) {
		int idxMin = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[idxMin]) {
				idxMin = j;
			}
		}
		int tmp = arr[i];
		arr[i] = arr[idxMin];
		arr[idxMin] = tmp;
	}*/

	for (int i = 1; i < n; i++) {
		int save = arr[i];
		int j = i - 1;
		while ((j >= 0) && (arr[j] > save)) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = save;
	}

	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

	free(arr);
}