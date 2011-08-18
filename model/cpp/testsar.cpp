#include "simpleSarADC.h"
#include <iostream>
using namespace std;

int main()
{
	simpleSarADC *adc = new simpleSarADC(5);
	adc->convert(0.45);
	return 1;
}
