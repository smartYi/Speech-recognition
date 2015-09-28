#pragma once
#include <iostream>
#include <vector>
#include "framedata.h"
using namespace std;
class kmeandata
{
public:
	kmeandata(void);
	~kmeandata(void);
	void push_segment(framedata input);

	vector<framedata> segment_data;
	double segment_mean[39];

	double cov[39];
	framedata get_cov();
	vector<double> get_differect(framedata current);
	void clear();
};

