// try.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;


int main()
{
	double example[100][100] = {0};
	int count = 0;
	double a;
	ifstream number_zero;
	number_zero.open("digit_number_3.txt");
	for(int i = 0;i<100;i++,count++){
		for(int j = 0;j < 39;j++){
			number_zero>>a;
			example[i][j] = a;	
		}
		if(number_zero.eof())
				break;
	}
	

	
	for(int i=0;i<count;i++){
		for(int j =0;j<39;j++)
			cout<<setw(6)<<example[i][j];
			cout<<endl;
		}
	return 0;
}

