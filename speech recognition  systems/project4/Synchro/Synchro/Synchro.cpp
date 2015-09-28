// Synchronous_DTW.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//����һ��������󣬳�ʼֵ��Ϊ0.0
    double distance [800][39] = {0.0};
	//����һ��cost���󣬳�ʼֵ��Ϊ0.0
	double cost[800][100] = {0.0};
	//����һ��������ģ����Ӻ��ģ��AB��
	Synchronous AB;//����һ��Synchronous ��
	AB.synchronous();//����������ĺ����ı�����������Ԫ�ص�ֵ
	
			

	//��һ��test ����
	ifstream single_test;
	single_test.open("E:\\JIE course\\speech recognition  systems\\project4\\DCT_stage3\\DCT\\input_record.txt",ios::in);
		if(!single_test){
			cout<<"Can not open a file "<<endl;
			exit(1);
		}
		//��test ���ݶ��뵽��������
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
	
	
	////����ÿ�����ŷ�Ͼ���
	for(int i=0;i<AB.pile_row;i++)
		for(int j=0;j<test_row;j++)
			distance[i][j] = get_distance(AB.pile_template[i],test_data[j]);



		//���ڵ�һ�У���������cost������ͬ
	for(int i=0;i<AB.pile_row;i++)
		cost[i][0] = distance[i][0];

	//�������ļ��㰴���е�˳�������м���
	for(int j=1;j<test_row;j++){

		//��һ��ģ������0
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

		//�ڶ���ģ������1
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

	//������ģ������2
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

	//���ĸ�ģ������3
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

	//�����ģ������4
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

		//������ģ������5
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

	//���߸�ģ������6
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

	//�ڰ˸�ģ������7
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

		//�ھŸ�ģ������8
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

	//��ʮ��ģ������9
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
	}//����ǿ�������������

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

	//�ҳ���С��
	double minimum = 10000.0;
	int tag = 0;
	for(int i=0;i<10;i++)
		if(most_least[i]<minimum){
			minimum = most_least[i];
			tag = i;
		}

	//�ж����ĸ����֣�
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