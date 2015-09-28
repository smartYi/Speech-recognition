#include"stdafx.h"
#include<iostream>
#include<ctime>
#include<conio.h>
#include<iomanip>
#include"get_distance.h"
#include"color.h"
using namespace std;


double DTW(double a[][39], double b[][39]){

	int length_of_template;
	int length_of_input;
	//Calculate the rows of template and input
	length_of_template = sizeof(a)/sizeof(a[0]);
	length_of_input = sizeof(b)/sizeof(b[0]);
	double distance[100][100] = {0.0};
	double cost[100][100] = {0.0};

	//Calculate the node costs
	for(int i = 0;i<length_of_template;i++)
		for(int j = 0;j<length_of_input;j++)
			distance[i][j] = get_distance(a[i],b[j]);


	//Calculate the DTW distances
	//First row and coloum are the same
	for(int i = 0;i<length_of_template;i++)
		cost[i][0] = distance[i][0];
	for(int j = 0;j<length_of_input;j++)
		cost[0][j] = distance[0][j];
	//Special for 2nd row
	double cost1;
	double cost2;
	double cost3;
	for(int j = 1;j<length_of_input;j++){
		cost1 = cost[0][j-1] + distance[1][j];
		cost2 = cost[1][j-1] + distance[1][j];
		cost[1][j] = ( cost1<cost2?cost1:cost2 );
	}
		//For the rest of rows
	for(int i = 2;i<length_of_template;i++)
		for(int j = 1;j<length_of_input;j++){
		cost1 = cost[i-1][j-1] + distance[i][j];
		cost2 = cost[i-2][j-1] + distance[i][j];
		cost3 = cost[i][j-1] + distance[i][j];
		cost[i][j] = (cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3));
		}
		return cost[length_of_template-1][length_of_input-1];
}
