class cdac
{
	private :
		double topPlate;
		int N;
		bool *bottomPlate;
		double *bitWeights
		double VREF;
	public :
		cdac(int N);
		cdac(int N,double bitOneWeight,double nonBinaryRatio);
		cdac(int N,double* bitWeights);

		double getTopPlate();
		bool appplyBit(int bitPostion,bool bitState);
		bool resetCDAC();
		


	
};

