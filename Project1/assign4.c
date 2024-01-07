#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int findHashIdx(int m, int n);	// 해시테이블 인덱스 리턴하는 함수
int insertNumbertoHashTable(int* arr, int m, int n);	// 해시테이블에 키를 삽입하는 함수
int deleteNumbertoHashTable(int* arr, int m, int n);	// 해시테이블에서 키를 삭제하는 함수
int searchNumbertoHashTable(int* arr, int m, int n);	// 해시테이블에서 키를 탐색하는 함수

int main() {
	int m, n;
	char cmd;
	scanf("%d", &m);	// 해시테이블 크기 입력

	int* arr = (int*)malloc(sizeof(int) * m);	// 해시테이블 동적할당
	for (int i = 0; i < m; i++) arr[i] = 0;	// empty sell로 초기화

	while (1) {
		scanf("%c", &cmd);	// 명령어 입력
		switch (cmd)
		{
		case 'i':
			scanf("%d", &n);	// 키 입력
			printf("%d\n", insertNumbertoHashTable(arr, m, n));	// 해시테이블에 키 삽입
			break;
		case 'd':
			scanf("%d", &n);	// 키 입력
			printf("%d\n", deleteNumbertoHashTable(arr, m, n));	// 해시테이블에서 키 삭제
			break;
		case 's':
			scanf("%d", &n);	// 키 입력
			printf("%d\n", searchNumbertoHashTable(arr, m, n));	// 해시테이블에서 키 탐색
			break;
		case 'e':
			free(arr);	// 해시테이블 메모리 해제 후 프로그램 종료
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
		if (arr[idx] == 0 || arr[idx] == -1)	// 빈 셀, 비활성화 셀
		{
			arr[idx] = n;	// 키 삽입
			return idx;
		}
		printf("C");	// 충돌
		if (idx == prevIdx && arr[idx] > 0) return -1;	// 빈 공간이 없을 때
		idx++;
		if (idx == m) idx = 0;	
	}
}

int deleteNumbertoHashTable(int* arr, int m, int n) {
	int idx = findHashIdx(m, n);
	int prevIdx = (idx == 0 ? m - 1 : idx - 1);

	while (1) {
		if (arr[idx] == 0) return -1;	// 빈 셀
		if (arr[idx] == n) {	// 키 발견
			arr[idx] = -1;
			return idx;
		}
		printf("C");	// 충돌
		if (idx == prevIdx && arr[idx] != n) return -1;	// 다 돌았는데 노드가 없을 때
			
		idx++;
		if (idx == m) idx = 0;
	}
}

int searchNumbertoHashTable(int* arr, int m, int n) {
	int idx = findHashIdx(m, n);
	int prevIdx = (idx == 0 ? m - 1 : idx - 1);

	while (1) {
		if (arr[idx] == 0) return -1;	// 빈 인덱스 발견
		
		if (arr[idx] == n) return idx;	// 키 발견

		printf("C");	// 충돌
		if (idx == prevIdx && arr[idx] != n) return -1;	// 끝까지 다 돌았을 때

		idx++;
		if (idx == m) idx = 0;
	}
}
