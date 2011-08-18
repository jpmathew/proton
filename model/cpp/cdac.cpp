#include "cdac.h"
#include <cmath>
#include <iostream>
using namespace std;

step::step(double stepValue,double stepTime)
{
	prev=0;
	this->stepValue=stepValue;
	this->stepTime=stepTime;
}

cdac::cdac(double tau)
{
	this->tau=tau;
	topPlateVoltage=0.0;
	last = new step(0,1);
}

void cdac::reset()
{
	step *stepIter;
	stepIter=last;
	while(stepIter->prev!=0)
	{
		last=stepIter->prev;
		delete stepIter;
		stepIter=last;
	}
	topPlateVoltage=0.0;
}

void cdac::applyStep(double stepValue,double stepTime)
{
	step *curStep=new step(stepValue,stepTime);
	curStep->prev=last;
	last=curStep;
	topPlateVoltage+=stepValue;
}

double cdac::getTopPlateVoltage(double curTime)
{
	double error=0.0;
	step *stepIter;
	stepIter=last;
	while(stepIter->prev!=0)
	{
		error+=stepIter->stepValue*exp(-(curTime-stepIter->stepTime)/tau);
		//cout<<stepIter->stepValue<<"\t"<<stepIter->stepTime<<endl;
		stepIter=stepIter->prev;
	}
	return topPlateVoltage-error;
}

cdac::~cdac()
{	
	step *stepIter;
	stepIter=last;
	while(stepIter->prev!=0)
	{
		last=stepIter->prev;
		delete stepIter;
		stepIter=last;
	}
	delete last;
}	
	
