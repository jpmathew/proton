#include "asyncSarADC.h"
using namespace std;

asyncSarADC::asyncSarADC(int resolution)
{
	this->resolution=resolution;
	bitOut   = new int(resolution);
	mainCmp  = new comparator(0.0,20.0,true,0.9);
	mainCdac = new cdac(80.0);
}

long asyncSarADC::convert(double input)
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
		mainCdac->applyStep(sign*bitWeight*VREF,curTime);
		curTime+=ctDacTime;

		dout=mainCmp->compare(input,mainCdac->getTopPlateVoltage(curTime),ctCmpTime);
		bitOut[iter-1]=dout->decision;
		curTime+=dout->time;
		sign=2*bitOut[iter-1]-1;
		delete dout;
	}
	
	code=0;
	for(iter=1;iter<=resolution;iter++)
	{
		code+=pow(2,resolution-iter)*bitOut[iter-1];
	}

	convTime=curTime;
	return code;
}

void asyncSarADC::dumpConvInfo()
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

int asyncSarADC::getConvTime()
{
	return convTime;
}

asyncSarADC::~asyncSarADC()
{
	delete [] bitOut;
}
