#ifndef COMPARATOR_H
#define COMPARATOR_H

class comparatorOut
{
	public:
	bool decision;
	bool isTimedOut;
	double time;
	comparatorOut(bool decision,bool isTimedOut,double time);
};


class comparator
{
	private:
	double offset;
	double tau;
	bool async;
	double timeout;
	double time;
	public:
	comparator(double offset,double tau,bool async);
	comparatorOut* compare(double inp,double inm,double timeout,double VDD);
};


#endif
