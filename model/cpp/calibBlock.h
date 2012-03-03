#ifndef CALIB_BLOCK_H
#define CALIB_BLOCK_H

class calibBlock
{
	public:
		int main;
		int fine[7];
		calibBlock()
		{
			main=0;
			for(int count=0;count<7;count++)
			{
				fine[count]=0;
			}
		}
}

