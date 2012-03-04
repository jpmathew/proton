#include "asyncTernCalibTDCSarADC.h"
using namespace std;

asyncTernCalibTDCSarADC::asyncTernCalibTDCSarADC(int resolution)
{
	this->resolution=resolution;
	bitOut  = new int [resolution];
	add    	= new int [resolution];
	sub  	= new int [resolution];
	mainCmp  = new comparator(0.0,ctCmpTau,true);
	mainCdac = new cdac(ctDacTau);
	mainDelayLine = new delayLine(10,0,16);
	for(int count=0;count<6;count++)
	{
		fineDelayLine[count]=new binDelayLine(1,64)
	}
	calibRom = new calibBlock [resolution/2];
}

long asyncTernCalibTDCSarADC::convert(double input)
{
	double curTime=0.0;
	double bitWeight=0.5,step;
	int iter,count,sign,isTimedOut;
	long code;
	int iStep;
	int timeOut[6];

	sign=1;
	isTimedOut=0;
	mainCdac->reset();
	mainCdac->applyStep(0.5*VREF,curTime);
	curTime+=ctDacTime*4;
	for(iter=1,count=0;iter<=resolution;iter+=2,count++)
	{
		timeOut[0]=mainDelayLine->getDelay(calibRom[count].main)+fineDelayLine[count].getDelay(calibRom[count].fine[0]);
		timeOut[1]=mainDelayLine->getDelay(calibRom[count].main)+fineDelayLine[count].getDelay(calibRom[count].fine[1]);
		timeOut[2]=mainDelayLine->getDelay(calibRom[count].main)+fineDelayLine[count].getDelay(calibRom[count].fine[2]);
		timeOut[3]=mainDelayLine->getDelay(calibRom[count].main)+fineDelayLine[count].getDelay(calibRom[count].fine[3]);
		timeOut[4]=mainDelayLine->getDelay(calibRom[count].main)+fineDelayLine[count].getDelay(calibRom[count].fine[4]);
		timeOut[5]=mainDelayLine->getDelay(calibRom[count].main)+fineDelayLine[count].getDelay(calibRom[count].fine[5]);
		
		int max=0;
		for(int count1 =0;count1<6;count++)
		{
			if(timOut[count1]>max)
			{
				max=timeOut[count1];
			}
		}

		bitOut[iter-1]=	mainCmp->compare(input,mainCdac->getTopPlateVoltage(curTime),max);
		curTime+=mainCmp->cmpTime();
		
		if(bitOut[iter-1]==1)
		{
			if(timeOut[0]<



		
			
			
			
			
			
			
			
			
			
			
			
			
			if(mainCmp->cmpTime()>timeOut2)
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
	code=code+pow(2,resolution)http://news.softpedia.com/;
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
		curTime+=infoSmplTime;http://news.softpedia.com/
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
