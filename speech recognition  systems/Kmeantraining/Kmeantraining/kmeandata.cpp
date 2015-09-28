#include "kmeandata.h"
#include <math.h>
#include <iostream>
using namespace std;

kmeandata::kmeandata(void)
{
	for (int i = 0; i < 39; i++)
	{
		segment_mean[i] = 0;
	}

	for (int i = 0; i < 39; i++)
	{
		cov[i] = 0;
	}
}


kmeandata::~kmeandata(void)
{
}

framedata kmeandata::get_cov()
{
	double dig_cov[39] = {0};
	framedata ret;
	for(unsigned i = 0; i < segment_data.size(); i++)
	{
		vector<double> tem_dif = get_differect(segment_data[i]);

		for (int j = 0; j < 39; j++)
		{
			dig_cov[j] += (tem_dif[j] * tem_dif[j]);
		}
	}
	for (int i = 0; i < 39; i++)
	{
		dig_cov[i] = dig_cov[i] / double(segment_data.size());
		cov[i] = dig_cov[i];
		ret.data[i] = dig_cov[i];
	}
	return ret;
	
}

vector<double> kmeandata::get_differect(framedata current)
{
	vector<double> diff;
	for (int i = 0; i < 39; i++)
	{
		diff.push_back(current.data[i] - segment_mean[i]);
	}
	return diff;
}

void kmeandata::push_segment(framedata input)
{
	segment_data.push_back(input);
	for (int i = 0; i < 39; i++)
	{
		double original_mean;
		original_mean = segment_mean[i] * (segment_data.size() - 1);
		segment_mean[i] = (original_mean + input.data[i]) / segment_data.size();
	}
}

void kmeandata::clear()
{
	segment_data.clear();
	for (int i = 0; i < 39; i++)
	{
		segment_mean[i] = 0;
	}
	for (int i = 0; i < 39; i++)
	{
		cov[i] = 0;
	}
}