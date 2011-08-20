#ifndef SIMPLESARADC_H
#define SIMPLESARADC_H

#include "cdac.h"
#include "comparator.h"
#include "simpleFunctions.h"
#include <iostream>
#include <fstream>

class simpleSarADC
{
	private:
		cdac *mainCdac;
		comparator *mainCmp;
		int *bitOut;
		int resolution;
		double *dacVals;
	public:
		simpleSarADC(int resolution);
		long convert(double input);
		void dumpConvInfo();
		~simpleSarADC();
};

#endif
