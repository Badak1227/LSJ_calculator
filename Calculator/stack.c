#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	int data;
	struct stack* next;
}stack;

stack* newStack() {
	stack* tmp = (stack*)malloc(sizeof(stack));
	tmp->data = 0;
	tmp->next = NULL;
	return tmp;
}

void push(stack* head, int data) {
	stack* tmp = newStack();
	tmp->data = data;
	tmp->next = head;
	head = tmp;
}

void pop(stack* head) {
	stack* tmp = head;
	head = head->next;
	free(tmp);
}

int top(stack* head) {

	return head->data;
}

void freeStack(stack* head) {
	while (head != NULL) {
		pop(head);
	}
}