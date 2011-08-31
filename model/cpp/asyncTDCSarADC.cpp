#include "asyncTDCSarADC.h"
using namespace std;

asyncTDCSarADC::asyncTDCSarADC(int resolution)
{
	this->resolution=resolution;
	bitOut   = new int [resolution];
	add   = new int [resolution];
	sub   = new int [resolution];
	mainCmp  = new comparator(0.0,ctCmpTau,true);
	mainCdac = new cdac(ctDacTau);
}

long asyncTDCSarADC::convert(double input)
{
	double curTime=0.0;
	double bitWeight=1.0;
	int iter,sign,isTimedOut;
	long code;
	int timeOut;

	sign=1;
	isTimedOut=0;
	mainCdac->reset();
	for(iter=1;iter<=resolution;iter++)
	{
		bitWeight/=2.0;
		mainCdac->applyStep(sign*bitWeight*VREF,curTime);
		if(sign!=0)
		{
			curTime+=ctDacTime;
		}
		timeOut=double((iter+2)*ctCmpTau)*0.69;
		bitOut[iter-1]=	mainCmp->compare(input,mainCdac->getTopPlateVoltage(curTime),timeOut);
		curTime+=mainCmp->cmpTime();
		isTimedOut=mainCmp->isTimedOut();
		add[iter-1]=(1-isTimedOut)*bitOut[iter-1];
		sub[iter-1]=(1-isTimedOut)*(1-bitOut[iter-1]);
		sign=add[iter-1]-sub[iter-1];
		//cout<<iter<<"\t"<<sign<<"\t"<<timeOut<<"\t"<<mainCmp->cmpTime()<<"\t"<<isTimedOut<<endl;
	}
	
	code=0;
	for(iter=1;iter<=resolution;iter++)
	{
		code+=pow(2,resolution-iter)*(add[iter-1]-sub[iter-1]);
	}
	code=code+pow(2,resolution);
	code/=2;

	convTime=curTime;
	return code;
}

void asyncTDCSarADC::dumpConvInfo()
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

int asyncTDCSarADC::getConvTime()
{
	return convTime;
}

asyncTDCSarADC::~asyncTDCSarADC()
{
	delete [] bitOut;
	delete [] add;
	delete [] sub;
	delete mainCdac;
	delete mainCmp;
}
