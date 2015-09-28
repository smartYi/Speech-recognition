#pragma once
#include "kmeandata.h"
#include "trainingdata.h"
#include <vector>
#include <iostream>
using namespace std;
class kmeanprocess
{
public:
	kmeanprocess(void);
	~kmeanprocess(void);
	vector<double>  construc_covmatrix(kmeandata* data, trainingdata current);
	void  transi_probile(kmeandata* data);
	vector<int> dtwprocess(vector<double> nodecost);

	double edge[5][5]; // ±ßcost
};

