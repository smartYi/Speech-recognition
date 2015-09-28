#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "framedata.h"
using namespace std;

class trainingdata
{
public:
	trainingdata(void);
	~trainingdata(void);
	trainingdata(string filename);
	vector<framedata> dctdata;
	int frame_count;
	int get_framecount();
};

