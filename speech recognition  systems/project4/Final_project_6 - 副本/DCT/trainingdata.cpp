#include "stdafx.h"
#include "trainingdata.h"


trainingdata::trainingdata(void)
{
}

trainingdata::trainingdata(double data[], int total)
{
	int count = 0;
	for (int i = 0; i < total; i++)
	{
		double tem[39];
		tem[count++] = data[i];
		if(count == 39)
		{
			count = 0;
			framedata a(tem);
			dctdata.push_back(a);
		}
	}
	frame_count = dctdata.size();
}

trainingdata::~trainingdata(void)
{
}

int trainingdata::get_framecount()
{
	return frame_count;
}