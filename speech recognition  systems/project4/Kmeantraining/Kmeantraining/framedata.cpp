#include "framedata.h"


framedata::framedata(void)
{
}


framedata::~framedata(void)
{
}

framedata::framedata(double input[39])
{
	for (int i = 0; i < 39; i++)
	{
		data[i] = input[i];
	}
}
