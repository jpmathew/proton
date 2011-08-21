#ifndef COMPARATOR_H
#define COMPARATOR_H

class comparator
{
	private:
	double offset;
	double tau;
	bool async;
	const static double VDD=0.9;

	bool decision;
	bool timedOut;
	double time;

	public:
	comparator(double offset,double tau,bool async);
	~comparator();
	bool compare(double inp,double inm,double timeout);
	bool isTimedOut();
	double cmpTime();
};


#endif
