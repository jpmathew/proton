#ifndef XNLCOMPUTE_H
#define XNLCOMPUTE_H

#include <fstream>
#include <iostream>
#include "simpleFunctions.h"
using namespace std;

class xnlCompute
{
	private:
		ifstream codeData;
		ofstream dnlData,inlData;
	
		long code,minCode,maxCode,numCode;
		double totalHit,avgHit,inl,dnl;
		int *codeHits;
	public:
		xnlCompute(int resolution);
		~xnlCompute();
		void computeLin(const char *fileName);
};
		
#endif
		
		



