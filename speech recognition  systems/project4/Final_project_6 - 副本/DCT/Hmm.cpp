#include "stdafx.h"
#include "Hmm.h"


Hmm::Hmm(void)
{
	for(int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 39; j++)
		{
			means[i].data[j] = 0.0;
		}
	}
	for(int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 39; j++)
		{
			cov[i].data[j] = 0.0;
		}
	}
}


Hmm::~Hmm(void)
{
}
