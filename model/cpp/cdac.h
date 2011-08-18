#ifndef CDAC_H
#define CDAC_H
class step
{
	public :
		double stepValue;
		double stepTime;
		step  *prev;
		step(double stepValue,double stepTime);
};

class cdac
{
	private :
		double topPlateVoltage;
		double tau;
		step *last;
	public :
		cdac(double tau);
		~cdac();
		void applyStep(double stepValue,double stepTime);
		double getTopPlateVoltage(double curTime);
		void reset();
};
#endif
