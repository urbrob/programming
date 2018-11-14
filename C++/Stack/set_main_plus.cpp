#include <stdio.h>
#include "set_plus.h"

int main(){
	Stack stack1, stack2;
	printf("Stack1 :\n %d - capacity\n	 %d - size\n  %d - is_empty\n ", stack1.getCapacity(), stack1.getSize(), stack1.isEmpty());
	stack1.push(5);
	stack1.push(1);
	stack1.push(2);
	stack1.push(7);
	stack1.push(16);
	printf("Stack1 :\n	%d - capacity\n	 %d - size\n  %d - is_empty\n", stack1.getCapacity(), stack1.getSize(), stack1.isEmpty());
	printf("Stack2 :\n	%d - capacity\n	 %d - size\n  %d - is_empty\n ", stack2.getCapacity(), stack2.getSize(), stack2.isEmpty());
	stack2.push(7);
	stack2.push(11);
	stack2.push(8);
	stack2.push(7);
	stack2.push(7);
	stack2.push(123);
	stack2.push(743);
	printf("Stack2 :\n	%d - capacity\n	 %d - size\n  %d - is_empty\n\n", stack2.getCapacity(), stack2.getSize(), stack2.isEmpty());

	printf("%d ", stack2.pop());
	printf("%d ", stack2.pop());
	printf("%d ", stack2.pop());
	printf("%d ", stack2.pop());
	printf("%d ", stack2.pop());
	printf("%d ", stack2.pop());
	printf("%d \n\n", stack2.pop());
	printf("Stack2 :\n	%d - capacity\n	 %d - size\n\n", stack2.getCapacity(), stack2.getSize());


	printf("%d ", stack1.pop());
	printf("%d ", stack1.pop());
	printf("%d ", stack1.pop());
	printf("%d ", stack1.pop());
	printf("%d \n\n", stack1.pop());
	printf("Stack1 :\n	%d - capacity\n	 %d - size\n", stack1.getCapacity(), stack1.getSize());

	return 0;
}


