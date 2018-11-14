#include "set_plus.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void error(char *err);

void error(const char* err) {
	printf("%s", err);
	abort();
}


Stack::Stack(){
	set = (int*)malloc(2 * sizeof(int));
	if(set) {
		size = 2;
		capacity = 0;
	}else error("Failed to allocate stack");
}

Stack::~Stack(){
	free(set);
}


void Stack::growth_stack(){
	set = (int*)realloc(set, 2 * size * sizeof(int));
	if(set) size = 2 * size;
	else error("Failed to allocate stack");
}


void Stack::shrink_stack(){
	if(size > 2){
		set = (int*)realloc(set, size * sizeof(int) / 2);
		if(set) size = size / 2;
		else error("Failed to allocate stack");
	}
}


void Stack::push(int value){
	if(capacity == size) growth_stack();
    *(set + capacity) = value;
    capacity += 1;
}


int Stack::pop(){
	if(isEmpty()) error("Stack is empty");
    capacity -= 1;
    if(capacity * 3 < size) shrink_stack();
    return *(set + capacity);
} 

int Stack::getSize(){
	return size;
}

int Stack::getCapacity(){
	return capacity;
}

  
bool Stack::isEmpty(){
    if(capacity == 0) return true;
    return false;
}
