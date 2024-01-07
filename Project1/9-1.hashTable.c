//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct HashBucket {
//	struct HashNode* hash;
//}HashBucket;
//
//typedef struct HashNode {
//	int node;
//	struct HashNode* next;
//}HashNode;
//
//int findHashIdx(int m, int node);
//void insertNode(HashBucket* hashBucket, int m, int node);
//int findNode(HashBucket* hashBucket, int m, int node);
//void printHashTable(HashBucket* hashBucket, int m);
//int deleteHashNode(HashBucket* hashBucket, int m, int node);
//
//int main() {
//	int m, node;
//	char cmd;
//	scanf("%d", &m);
//	HashBucket* hashBucket = (HashBucket*)malloc(m * sizeof(HashBucket));
//	for (int i = 0; i < m; i++) {
//		HashNode* hashNodeHead = (HashNode*)malloc(sizeof(HashNode));
//		hashNodeHead->next = NULL;
//		hashNodeHead->node = -1;
//
//		hashBucket[i].hash = hashNodeHead;
//	}
//
//	while (1) {
//		scanf("%c", &cmd);
//		switch (cmd)
//		{
//		case 'i':
//			scanf("%d", &node);
//			insertNode(hashBucket, m, node);
//			break;
//		case 's':
//			scanf("%d", &node);
//			printf("%d\n", findNode(hashBucket, m, node));
//			break;
//		case 'd':
//			scanf("%d", &node);
//			printf("%d\n", deleteHashNode(hashBucket, m, node));
//			break;
//		case 'p':
//			printHashTable(hashBucket, m);
//			break;
//		case 'e':
//			return;
//		default:
//			break;
//		}
//	}
//}
//
//int findHashIdx(int m, int node) {
//	return node % m;
//}
//
//void insertNode(HashBucket* hashBucket, int m, int node) {
//	int idx = findHashIdx(m, node);
//
//	HashNode* hashNode = hashBucket[idx].hash;
//
//	HashNode* newHashNode = (HashNode*)malloc(sizeof(HashNode));
//	newHashNode->node = node;
//	newHashNode->next = NULL;
//	
//	newHashNode->next = hashNode->next;
//	hashNode->next = newHashNode;
//}
//
//int findNode(HashBucket* hashBucket, int m, int node) {
//	int idx = findHashIdx(m, node);
//	HashNode* hashNode = hashBucket[idx].hash;
//
//	int cnt = 0;
//	while (hashNode->next != NULL) {
//		hashNode = hashNode->next;
//		cnt++;
//
//		if (hashNode->node != node && hashNode->next == NULL) return 0;
//		if (hashNode->node == node) break;
//	}
//
//	return cnt;
//}
//
//void printHashTable(HashBucket* hashBucket, int m) {
//	for (int i = 0; i < m; i++) {
//		HashNode* hashNode = hashBucket[i].hash;
//
//		while (hashNode->next != NULL) {
//			hashNode = hashNode->next;
//			printf(" %d", hashNode->node);
//		}
//	}
//	printf("\n");
//}
//
//int deleteHashNode(HashBucket* hashBucket, int m, int node) {
//	int idx = findHashIdx(m, node);
//	HashNode* hashNode = hashBucket[idx].hash;
//
//	if (hashNode->node == -1 && hashNode->next == NULL) return 0;
//
//	int cnt = 0;
//	while (hashNode->next != NULL) {
//		cnt++;
//		if (hashNode->next->node == node) break;
//		hashNode = hashNode->next;
//		
//		if (hashNode->node != node && hashNode->next == NULL) return 0;
//	}
//
//	hashNode->next = hashNode->next->next;
//
//	return cnt;
//}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bucket {
	struct Hash* hash;
}Bucket;

typedef struct Hash {
	int key;
	struct Hash* next;
}Hash;

int findIdx(int m, int key);
void insertHashTable(Bucket* hashTable, int key, int m);
void printHashTable(Bucket* hashTable, int m);
int findHashTable(Bucket* hashTable, int key, int m);
int deleteHashTable(Bucket* hashTable, int key, int m);

int main() {
	int m;
	scanf("%d", &m);

	// 해시테이블 초기화
	Bucket* HashTable = (Bucket*)malloc(sizeof(Bucket) * m);
	for (int i = 0; i < m; i++) {
		Hash* hashHead = (Hash*)malloc(sizeof(Hash*));
		hashHead->next = NULL;
		hashHead->key = -1;

		HashTable[i].hash = hashHead;
	}

	char cmd;
	int key, result;
	while (1) {
		scanf("%c", &cmd);
		switch (cmd)
		{
		case 'i':
			scanf("%d", &key);
			insertHashTable(HashTable, key, m);
			break;
		case 's':
			scanf("%d", &key);
			result = findHashTable(HashTable, key, m);
			printf("%d\n", result);
			break;
		case 'p':
			printHashTable(HashTable, m);
			break;
		case 'd':
			scanf("%d", &key);
			result = deleteHashTable(HashTable, key, m);
			printf("%d\n", result);
			break;
		case 'e':
			free(HashTable);
			return;
		default:
			break;
		}
	}
}

int findIdx(int m, int key) {
	return key % m;
}

void insertHashTable(Bucket* hashTable, int key, int m) {
	int idx = findIdx(m, key);

	Hash* hashHead = hashTable[idx].hash;

	Hash* newHashNode = (Hash*)malloc(sizeof(Hash));
	newHashNode->key = key;
	newHashNode->next = NULL;

	newHashNode->next = hashHead->next;
	hashHead->next = newHashNode;

	return;
}

void printHashTable(Bucket* hashTable, int m) {
	for (int i = 0; i < m; i++) {
		Hash* hashHead = hashTable[i].hash;
		while (hashHead->next != NULL) {
			hashHead = hashHead->next;
			printf(" %d", hashHead->key);
		}
	}
	printf("\n");
}

int findHashTable(Bucket* hashTable, int key, int m) {
	int idx = findIdx(m, key);
	Hash* hashNode = hashTable[idx].hash;

	int order = 0;
	while (hashNode->next != NULL) {
		hashNode = hashNode->next;
		order++;
		if (hashNode->key == key)
			return order;
	}
	return 0;
}

int deleteHashTable(Bucket* hashTable, int key, int m) {
	int idx = findIdx(m, key);
	Hash* hashHead = hashTable[idx].hash;

	if (hashHead->next == NULL) return 0;	// 삭제할 노드가 없는 경우

	int cnt = 0;
	while (hashHead->next != NULL) {
		cnt++;
		if (hashHead->next->key == key) break;
		hashHead = hashHead->next;
		
		if (hashHead->key != key && hashHead->next == NULL) return 0;
	}

	hashHead->next = hashHead->next->next;

	return cnt;
}
