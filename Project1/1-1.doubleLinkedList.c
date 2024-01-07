#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct DNODE {	// ����ü ����
	struct DNODE* prev;	// ���� ��ũ
	char data;
	struct DNODE* next;	// ���� ��ũ
}NODE;

NODE* head, * tail;

NODE* makenode(char data);
void init();
void print();
void add(int rank, char data);
void delete(int rank);
void get(int rank);

void main() {
	init();
	int n;
	scanf("%d", &n);
	getchar();

	for (int i = 0; i < n; i++) {
		char cmd_line[6], cmd, text;
		int rank;

		gets(cmd_line);
		cmd = cmd_line[0];

		switch (cmd)
		{
		case 'A' :
			rank = cmd_line[2] - 48;
			text = cmd_line[4];
			add(rank, text);
			break;
		case 'D' :
			rank = cmd_line[2] - 48;
			delete(rank);
			break;
		case 'G' :
			rank = cmd_line[2] - 48;
			get(rank);
			break;
		case 'P' :
			print();
			break;
		default:
			break;
		}
	}
}

NODE* makenode(char data) {	// ��� ����
	NODE* p = (NODE*)malloc(sizeof(NODE));
	p->data = data;
	p->next = NULL;
	p->prev = NULL;
	return p;
}

void init() {	// head, tail �ʱ�ȭ
	head = (NODE*)malloc(sizeof(NODE));
	tail = (NODE*)malloc(sizeof(NODE));
	head->data = '0';
	tail->data = '0';

	head->next = tail;
	head->prev = head;
	tail->prev = head;
	tail->next = tail;
}

void print() {	// ���
	NODE* p;
	p = head->next;

	while (p->next != tail) {
		printf("%c", p->data);
		p = p->next;
	}

	printf("%c\n", p->data);
}

void add(int rank, char data) {	// ��� ����
	NODE* newnode = makenode(data);
	NODE* p;
	p = head;

	if (head->next == tail) {
		p->next->prev = newnode;
		newnode->next = p->next;
		p->next = newnode;
		newnode->prev = p;
	}
	else {
		for (int i = 0; i < rank - 1; i++) {
			p = p->next;
		}

		newnode->prev = p;
		newnode->next = p->next;
		p->next = newnode;
		newnode->next->prev = newnode;
	}
}

void delete(int rank) { // ��� ����
	NODE* p;
	p = head;

	for (int i = 0; i < rank - 1; i++) {
		p = p->next;
	}

	p->next->next->prev = p;
	p->next = p->next->next;
}

void get(int rank) { // ��� ��ȯ
	NODE* p;
	p = head->next;
	for (int i = 0; i < rank - 1; i++) {
		p = p->next;
		if (p == tail) {
			break;
		}
	}

	if (p == tail) {
		printf("invalid position\n");
	}
	else {
		printf("%c\n", p->data);
	}
}