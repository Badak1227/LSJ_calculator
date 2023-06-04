TARGET = Calculator_20203082.out

all : $(TARGET)

$(TARGET) : main.o calc.o stack.o queue.o
	gcc -o $(TARGET) main.o calc.o stack.o queue.o -lm
	
main.o :
	gcc -c main.c

calc.o :
	gcc -c calc.c

stack.o :
	gcc -c stack.c

queue.o :
	gcc -c queue.c
