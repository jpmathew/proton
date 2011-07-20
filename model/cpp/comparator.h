#ifndef COMPARATOR_H
#define COMPARATOR_H

class comparator
{
	private:
	double offset;
	public:
	comparator(double offset)
	{
		offset=this->offset;
	}
	bool compare(double inp,double inm);
};

#endif
