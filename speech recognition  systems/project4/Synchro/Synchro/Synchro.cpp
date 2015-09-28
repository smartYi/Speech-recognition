// Synchronous_DTW.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"read_template.h"
#include"Synchronous.h"
#include"get_distance.h"
#include"DCT.h"
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<direct.h>
#include<string>

using namespace std;
   
int main  (){

    DCT();
	//构建一个距离矩阵，初始值设为0.0
    double distance [800][39] = {0.0};
	//构建一个cost矩阵，初始值设为0.0
	double cost[800][100] = {0.0};
	//返回一个将所有模板叠加后的模板AB。
	Synchronous AB;//构建一个Synchronous 类
	AB.synchronous();//调用类里面的函数改变类里面其他元素的值
	
			

	//打开一个test 数据
	ifstream single_test;
	single_test.open("E:\\JIE course\\speech recognition  systems\\project4\\DCT_stage3\\DCT\\input_record.txt",ios::in);
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
	
	
	////计算每个点的欧氏距离
	for(int i=0;i<AB.pile_row;i++)
		for(int j=0;j<test_row;j++)
			distance[i][j] = get_distance(AB.pile_template[i],test_data[j]);



		//对于第一列，距离矩阵和cost矩阵相同
	for(int i=0;i<AB.pile_row;i++)
		cost[i][0] = distance[i][0];

	//接下来的计算按照列的顺序来进行计算
	for(int j=1;j<test_row;j++){

		//第一个模板数组0
		for(int i=0;i<AB.zero;i++){
			if(i==0)
				cost[i][j] = cost[i][j-1] + distance[i][j];
			else if(i==1){
				double cost1=0.0;
				double cost2=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?cost1:cost2;
		}
			else{
				double cost1=0.0;
				double cost2=0.0;
				double cost3=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost3 = cost[i-2][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
			}
		}

		//第二个模板数组1
		for(int i=AB.zero;i<AB.zero+AB.one;i++){
			if((i-AB.zero)==0)
				cost[i][j] = cost[i][j-1] + distance[i][j];
			else if((i-AB.zero)==1){
				double cost1=0.0;
				double cost2=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?cost1:cost2;
		}
			else{
				double cost1=0.0;
				double cost2=0.0;
				double cost3=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost3 = cost[i-2][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
			}
		}

	//第三个模板数组2
		for(int i=AB.zero+AB.one;i<AB.zero+AB.one+AB.two;i++){
			if((i-AB.zero-AB.one)==0)
				cost[i][j] = cost[i][j-1] + distance[i][j];
			else if((i-AB.zero-AB.one)==1){
				double cost1=0.0;
				double cost2=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?cost1:cost2;
		}
			else{
				double cost1=0.0;
				double cost2=0.0;
				double cost3=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost3 = cost[i-2][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
			}
		}

	//第四个模板数组3
		for(int i=AB.zero+AB.one+AB.two;i<AB.zero+AB.one+AB.two+AB.three;i++){
			if((i-AB.zero-AB.one-AB.two)==0)
				cost[i][j] = cost[i][j-1] + distance[i][j];
			else if((i-AB.zero-AB.one-AB.two)==1){
				double cost1=0.0;
				double cost2=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?cost1:cost2;
		}
			else{
				double cost1=0.0;
				double cost2=0.0;
				double cost3=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost3 = cost[i-2][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
			}
		}

	//第五个模板数组4
		for(int i=AB.zero+AB.one+AB.two+AB.three;i<AB.zero+AB.one+AB.two+AB.three+AB.four;i++){
			if((i-AB.zero-AB.one-AB.two-AB.three)==0)
				cost[i][j] = cost[i][j-1] + distance[i][j];
			else if((i-AB.zero-AB.one-AB.two-AB.three)==1){
				double cost1=0.0;
				double cost2=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?cost1:cost2;
		}
			else{
				double cost1=0.0;
				double cost2=0.0;
				double cost3=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost3 = cost[i-2][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
			}
		}

		//第六个模板数组5
		for(int i=AB.zero+AB.one+AB.two+AB.three+AB.four;i<AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five;i++){
			if((i-AB.zero-AB.one-AB.two-AB.three-AB.four)==0)
				cost[i][j] = cost[i][j-1] + distance[i][j];
			else if((i-AB.zero-AB.one-AB.two-AB.three-AB.four)==1){
				double cost1=0.0;
				double cost2=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?cost1:cost2;
		}
			else{
				double cost1=0.0;
				double cost2=0.0;
				double cost3=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost3 = cost[i-2][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
			}
		}

	//第七个模板数组6
		for(int i=AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five;i<AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five+AB.six;i++){
			if((i-AB.zero-AB.one-AB.two-AB.three-AB.four-AB.five)==0)
				cost[i][j] = cost[i][j-1] + distance[i][j];
			else if((i-AB.zero-AB.one-AB.two-AB.three-AB.four-AB.five)==1){
				double cost1=0.0;
				double cost2=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?cost1:cost2;
		}
			else{
				double cost1=0.0;
				double cost2=0.0;
				double cost3=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost3 = cost[i-2][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
			}
		}

	//第八个模板数组7
		for(int i=AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five+AB.six;i<AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five+AB.six+AB.seven;i++){
			if((i-AB.zero-AB.one-AB.two-AB.three-AB.four-AB.five-AB.six)==0)
				cost[i][j] = cost[i][j-1] + distance[i][j];
			else if((i-AB.zero-AB.one-AB.two-AB.three-AB.four-AB.five-AB.six)==1){
				double cost1=0.0;
				double cost2=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?cost1:cost2;
		}
			else{
				double cost1=0.0;
				double cost2=0.0;
				double cost3=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost3 = cost[i-2][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
			}
		}

		//第九个模板数组8
		for(int i=AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five+AB.six+AB.seven;i<AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five+AB.six+AB.seven+AB.eight;i++){
			if((i-AB.zero-AB.one-AB.two-AB.three-AB.four-AB.five-AB.six-AB.seven)==0)
				cost[i][j] = cost[i][j-1] + distance[i][j];
			else if((i-AB.zero-AB.one-AB.two-AB.three-AB.four-AB.five-AB.six-AB.seven)==1){
				double cost1=0.0;
				double cost2=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?cost1:cost2;
		}
			else{
				double cost1=0.0;
				double cost2=0.0;
				double cost3=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost3 = cost[i-2][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
			}
		}

	//第十个模板数组9
		for(int i=AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five+AB.six+AB.seven+AB.eight;i<AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five+AB.six+AB.seven+AB.eight+AB.nine;i++){
			if((i-AB.zero-AB.one-AB.two-AB.three-AB.four-AB.five-AB.six-AB.seven-AB.eight)==0)
				cost[i][j] = cost[i][j-1] + distance[i][j];
			else if((i-AB.zero-AB.one-AB.two-AB.three-AB.four-AB.five-AB.six-AB.seven-AB.eight)==1){
				double cost1=0.0;
				double cost2=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?cost1:cost2;
		}
			else{
				double cost1=0.0;
				double cost2=0.0;
				double cost3=0.0;
				cost1 = cost[i-1][j-1]+distance[i][j];
				cost2 = cost[i][j-1]+distance[i][j];
				cost3 = cost[i-2][j-1]+distance[i][j];
				cost[i][j] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
			}
		}
	}//这个是控制列数的括号

	double most_least[10] = {0.0};
	most_least[0] = cost[AB.zero-1][test_row-1];
	most_least[1] = cost[AB.zero+AB.one-1][test_row-1];
	most_least[2] = cost[AB.zero+AB.one+AB.two-1][test_row-1];
	most_least[3] = cost[AB.zero+AB.one+AB.two+AB.three-1][test_row-1];
	most_least[4] = cost[AB.zero+AB.one+AB.two+AB.three+AB.four-1][test_row-1];
	most_least[5] = cost[AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five-1][test_row-1];
	most_least[6] = cost[AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five+AB.six-1][test_row-1];
	most_least[7] = cost[AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five+AB.six+AB.seven-1][test_row-1];
	most_least[8] = cost[AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five+AB.six+AB.seven+AB.eight-1][test_row-1];
	most_least[9] = cost[AB.zero+AB.one+AB.two+AB.three+AB.four+AB.five+AB.six+AB.seven+AB.eight+AB.nine-1][test_row-1];

	//找出最小的
	double minimum = 10000.0;
	int tag = 0;
	for(int i=0;i<10;i++)
		if(most_least[i]<minimum){
			minimum = most_least[i];
			tag = i;
		}

	//判断是哪个数字？
		if(tag==0)
			cout<<"Do you say 0?";
		if(tag==1)
			cout<<"Do you say 1?";
		if(tag==2)
			cout<<"Do you say 2?";
		if(tag==3)
			cout<<"Do you say 3?";
		if(tag==4)
			cout<<"Do you say 4?";
		if(tag==5)
			cout<<"Do you say 5?";
		if(tag==6)
			cout<<"Do you say 6?";
		if(tag==7)
			cout<<"Do you say 7?";
		if(tag==8)
			cout<<"Do you say 8?";
		if(tag==9)
			cout<<"Do you say 9?";

	/*return 0;*/
}