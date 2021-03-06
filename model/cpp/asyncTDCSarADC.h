#ifndef ASYNCTDCSARADC_H
#define ASYNCTDCSARADC_H

#include "cdac.h"
#include "comparator.h"
#include "simpleFunctions.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>

class asyncTDCSarADC
{
	private:
		cdac *mainCdac;
		comparator *mainCmp;
		int *bitOut,*add,*sub;
		int resolution;
		int convTime;
		const static int ctCmpTau=10;
		const static int ctDacTau=40;
		const static int ctDacTime=80;
		const static int ctOverHeadTime=20;
		const static int ctCmpTime=140;
		const static double VREF=0.9;
	public:
		asyncTDCSarADC(int resolution);
		long convert(double input);
		int getConvTime(); 
		void dumpConvInfo();
		~asyncTDCSarADC();
};

#endif
