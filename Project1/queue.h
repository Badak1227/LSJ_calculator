#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct queueNode {
	int data;
	struct queueNode* next;
}qNode;

typedef struct queue {
	qNode* front;
	qNode* rear;
}queue;

queue newQueue() {
	queue tmp;
	tmp.front = NULL;
	tmp.rear = NULL;

	return tmp;
}

qNode* get_qNode() {
	qNode* tmp = (qNode*)malloc(sizeof(qNode));
	tmp->data = 0;
	tmp->next = NULL;
}

void enqueue(queue* head, int data) {
	qNode* tmp = get_qNode();
	tmp->data = data;

	if (head->front == NULL) {
		head->front = tmp;
		head->rear = tmp;
		return;
	}

	head->rear->next = tmp;

	head->rear = tmp;
}

void dequeue(queue* head) {
	qNode* tmp = head->front;

	if (head->front == head->rear) head->rear = NULL;

	head->front = head->front->next;

	free(tmp);
}

void freeQueue(queue* head) {
	while (head->front != NULL) {
		dequeue(head);
	}
}