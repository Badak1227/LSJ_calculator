#ifndef __STACK_H__ 
#define __STACK_H__

typedef struct stack {
	int data;
	struct stack* next;
}stack;

stack* newStack();

void push(stack* head, int data);

void pop(stack* head);

int top(stack* head);

void freeStack(stack* head);

#endif