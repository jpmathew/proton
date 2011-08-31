#include "asyncTDCSarADC.h"
#include "xnlCompute.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ofstream dataOut("data.dat",ios::out);
	ofstream cnvTimeOut("cnvTime.dat",ios::out);
	asyncTDCSarADC *adc = new asyncTDCSarADC(10);
	xnlCompute *linTest = new xnlCompute(10);
	double input;
	long code;
	int rampTest=1;
	if(rampTest==1)
	{
		for(input=0.0;input<0.9;input+=0.00001)
		{
			code=adc->convert(input);
			dataOut<<code<<endl;
			cnvTimeOut<<adc->getConvTime()<<endl;
		}
	}
	else
	{
		code=adc->convert(0.45);
		cout<<code<<endl;
	}
	linTest->computeLin("data.dat");

	delete adc;
	delete linTest;

	return 1;
}
