#ifndef COMPARATOR_H
#define COMPARATOR_H

class comparatorOut
{
	private:
	bool decision;
	bool timedout;
	double time;
	public:
	comparatorOut(bool decision,bool timedout,double time);
	bool getDecision();
	bool isTimedOut();
	double getTime();
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
