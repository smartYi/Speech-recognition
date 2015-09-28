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
	vector<double>  construc_covmatrix(vector<double> mean[5], trainingdata current);
	void  transi_probile(kmeandata* data);
	vector<int> dtwprocess(vector<double> nodecost);
	double dtw(vector<double> nodecost);
	vector<double> getconv(vector<double> mean, trainingdata current);
	vector<double> get_differect(vector<double> mean, framedata current);
	double edge[5][5]; // ±ßcost
};

