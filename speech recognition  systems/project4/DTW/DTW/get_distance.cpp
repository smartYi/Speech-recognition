#include"stdafx.h"
#include<iostream>
using namespace std;

double get_distance(double a[],double b[]){
	double distance = 0.0;
	for(int i = 0;i<sizeof(a)/sizeof(a[0]);i++)
		distance += (a[i] - b[i])* (a[i] - b[i]);
	distance = sqrt(distance);
	return distance;
}