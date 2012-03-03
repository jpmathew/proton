#include "binDelayLine.h"

delayLine::delayLine(int delayStep,int totTaps)
{
	int count=0;
	unitDel=new int[totTaps];
	for(count=0;count<totTaps;count++)
	{
		unitDel[count]=delayStep;
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
