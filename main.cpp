#include <iostream>
using namespace std;
#include <stdlib.h>
#include "config.h"

#ifdef USE_MYMATH
	#include "math/MathFunctions.h"
#else
	#include <cmath>
#endif

int main (int argc, char * argv[]) {
	if (argc < 3) {
		cout << "Usage " << argv[0] << " base exponent \n";
		return 1;
	}
	double base = atof(argv[1]);
	double exponent = atoi(argv[2]);
	double result = power(base, exponent);
	cout << base << '^' << exponent << " is " << result << endl;
	return 0;
}