#ifndef __QUEUE_H__ 
#define __QUEUE_H__

typedef struct queueNode {
	int data;
	struct queueNode* next;
}qNode;

typedef struct queue {
	qNode* front;
	qNode* rear;
}queue;

queue newQueue();

qNode* get_qNode();

void enqueue(queue* head, int data);

void dequeue(queue* head);

void freeQueue(queue* head);

#endif