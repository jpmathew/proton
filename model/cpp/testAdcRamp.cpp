#include "simpleSarADC.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ofstream dataOut("data.dat",ios::out);
	simpleSarADC *adc = new simpleSarADC(5);
	double input;
	long code;
	
	for(input=0.0;input<1.0;input+=0.001)
	{
		code=adc->convert(input);
		//cout<<code<<endl;
		dataOut<<code<<endl;
	}

	return 1;
}
