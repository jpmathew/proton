#include "cdac.h"
#include "comparator.h"

class simpleSarADC
{
	private:
		cdac *mainCdac;
		comparator *mainCmp;
		int *bitOut;
		int resolution;
	public:
		simpleSarADC(int resolution);
		long convert(double input);
};
