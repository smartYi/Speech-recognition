#include "stdafx.h"
#include "kmeanprocess.h"
#include "framedata.h"
#include <vector>
using namespace std;

kmeanprocess::kmeanprocess(void)
{
}


kmeanprocess::~kmeanprocess(void)
{
}


typedef struct kmean
{
	int turn_point[4];
	double score;
};

double kmeanprocess::dtw(vector<double> nodecost)
{
	vector<int> segment_index;
	segment_index.push_back(0);
	vector<double> re_segmemt = nodecost;//若是调用函数，把形参付给这个vector即可
	double temp;
	kmean TD;
	int frame;
	frame = re_segmemt.size()/5;

	double dtw[5][200] = {0};
	for(int i=0;i<5;i++)
		for(int j=0;j<frame;j++)
			dtw[i][j] = re_segmemt.at(j+i*frame);

	double new_dtw[5][200]={0};
	for(int i=0;i<5;i++)
		new_dtw[i][0] = dtw[i][0];
	for(int j=1;j<frame;j++)
		new_dtw[0][j]  = new_dtw[0][j-1] + dtw[0][j];
	for(int i=1;i<5;i++)
		for(int j=1;j<frame;j++){
			double score1 = dtw[i][j] + new_dtw[i][j-1];
			double score2 = dtw[i][j] + new_dtw[i-1][j-1];
			new_dtw[i][j] = score1<score2?score1:score2;
		}

		TD.score = new_dtw[4][frame-1];
		//找出每个状态的frame
		double frame_number[5] = {0};
		frame_number[0] =1;
		for(int i=0;i<4;i++)
			TD.turn_point[i] = 0;
		int tag_row = 0;
		int tag_coloum =0;
		do{
			if(new_dtw[tag_row][tag_coloum+1]<new_dtw[tag_row+1][tag_coloum+1]){
				frame_number[tag_row]++;
				tag_coloum++;
			}
			else{
				if(tag_row==0)
					TD.turn_point[tag_row] = frame_number[tag_row];
				else
					TD.turn_point[tag_row] = frame_number[tag_row] + TD.turn_point[tag_row-1];
				tag_row++;
				tag_coloum++;
				frame_number[tag_row]++;
			}
		}while(tag_row<5&&tag_coloum<frame-1);

		for (int i = 0; i < 4;i++)
		{
			segment_index.push_back(TD.turn_point[i]);
		}
		segment_index.push_back(frame);

		return TD.score;
}

vector<double> kmeanprocess::construc_covmatrix(Hmm model, trainingdata current)
{
	vector<double> tem;
	for(int i = 0; i < 5; i++)
	{
		framedata cov;
		cov = model.cov[i];
		for (int index = 0; index < current.get_framecount(); index++)
		{
			double sum = 0.0;
			double cov_sum = 0.0;
			for(int j = 0; j < 39; j++)
			{
				double a = (current.dctdata[index].data[j] - model.means[i].data[j])
					* (current.dctdata[index].data[j] - model.means[i].data[j]) / cov.data[j];
				sum = sum + a;
				cov_sum += log(2 * 3.1415 * cov.data[j]);
			}

			tem.push_back((0.5 * (sum + cov_sum)));
		}
	}
	return tem;
}
