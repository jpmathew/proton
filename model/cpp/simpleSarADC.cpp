#include "simpleSarADC.h"
using namespace std;

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
	int iter,sign,diter;
	long code;

	sign=1;
	mainCdac->reset();

	for(iter=1;iter<=resolution;iter++)
	{
		bitWeight/=2.0;
		mainCdac->applyStep(sign*bitWeight,curTime);
		curTime+=dacTime;

		dout=mainCmp->compare(input,mainCdac->getTopPlateVoltage(curTime),100,0.9);
		bitOut[iter]=dout->decision;
		sign=2*bitOut[iter]-1;
		curTime+=cmpTime;

		delete dout;
	}
	
	code=0;
	for(iter=1;iter<=resolution;iter++)
	{
		code+=pow(2,resolution-iter)*bitOut[iter];
	}

	convTime=curTime;
	return code;
}

void simpleSarADC::dumpConvInfo()
{
	int infoSmplTime=20;
	int curTime=0;
	int iter;

	ofstream dacFile("dac.dat",ios::out);
	ofstream bitFile("bit.dat",ios::out);

	for(iter=0;iter<resolution;iter++)
	{
		bitFile<<bitOut[iter]<<endl;
	}
	
	while(curTime<convTime)
	{
		dacFile<<mainCdac->getTopPlateVoltage(curTime)<<endl;
		curTime+=infoSmplTime;
	}

	dacFile.close();
	bitFile.close();
}

simpleSarADC::~simpleSarADC()
{
	delete [] bitOut;
}
