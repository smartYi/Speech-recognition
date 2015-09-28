#include "stdafx.h"
#pragma once
#include <vector>
#include "Hmm.h"
#include "trainingdata.h"
using namespace std;
class kmeanprocess
{
public:
	kmeanprocess(void);
	~kmeanprocess(void);
	double dtw(vector<double> nodecost);
	vector<double> construc_covmatrix(Hmm model, trainingdata current);
};

