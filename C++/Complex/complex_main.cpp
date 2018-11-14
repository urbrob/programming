#include <iostream>
#include "complex.h"

int main(){
	Complex a, b, c;
	b.set_real(1);
	b.set_imaginary(1);
	a.set_real(1);
	a.set_imaginary(1);
	
	c = a + b;
	std::cout << c.get_real() << '\n';
	c += a += b;
	std::cout << c.get_real() << '\n';
	c *= a *= b;
	std::cout << c.get_real() << '\n';
	/*c = a - b;
	std::cout << c.get_real() << '\n';
	c = a / b;
	std::cout << c.get_real() << '\n';
	c = a * b;
	std::cout << c.get_real() << '\n';
	c = a + 4;
	std::cout << c.get_real() << '\n';
	c = a - 2;
	std::cout << c.get_real() << '\n';
	c = a * 4 ;
	std::cout << c.get_real() << '\n';
	*/return 0;
}
