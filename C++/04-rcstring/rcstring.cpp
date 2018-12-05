#include "rcstring.h"

int main() {
    rcstring a, b, c, x;
    a = "bk 10";
    b = "ala MA kota";
	a = b;
	c = b;
    cout << "number = " << a.convertToInteger() << endl;
	cout << "string = " << a << endl;
	
	cout << "Get reference A " << a.getNcounter() << endl;
	cout << "Get reference B " << b.getNcounter() << endl;
	cout << "Get reference C " << c.getNcounter() << endl;
	
    b.convertToLowercase();
    cout << "lower = " << b << endl;
    cout << a << endl;
    cout << c << endl;
	
	cout << "Get reference A " << a.getNcounter() << endl;
	cout << "Get reference B " << b.getNcounter() << endl;
	cout << "Get reference C " << c.getNcounter() << endl;
    
	x = b.generateSubstring(5);
    cout << "3 fun from x = " << x << endl;
	cout << "3 fun from b = " << b << endl;
	cout << "3 fun from a = " << a << endl;
	cout << "3 fun from c = " << c << endl;
	
	cout << "Get reference A " << a.getNcounter() << endl;
	cout << "Get reference B " << b.getNcounter() << endl;
	cout << "Get reference C " << c.getNcounter() << endl;
	cout << "Get reference X " << x.getNcounter() << endl;
    return 0;
}
