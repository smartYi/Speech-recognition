#include"stdafx.h"
#include<iostream>
using namespace std;

double get_distance(double a[39],double b[39]){
	double distance = 0.0;
	for(int i = 0;i<39;i++)
		distance += (a[i] - b[i])* (a[i] - b[i]);
	distance = sqrt(distance);
	return distance;
}