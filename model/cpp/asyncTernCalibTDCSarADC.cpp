#include "asyncTernCalibTDCSarADC.h"
using namespace std;

asyncTernCalibTDCSarADC::asyncTernCalibTDCSarADC(int resolution)
{
	this->resolution=resolution;
	bitOut   = new int [resolution];
	add   = new int [resolution];
	sub   = new int [resolution];
	mainCmp  = new comparator(0.0,ctCmpTau,true);
	mainCdac = new cdac(ctDacTau);
	mainDelayLine = new delayLine(10,60,16);
	calibDelayLineP = new binDelayLine(1,16);
	calibDelayLineM = new binDelayLine(1,16);
	for(int count=0;count<6;count++)
	{
		auxDelayLine[count]=new binDelayLine(1,48)
	}

}

long asyncTernTDCSarADC::convert(double input)
{
	double curTime=0.0;
	double bitWeight=0.5,step;
	int iter,sign,isTimedOut;
	long code;
	int timeOut,timeOut1,timeOut2,timeOut3;
	int iStep;

	sign=1;
	isTimedOut=0;
	mainCdac->reset();
	mainCdac->applyStep(0.5*VREF,curTime);
	curTime+=ctDacTime*4;
	for(iter=1;iter<=resolution;iter+=2)
	{
		timeOut=double((iter)*ctCmpTau)*0.7;
		timeOut1=timeOut+0.47*ctCmpTau;
		timeOut2=timeOut+0.98*ctCmpTau;
		timeOut3=timeOut+2.08*ctCmpTau;

		bitOut[iter-1]=	mainCmp->compare(input,mainCdac->getTopPlateVoltage(curTime),timeOut3);
		curTime+=mainCmp->cmpTime();
		isTimedOut=mainCmp->isTimedOut();
		

		if(mainCmp->isTimedOut())
		{
			add[iter-1]=0;
			sub[iter-1]=0;
			add[iter]=0;
			sub[iter]=0;
		}
		else if(mainCmp->cmpTime()>timeOut2)
		{
			add[iter]=bitOut[iter-1];
			sub[iter]=1-bitOut[iter-1];
			add[iter-1]=0;
			sub[iter-1]=0;
		}
		else if(mainCmp->cmpTime()>timeOut1)
		{
			add[iter]=0;
			sub[iter]=0;
			add[iter-1]=bitOut[iter-1];
			sub[iter-1]=1-bitOut[iter-1];
		}
		else
		{
			add[iter]=bitOut[iter-1];
			sub[iter]=1-bitOut[iter-1];
			add[iter-1]=bitOut[iter-1];
			sub[iter-1]=1-bitOut[iter-1];
		}

		iStep=abs((add[iter-1]-sub[iter-1])*2+(add[iter]-sub[iter]));
		step=(add[iter-1]-sub[iter-1])*bitWeight/2.0+(add[iter]-sub[iter])*bitWeight/4.0;
		bitWeight/=4.0;
		curTime+=ctOverHeadTime;
		mainCdac->applyStep(step*VREF,curTime);
		curTime+=(iStep+2)*ctDacTime;
		//cout<<iStep<<"\t"<<isTimedOut<<endl;
		//cout<<iter<<"\t"<<step<<"\t"<<add[iter-1]-sub[iter-1]<<"\t"<<add[iter]-sub[iter]<<"\t"<<timeOut<<"\t"<<timeOut1<<"\t"<<timeOut2<<"\t"<<timeOut3<<"\t"<<mainCmp->cmpTime()<<"\t"<<isTimedOut<<endl;
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

void asyncTernTDCSarADC::dumpConvInfo()
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

int asyncTernTDCSarADC::getConvTime()
{
	return convTime;
}

asyncTernTDCSarADC::~asyncTernTDCSarADC()
{
	delete [] bitOut;
	delete [] add;
	delete [] sub;
	delete mainCdac;
	delete mainCmp;
}
