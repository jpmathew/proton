#include <iostream>
#include "cdac.h"
using namespace std;

int main()
{
	cdac *mainCDAC;
	double curTime=0.0;
	mainCDAC = new cdac(100.0);
	mainCDAC->applyStep(.5,curTime);
	curTime+=100.0;
	cout<<mainCDAC->getTopPlateVoltage(curTime)<<endl;
	curTime+=100.0;
	cout<<mainCDAC->getTopPlateVoltage(curTime)<<endl;
	mainCDAC->applyStep(.25,curTime);
	curTime+=100.0;
	cout<<mainCDAC->getTopPlateVoltage(curTime)<<endl;
	return 1;
}



