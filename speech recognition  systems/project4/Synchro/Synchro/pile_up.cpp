// Synchronous_DTW.cpp : �������̨Ӧ�ó������ڵ㡣
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

	//����һ��������󣬳�ʼֵ��Ϊ0.0
    double distance [800][39] = {0.0};
	//����һ��cost���󣬳�ʼֵ��Ϊ0.0
	double cost[800][39] = {0.0};
	//����һ��������ģ����Ӻ��ģ��AB��
	Synchronous AB;//����һ��Synchronous ��
	AB.synchronous();//����������ĺ����ı�����������Ԫ�ص�ֵ
	
	//��һ��test ����
	ifstream single_test;
	single_test.open("input_record.txt",ios::in);
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
	
		cout<<AB.pile_row;
	////����ÿ�����ŷ�Ͼ���
	for(int i=0;i<AB.pile_row;i++)
		for(int j=0;j<test_row;j++)
			distance[i][j] = get_distance(AB.pile_template[i],test_data[j]);

	


	return 0;
}