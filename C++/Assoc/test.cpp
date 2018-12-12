#include "assoctab.h"
#include <iostream>
using namespace std;

int main() {
    caseAssocTab a1, a2;
    a1["ala"] = 1;
    a1["ola"] = 2;
    cout << a1["ala"] << " " << a1["ola"] << " " << a1["ula"] << endl;
    a1["ula"]++;
    cout << a1["Ala"] << " " << a1["oLa"] << " " << a1["uLa"] << endl;
    
    cout << "KONIEC TESTU CASE SENSITIVE" << endl;

    nonCaseAssocTab b1, b2;
    b1["ala"] = 3;
    b1["ola"] = 4;
    cout << b1["ala"] << " " << b1["ola"] << " " << b1["ula"] << endl;
    b1["uLa"]++;
    b2["olada"]++;
    cout << b1["alA"] << " " << b1["oLa"] << " " << b1["ulA"] << endl;
    cout << b2["olada"] << " " << b2["olA"] << " " << b2["Ula"] << endl;
    cout << b1["dla"] << " " << b1["owa"] << " " << b1["uaa"] << endl;
    cout << "KONIEC TESTU NON CASE SENSITIVE" << endl;
    return 0;
}
