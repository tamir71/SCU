#include <iostream>
#include <iomanip>
#include "poly.h"

// Main Function Stuff
using namespace std;
using coen79_lab4::polynomial;

void printTest();

int main(int argc, const char * argv[])
{
	polynomial p1, p2;
	p1.assign_coef(5,29);
	p1.assign_coef(6,28);
	p1.assign_coef(7,17);
	p1.assign_coef(8,1);
	p1.assign_coef(9,0);
	p2.assign_coef(-2,29);
	p2.assign_coef(-2.5,28);
	p2.assign_coef(-3,17);
	p2.assign_coef(-3.5,1);
	p2.assign_coef(-4,0);
	p1 = p1 + p2;
        for(int i = 0; i < polynomial::CAPACITY; i++) {
            printf("%f\n", p1.coefficient(i));
        }
        cout << p1;
        return 0;
}
