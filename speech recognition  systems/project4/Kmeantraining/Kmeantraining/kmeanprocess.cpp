#include "kmeanprocess.h"
#include <iostream>
#include <fstream>
using namespace std;


kmeanprocess::kmeanprocess(void)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			edge[i][j] = 0;
		}
	}
}


kmeanprocess::~kmeanprocess(void)
{
}


vector<double> kmeanprocess::construc_covmatrix(kmeandata* data, trainingdata current)
{

	vector<double> tem;
	for (int i = 0; i < 5; i++)
	{
		framedata cov;
		cov = data[i].get_cov();
		
		for (int index = 0; index < current.get_framecount(); index++)
		{
			double sum = 0.0;
			double cov_sum = 0.0;
			for(int j = 0; j < 39; j++)
			{
				double a = (current.dctdata[index].data[j] - data[i].segment_mean[j])
					* (current.dctdata[index].data[j] - data[i].segment_mean[j]) / cov.data[j];
				sum = sum + a;
				cov_sum += log(2 * 3.1415 * cov.data[i]);
			}

			tem.push_back((0.5 * (sum + cov_sum)));
		}
	}
	return tem;
}


void kmeanprocess::transi_probile(kmeandata* data)
{

	for (int i = 0; i < 4; i++)
	{
		edge[i][i+1] = (-log((4.0 / double(data[i].segment_data.size()))));
		edge[i][i] = (-log(((1.0 - 4.0 / double(data[i].segment_data.size())))));
	}
}

vector<int> kmeanprocess::dtwprocess(vector<double> nodecost)
{

	vector<int> segment_index;
	int row_max;
	row_max = nodecost.size() / 5;
	int col = 0;
	int row = 1;
	// 预处理
	//int zero_count = 4;
	//for (int colun = 0; colun < 4; colun++)
	//{
	//	for (int zero_row = row_max - zero_count; zero_row < row_max; zero_row++)
	//	{
	//		nodecost[colun * row_max + zero_row] = 0.0;
	//	}
	//	zero_count--;
	//}

	ofstream midsamplevalue3;
	midsamplevalue3.open("raw_data.txt");
	midsamplevalue3.clear();
	midsamplevalue3.close();
	ofstream midsamplevalue21;
	midsamplevalue21.open("raw_data.txt",ios::app);
	for(int i=0;i<nodecost.size();i++)
	{
		midsamplevalue21<<nodecost[i]<< " ";
		if(i % row_max == 0)
			cout << endl;
	}
	midsamplevalue21.close();

	segment_index.push_back(0);
	while (col < 4)
	{
		double node_cost = 0.0;
		double edge_cost = 0.0;
		double node_up;
		if(col + 1 > 4) // 当来到顶格的时候
			node_up = 0;
		else
			node_up = nodecost[(col + 1) * row_max + row];

		double node_hor = nodecost[col * row_max + row];
		if (node_up >= node_hor)
		{
			col++;
			segment_index.push_back(row);
		}
		//if(row == (row_max - 1))
		//	break;
		row++;

	}
	segment_index.push_back(row_max);
	return segment_index;
}