#ifndef SIMPLESARADC_H
#define SIMPLESARADC_H

#include "cdac.h"
#include "comparator.h"
#include "simpleFunctions.h"
#include <iostream>
#include <fstream>

class asyncSarADC
{
	private:
		cdac *mainCdac;
		comparator *mainCmp;
		int *bitOut;
		int resolution;
		int convTime;
		const static int ctDacTime=600;
		const static int ctCmpTime=140;
		const static double VREF=0.9;
	public:
		asyncSarADC(int resolution);
		long convert(double input);
		int getConvTime(); 
		void dumpConvInfo();
		~asyncSarADC();
};

#endif
