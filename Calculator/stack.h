#ifndef __STACK_H__ 
#define __STACK_H__

typedef struct stackNode {
	long long data;
	struct stackNode* next;
}sNode;

typedef struct stack {
	sNode* end;
}stack;

stack newStack();

sNode* get_sNode();

void push(long long data, stack* head);

long long pop(stack* head);

int top(stack* head);

int isEmptyStack(stack* head);

void freeStack(stack* head);
#endif