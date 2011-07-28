#include <iostream>
#include "comparator.h"
using namespace std;

int main()
{
	comparator *cmp1;
	comparatorOut *cmpOut1;
	bool decision;
	bool timedout;
	double time;
	cmp1=new comparator(0.01,200.0,true);
	cmpOut1=cmp1->compare(.62,.43,300,0.9);
	decision=cmpOut1->getDecision();
	timedout=cmpOut1->isTimedOut();
	time=cmpOut1->getTime();
	cout<<time<<endl;
	return 0;
}

