#include "simpleSarADC.h"
#include <iostream>
using namespace std;


long pow(int base,int exp)
{
	int iter;
	long result=1;
	for(iter=1;iter<=exp;iter++)
	{
		result*=base;
	}
	return result;
}

simpleSarADC::simpleSarADC(int resolution)
{
	this->resolution=resolution;
	bitOut   = new int(resolution);
	mainCmp  = new comparator(0.0,20.0,false);
	mainCdac = new cdac(80.0);
}

long simpleSarADC::convert(double input)
{
	double curTime=0.0;
	double bitWeight=1.0;
	comparatorOut *dout;
	int iter,sign;
	long code;

	sign=1;
	mainCdac->reset();

	for(iter=1;iter<=resolution;iter++)
	{
		bitWeight/=2.0;
		mainCdac->applyStep(sign*bitWeight,curTime);
		curTime+=480;
		//cout<<mainCdac->getTopPlateVoltage(curTime)<<endl;
		dout=mainCmp->compare(input,mainCdac->getTopPlateVoltage(curTime),100,0.9);
		bitOut[iter]=dout->decision;
		sign=2*bitOut[iter]-1;
		//cout<<bitOut[iter]<<endl;
		curTime+=100;
		delete dout;
	}
	
	code=0;
	for(iter=1;iter<=resolution;iter++)
	{
		code+=pow(2,resolution-iter)*bitOut[iter];
	}

	return code;
}

