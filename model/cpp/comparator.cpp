#include "comparator.h"
#include <cmath>
#include <iostream>
using namespace std;

comparator::comparator(double offset,double tau,bool async)
{
	this->offset=offset;
	this->tau=tau;
	this->async=async;
}

comparatorOut* comparator::compare(double inp,double inm,double timeout,double VDD)
{
	double readyTime;
	bool decision;
	bool timedout;
	double time;
	readyTime=tau*log(VDD/(inp-inm));
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
		decision=(inp-inm>offset)?true:false;
		time=readyTime;
		timedout=false;
	}
	return (new comparatorOut(decision,timedout,time));
}

comparatorOut::comparatorOut(bool decision,bool isTimedOut,double time)
{
	this->decision=decision;
	this->isTimedOut=isTimedOut;
	this->time=time;
}


