#include "asyncSarADC.h"
#include "xnlCompute.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ofstream dataOut("data.dat",ios::out);
	ofstream cnvTimeOut("cnvTime.dat",ios::out);
	asyncSarADC *adc = new asyncSarADC(10);
	xnlCompute *linTest = new xnlCompute(10);
	double input;
	long code;
	int rampTest=11
	if(rampTest==1)
	{
		for(input=0.0;input<0.0001;input+=0.00001)
		{
			code=adc->convert(input);
			cout<<code<<"\t"<<input<<endl;
			dataOut<<code<<endl;
			cnvTimeOut<<adc->getConvTime()<<endl;	
		}
	}
	else
	{
		code=adc->convert(0.0+0.00001);
		cout<<code<<endl;
		adc->dumpConvInfo();
	}
	linTest->computeLin("data.dat");
	return 1;
}
