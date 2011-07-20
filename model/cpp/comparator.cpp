#include "comparator.h"

bool comparator::compare(double inp,double inm)
{
	return ( (inp-inm) > offset ? true : false) ;
}
