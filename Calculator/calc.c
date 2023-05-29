#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "queue.h"
#include "stack.h"

void caculate(stack* operand, stack* operator) {
	while (!isEmptyStack(operator)) {

		char sign = pop(operator);
		if (sign == '(') break;

		long long num2 = pop(operand), num1 = pop(operand);

		if (sign == '+') {
			push(num1 + num2, operand);
		}
		else if (sign == '-') {
			push(num1 - num2, operand);
		}
		else if (sign == '*') {
			push(num1 * num2, operand);
		}
		else if (sign == '/') {
			push(num1 / num2, operand);
		}
		else if (sign == '%') {
			push(num1 % num2, operand);
		}
		else if (sign == '^') {
			push(num1 ^ num2, operand);
		}
	}
	
}

void calc(queue* exp) {
	stack operand = newStack();
	stack operator = newStack();

	int num = 0;

	int preOperatorCheck = 1; // 이전에 연산자가 왔는지 or 맨 처음인지 체크

	int minusCheck = 0; // -연산자가 연속으로 오는지 체크

	int plusCheck = 0; // +연산자가 연속으로 오는지 체크

	int overflowCheck = 0;

	while (!isEmptyQueue(exp)) {
		char cur = deQueue(exp);

		if ('0' <= cur && cur <= '9') {
			num = num * 10 + (cur - '0');

			preOperatorCheck = 0;
			minusCheck = 0;
			plusCheck = 0;
		}
		else {
			if (cur == '-') {
				if (preOperatorCheck == 1) {
					if (minusCheck == 1) {
						printf("ERROR: Invalid Experiment");
						break;
					}

					push(-1, &operand);
					push('*', &operator);
					minusCheck = 1;
				}
				else {
					push(num, &operand);
					num = 0;

					if (!isEmptyStack(&operator)) {
						char prev = top(&operator);
						if (prev == '*' || prev == '/' || prev == '%' || prev == '^') {
							caculate(&operand, &operator);
						}
					}

					
					push(cur, &operator);

					preOperatorCheck = 1;
					minusCheck = 0;
				}

				plusCheck = 0;
			}
			else if (cur == '+') {

				if (preOperatorCheck == 1) {

					if (plusCheck == 1) {
						printf("ERROR: Invalid Experiment");
						break;
					}

					push(1, &operand);
					push('*', &operator);
					plusCheck = 1;
				}
				else {
					push(num, &operand);
					num = 0;

					if (!isEmptyStack(&operator)){
						char prev = top(&operator);
						if (prev == '*' || prev == '/' || prev == '%' || prev == '^') {
							caculate(&operand, &operator);
						}
					}

					
					push(cur, &operator);

					preOperatorCheck = 1;
					plusCheck = 0;
				}

				minusCheck = 0;
			}
			else if (cur == '*' || cur == '/' || cur == '%') {

				if (preOperatorCheck == 1) {
					printf("ERROR: Invalid Experiment", top(&operand), cur);
					break;
				}
				
				if (!isEmptyStack(&operator)) {
					char prev = top(&operator);
					if (prev == '^') {
						caculate(&operand, &operator);
					}
				}

				push(num, &operand);
				num = 0;
				push(cur, &operator);
				
				preOperatorCheck = 1;
				plusCheck = 0;
				minusCheck = 0;
			}
			else if (cur == '^') {
				if (preOperatorCheck == 1) {
					printf("ERROR: Invalid Experiment", top(&operand), cur);
					break;
				}

				push(num, &operand);
				num = 0;
				push(cur, &operator);

				preOperatorCheck = 1;
				plusCheck = 0;
				minusCheck = 0;
			}
			else if (cur == '(') {
				if (preOperatorCheck == 0) {
					printf("ERROR: Invalid Experiment", top(&operator), cur);
					break;
				}
				
				push(num, &operand);
				num = 0;
				push('(', &operator);

				plusCheck = 0;
				minusCheck = 0;
			}
			else if (cur == ')') {
				if (preOperatorCheck == 1) {
					printf("ERROR: Invalid Experiment", top(&operator), cur);
					break;
				}

				push(num, &operand);
				num = 0;
				caculate(&operand, &operator);

				plusCheck = 0;
				minusCheck = 0;
			}
		}
	}

	push(num, &operand);
	caculate(&operand, &operator);

	if (overflowCheck) {
		printf("ERROR: OverFlow Occured");
	}
	else {
		printf("%d\n", top(&operand));
	}

	freeStack(&operand);
	freeStack(&operator);
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
		if (('0' <= cur && cur <= '9') || cur == '(' || cur == ')' || cur == '+' || cur == '-' || cur == '*' || cur == '/' || cur == '%' || cur == '^') {

			//괄호쌍 검사
			if (cur == '(') {
				push('(', &open);
			}
			else if (cur == ')') {
				if (isEmptyStack(&open)) {
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
	
	if (!isEmptyStack(&open)) {
		printf("ERROR: Not An Operand or Operator\n");
		
		freeStack(&open);
		freeQueue(&exp);
		return 1;
	}

	calc(&exp);
	freeQueue(&exp);
	return 1;
}

