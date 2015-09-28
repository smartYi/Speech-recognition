// Synchronous_DTW.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"read_template.h"
#include"Synchronous.h"
#include"get_distance.h"
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<string>

using namespace std;
   

int main (){

	//构建一个距离矩阵，初始值设为0.0
    double distance [800][39] = {0.0};
	//构建一个cost矩阵，初始值设为0.0
	double cost[800][39] = {0.0};
	//返回一个将所有模板叠加后的模板AB。
	Synchronous AB;//构建一个Synchronous 类
	AB.synchronous();//调用类里面的函数改变类里面其他元素的值
	
	//打开一个test 数据
	ifstream single_test;
	single_test.open("input_record.txt",ios::in);
		if(!single_test){
			cout<<"Can not open a file "<<endl;
			exit(1);
		}
		//将test 数据读入到测试数组
		double test_data[100][39] = {0.0};
		int test_row = 0;
		double test_temp = 0.0;
		for(int i = 0;i<100;i++,test_row++){
		for(int j = 0;j < 39;j++){
			single_test>>test_temp;
			test_data[i][j] = test_temp;	
		}
		if(single_test.eof())
				break;
	}
	
		cout<<AB.pile_row;
	////计算每个点的欧氏距离
	for(int i=0;i<AB.pile_row;i++)
		for(int j=0;j<test_row;j++)
			distance[i][j] = get_distance(AB.pile_template[i],test_data[j]);

	


	return 0;
}