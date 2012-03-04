#include "simpleFunctions.h"

long pow(int base,int exp)
{
	int iter;
	long result=1;
	for(iter=1;iter<=exp;iter++)
	{
		result*=base;
	}
	return result;
}

int maxInt(int x,int y)
{
	return x>y?x:y;
}
