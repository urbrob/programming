#ifndef SET_PLUS_H_   
#define SET_PLUS_H_
#include <stdbool.h>



class Stack {
private:
	int *set;
	int size;
	int capacity;
	void shrink_stack();
	void growth_stack();
	
public:
	Stack();
	~Stack();
	int getSize();
	int getCapacity();
	void push(int value);
	int pop();
	bool isEmpty();

};

#endif
