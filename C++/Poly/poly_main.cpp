#include "poly.h"														// Defines class Poly
#include <iostream>

using namespace std;

void test(const Poly& p1, const Poly& p2);

int main() {
	Poly p1;															// Declare object representing polynomial p1
	p1[3] = 2;															// Specify coefficients of p1 = 2x^3 + 3.6x + 7
	p1[1] = -3.2;
	p1[0] = 1;

	Poly p2 = 5;														// Declare object representing polynomial p2 = 5
	p2[4] = 1;															// Specify additional coefficients of p2 = x^4 - 6x^2 + 3x + 5
	p2[2] = -6;
	p2[1] = 3;
	test(p1, p2);
}

void test(const Poly& p1, const Poly& p2) {
	cout << "Polynomial p1: " << p1 << endl;
	cout << "Polynomial p2: " << p2 << endl;

	cout << "Sum of polynomials p1 and p2: " << p1 + p2 << endl;

	cout << "Difference of polynomials p1 and p2: " << p1 - p2 << endl;
	cout << "Difference of polynomials p1 and p1: " << p1 - p1 << endl;	// Should display 0 (not 0x^3 + 0x + 0)
	cout << "WAT";
	cout << "Product of polynomials p1 and p2: " << p1 * p2 << endl;

	cout << "Negation of polynomial p2: " << -p2 << endl;
	cout << "Negation of polynomial p2: " << p2 << endl;

	cout << "Value of polynomial p1 at point 1.5: " << p1(1.5) << endl;
}
