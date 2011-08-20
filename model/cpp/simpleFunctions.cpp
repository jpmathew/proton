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
