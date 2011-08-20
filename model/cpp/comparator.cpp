#include "comparator.h"
#include <cmath>
#include <iostream>
using namespace std;

comparator::comparator(double offset,double tau,bool async,double VDD)
{
	this->offset=offset;
	this->tau=tau;
	this->async=async;
	this->VDD=VDD;
}

comparatorOut* comparator::compare(double inp,double inm,double timeout)
{
	double readyTime;
	bool decision;
	bool timedout;
	double time;
	
	if(abs(inp-inm-offset)<1e-6)
	{
		inp=inm+offset+1e-6;
	}
	readyTime=tau*log(VDD/(abs(inp-inm-offset)));

	if(async==true)
	{
		if(readyTime>=timeout)
		{
			decision=false;
			time=timeout;
			timedout=true;
		}
		else
		{
			decision=((inp-inm)>offset)?true:false;
			time=readyTime;
			timedout=false;
		}
	}
	else
	{
		decision=((inp-inm-offset*exp(timeout/tau))>VDD)?true:false;
		time=timeout;
		timedout=false;
	}
//	if((inp-inm-offset)>1e-8)
//	{
//		readyTime=tau*log(VDD/(inp-inm-offset));
//	}
//	else
//	{
//		readyTime=1000000;
//	}
//	cout<<readyTime<<endl;
//	if(async==true)
//	{
//		if(readyTime>=timeout)
//		{
//			decision=false;
//			time=timeout;
//			timedout=true;
//		}
//		else
//		{
//			decision=((inp-inm)>offset)?true:false;
//			time=readyTime;
//			timedout=false;
//		}
//	}
//	else
//	{
//		decision=(inp-inm>offset)?true:false;
//		time=readyTime;
//		timedout=false;
//	}
	return (new comparatorOut(decision,timedout,time));
}

comparatorOut::comparatorOut(bool decision,bool isTimedOut,double time)
{
	this->decision=decision;
	this->isTimedOut=isTimedOut;
	this->time=time;
}


