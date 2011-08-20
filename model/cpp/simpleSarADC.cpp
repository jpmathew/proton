#include "simpleSarADC.h"
using namespace std;

simpleSarADC::simpleSarADC(int resolution)
{
	this->resolution=resolution;
	bitOut   = new int(resolution);
	dacVals  = new double(resolution*5);
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

		for(diter=0;diter<5;di
		dacVals[iter]=mainCdac->getTopPlateVoltage(curTime);



		curTime+=280;
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

void simpleSarADC::dumpConvInfo()
{
	ofstream dacFile("dac.dat",ios::out);
	ofstream bitFile("bit.dat",ios::out);
	int iter;

	for(iter=0;iter<resolution;iter++)
	{
		dacFile<<dacVals[iter]<<endl;
		bitFile<<bitOut[iter]<<endl;
	}

	dacFile.close();
	bitFile.close();
}

simpleSarADC::~simpleSarADC()
{
	delete [] bitOut;
	delete [] dacVals;
}
