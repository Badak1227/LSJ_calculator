#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "queue.h"
#include "stack.h"

long long calc(queue exp) {
	stack operand = newStack();
	stack operator = newStack();

	int num = 0;

	int preOperatorCheck = 1; // 이전에 연산자가 왔는지 or 맨 처음인지 체크

	int minusCheck = 0; // -연산자가 연속으로 오는지 체크

	int plusCheck = 0; // +연산자가 연속으로 오는지 체크

	while (!isEmptyQueue(&exp)) {
		char cur = deQueue(&exp);

		if ('0' <= cur && cur <= '9') {
			num = num * 10 + (cur - '0');
		}
		else {
			if (preOperatorCheck == 1) {
				if (cur == '-' && minusCheck == 0) {
					push(-1, &operand);
					push('*', &operator);
					minusCheck = 1;
					plusCheck = 0;
				}
				else if (cur == '+' && plusCheck == 0) {
					push(1, &operand);
					push('*', &operator);
					plusCheck = 1;
					minusCheck = 0;
				}
				else {
					printf("ERROR: Invalid Experimen");
					freeQueue(&exp);
					freeStack(&operand);
					freeStack(&operator);
				}

				preOperatorCheck = 0;
			}
			else {
				if (cur == '(') {
					push('(', &operator);
					plusCheck = 0;
					minusCheck = 0;
				}
			}
		}
	}

	return 0;
}

//newQueue()와 newStack()으로 생성된 스택/큐는 지역변수
int input() {
	queue exp = newQueue();
	
	stack open = newStack(); // 괄호쌍 검사용 스택

	char cur = getc(stdin);

	if (cur == '\n') return 0; 

	while (cur != '\n') {
		if (cur == ' ') {
			cur = getc(stdin);
			continue;
		}

		//괄호, 숫자, 연산자 외 입력 검사
		if ('0' <= cur && cur <= '9' || cur <= '(' || cur == ')' || cur == '+' || cur == '-' || cur == '*' || cur == '/' || cur == '%' || cur == '^') {

			//괄호쌍 검사
			if (cur == '(') {
				push('(', &open);
			}
			else if (cur == ')') {
				if (isEmptyStack(&open) == NULL) {
					printf("ERROR: Invalid Pair Of Parentheses\n");

					while (getc(stdin) != '\n');

					freeQueue(&exp);
					return 1;
				}
				else {
					pop(&open);
				}
			}

			enQueue(cur, &exp);
			cur = getc(stdin);
		}
		else {
			printf("ERROR: Not An Operand or Operator\n");

			while (getc(stdin) != '\n');

			freeQueue(&exp);
			return 1;
		}
	}
	
	if (isEmptyStack(&open) != NULL) {
		printf("ERROR: Not An Operand or Operator\n");
		
		freeStack(&open);
		freeQueue(&exp);
		return 1;
	}

	calc(exp);
	freeQueue(&exp);
	return 1;
}

