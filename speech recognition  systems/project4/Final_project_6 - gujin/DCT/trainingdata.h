#include "stdafx.h"
#pragma once
#include <vector>
#include "framedata.h"
using namespace std;
class trainingdata
{
public:
	trainingdata(void);
	~trainingdata(void);
	vector<framedata> dctdata;
	trainingdata(double data[], int total);
	int frame_count;
	int get_framecount();
};

