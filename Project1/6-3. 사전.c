#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int findElement(int* arr, char* cmd);
int len;

int main() {
	int a, b, n, * arr;
	scanf("%d %d %d", &a, &b, &n);
	getchar();

	len = b - a + 1;

	arr = (int*)malloc(sizeof(int) * (b - a + 1));
	for (int i = 0; i <= b - a; i++) {
		arr[i] = a + i;
	}

	char* cmd = (char*)malloc(sizeof(char) * (n + 1));
	gets(cmd);

	printf("%d", findElement(arr, cmd));
	free(cmd);
}

int findElement(int* arr, char* cmd) {
	int mid, left = 0, right = len - 1, i = 0;

	while (1) {
		if (left > right) {
			return -1;
		}

		mid = (left + right) / 2;
		if (left == right) {
			return arr[left];
		}
		else {
			if (cmd[i] == 'Y') {	// m + 1 <= k <= b
				left = mid + 1;
			}
			else {	// a <= k <= m
				right = mid;
			}
			i++;
		}
	}
}

