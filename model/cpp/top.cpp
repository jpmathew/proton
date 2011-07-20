#include <iostream>
#include "comparator.h"
using namespace std;

int main()
{
	comparator *cmp1;
	cmp1=new comparator(0.01);

	bool output;
	output=cmp1->compare(.22,.43);

	cout<<output<<endl;

	return 0;
}

