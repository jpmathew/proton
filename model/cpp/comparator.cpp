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

bool comparator::compare(double inp,double inm,double timeout)
{
	double readyTime;

	if(abs(inp-inm-offset)<1e-8)
	{
		inp=inm+offset-1e-8;
	}
	
	readyTime=tau*log(VDD/(abs(inp-inm-offset)));

	if(async==true)
	{
		if(readyTime>=timeout)
		{
			decision=false;
			time=timeout;
			timedOut=true;
		}
		else
		{
			decision=((inp-inm)>offset)?true:false;
			time=readyTime;
			timedOut=false;
		}
	}
	else
	{
		decision=(((inp-inm-offset)*exp(timeout/tau))>VDD)?true:false;
		time=timeout;
		timedOut=false;
	}
	
	return decision;
}


bool comparator::isTimedOut()
{
	return timedOut;
}

double comparator::cmpTime()
{
	return time;
}

comparator::~comparator()
{
}



