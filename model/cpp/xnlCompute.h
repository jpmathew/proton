#include <fstream>
#include <iostream>
using namespace std;

class xnlCompute
{
	private:
		ifstream codeData;
		ofstream dnlData,inlData;
	public:
		xnlCompute()
		{
		}
		void computeLin(char *fileName);
};
		

		
		


