#include "delayLine.h"

delayLine::delayLine(int delayStep,int percentageVariation,int totTaps)
{
	int count=0;
	unitDel=new int[totTaps];
	for(count=0;count<totTaps;count++)
	{
		unitDel[count]=delayStep(1+(rand()%percentageVariation)/100);
	}
}
int delayLine::getDelay(int tap)
{
	int count=0;
	int totDelay=0;
	for(count=0;count++;count<tap)
	{
		totDelay+=unitDel[count];
	}
	return totDelay;
}
