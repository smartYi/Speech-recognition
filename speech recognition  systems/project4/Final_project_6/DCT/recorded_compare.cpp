#include"stdafx.h"
#include"read_template.h"
#include"multiple_template_path.h"
#include"DTW.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include <vector>
#include "recorded_compare.h"
#include "input_file.h"

using namespace std;

void recorded_compare(){

	
	multiple TD;
	TD.read();/////����ǵ�ģ�������
	vector<string> TB;
	vector<string> TP;
	input_file inputfile;
	TB = inputfile.read_input_compare();////����ǲ������ݵ�·��

	multiple_template_path path_of_templates;

	TP = path_of_templates.path_of_multiple_temps();//����Ƕ�ģ�����ݵ�·��
	
	//���Ƚ���ȡ��������
	

	double least[10] = {0.0};
	double minimum = 1000.0;
	int accuracy = 0;
	int zero= 0, one = 0,two=0,three=0,four=0,five=0,six=0,seven=0,eight=0,nine=0;
	//Read input feature vectors
	//Choose template style
	int choice;
	cout<<"Single template to push 1: "<<endl<<"Multiple templates to push 2: ";
	cin>>choice;
    if(choice == 1)/////����ǵ�һģ��ıȽ�
	{
	for(int index = 0;index<TB.size();index++){

	double minimum = 1000.0;
	double example[100][39] = {0.0};
	int count_input = 0;
	double temp;
	string filename = TB.at(index);
	ifstream number_input;
	number_input.open(filename,ios::in);
	if(!number_input){
		cout<<"can not open a file."<<endl;
		exit(1);
	}

	for(int i = 0;i<100;i++,count_input++){
		for(int j = 0;j < 39;j++){
			number_input>>temp;
			example[i][j] = temp;	
		}
		if(number_input.eof())
				break;
	}

	
	//Calculate all distances
	least[0] = DTW(TD.temp_0,example,TD.number_0,count_input);
	least[1] = DTW(TD.temp_1,example,TD.number_1,count_input);
	least[2] = DTW(TD.temp_2,example,TD.number_2,count_input);
	least[3] = DTW(TD.temp_3,example,TD.number_3,count_input);
	least[4] = DTW(TD.temp_4,example,TD.number_4,count_input);
	least[5] = DTW(TD.temp_5,example,TD.number_5,count_input);
	least[6] = DTW(TD.temp_6,example,TD.number_6,count_input);
	least[7] = DTW(TD.temp_7,example,TD.number_7,count_input);
	least[8] = DTW(TD.temp_8,example,TD.number_8,count_input);
	least[9] = DTW(TD.temp_9,example,TD.number_9,count_input);

	//Find the most least distance
	for(int  i = 0;i<10;i++)
		if(least[i]<minimum )
			minimum  = least[i];
	
	//Diaplay the number you want to say
	if(minimum == least[0]){
		
		if((index<=4)&&(index>=0)){
		accuracy++;
		zero++;}}
	if(minimum == least[1]){
		
		if((index<=9)&&(index>=5)){
		accuracy++;
		one++;}}
	if(minimum == least[2]){
		
		if((index<=14)&&(index>=10)){
		accuracy++;
		two++;}}
	if(minimum == least[3]){
		
		if((index<=19)&&(index>=15)){
		three++;
		accuracy++;}}
	if(minimum == least[4]){
		
		if((index<=24)&&(index>=20)){
		accuracy++;
		four++;}}
	if(minimum == least[5]){
		
		if((index<=29)&&(index>=25)){
		accuracy++;
		five++;}}
	if(minimum == least[6]){
		
		if((index<=34)&&(index>=30)){
		accuracy++;
		six++;}}
	if(minimum == least[7]){
	
		if((index<=39)&&(index>=35)){
		seven++;
		accuracy++;
		}}
	if(minimum == least[8]){
		
		if((index<=44)&&(index>=40)){
		eight++;
		accuracy++;}}
	if(minimum == least[9]){
		
		if((index<=49)&&(index>=45)){
		nine++;
		accuracy++;}}
}
	cout<<accuracy<<endl;
	cout<<setw(6)<<"zero = "<<zero<<endl<<setw(6)<<"one = "<<one<<endl<<setw(6)<<"two = "<<two<<endl;
	cout<<setw(6)<<"three = "<<three<<endl<<setw(6)<<"four = "<<four<<endl<<setw(6)<<"five = "<<five<<endl;
	cout<<"six = "<<six<<endl<<"seven = "<<seven<<endl<<"eight = "<<eight<<endl;
	cout<<setw(6)<<"nine = "<<nine<<endl;
	}

	if(choice == 2)///����Ƕ�ģ��Ƚ�
	{
		int a=0;
	double distance_between [50][50] = {0.0};
	for(int index_row = 0;index_row<TB.size();index_row++){///TB ��ŵ��ǲ������ݵ�·��
		///����һ�������������50���������ݺ�50��ģ��֮��ľ���,����������ж�����׼ȷ�ʵ�
	//��ȡ��ǰҪ���бȽϵĲ������ݵ�example ������
	double minimum = 1000.0;
	double example[100][39] = {0.0};
	int count_input = 0;//�������ݵĵ�֡��
	double temp;
	string filename = TB.at(index_row);
	ifstream number_input;
	number_input.open(filename,ios::in);
	if(!number_input){
		cout<<"can not open a file."<<endl;
		exit(1);
	}

	for(int i = 0;i<100;i++,count_input++){
		for(int j = 0;j < 39;j++){
			number_input>>temp;
			example[i][j] = temp;	
		}
		if(number_input.eof())
				break;
	}
	//���˵�ǰ�Ƚϵ������Ѿ���ȡ��ϣ�������Ҫ����һ��50�ε�ѭ�������αȽϲ������ݺ�ģ�����ݵľ���
	
	for(int index_coloum = 0;index_coloum<50;index_coloum++){
		//���ȶ�ȡ�����TP�����ģ������·�������ҽ����е����ݶ�ȡ��Ҫ�Ƚϵ�һ��������
		double current_template_data[100][39] = {0.0};
		int current_template_row = 0;////ģ���֡��
		double current_data;
		ifstream read_path;
		read_path.open(TP.at(index_coloum),ios::in);
		if(!read_path){
		cout<<"can not open a file."<<endl;
		exit(1);
	}
		for(int i = 0;i<100;i++,current_template_row++){
		for(int j = 0;j < 39;j++){
			read_path>>current_data;
			current_template_data[i][j] = current_data;	
		}
		if(read_path.eof())
				break;
	}///���˵�ǰ��ģ�������Ѿ���ȡ��current_template_data ������
		//����DTW �������ص�ǰ�������Ƚϵ����·��
		distance_between[index_row][index_coloum] = DTW(current_template_data,example,current_template_row,count_input);
		if(distance_between[index_row][index_coloum]<minimum)
			minimum = distance_between[index_row][index_coloum];///�ҳ���ǰ����������С���Ǹ�����
	}
	//�ڻ�����һ����������֮ǰ�������жϵ�ǰ�Ĳ��Խ���Ƿ�׼ȷ����
	for(int k=0;k<50;k++){
		if(minimum == distance_between[index_row][k]){
			if(k>=0&&k<=4&&index_row>=0&&index_row<=4){
				zero++;accuracy++;}//�����ǰ�Ĳ���������0  ���Ҳ���Ľ��Ҳ��0������0��׼ȷ���ϼ�1.
			if(k>=5&&k<=9&&index_row>=5&&index_row<=9){
				one++;accuracy++;}//�����ǰ�Ĳ���������1  ���Ҳ���Ľ��Ҳ��1������1��׼ȷ���ϼ�1.
			if(k>=10&&k<=14&&index_row>=10&&index_row<=14){
				two++;accuracy++;}//�����ǰ�Ĳ���������2  ���Ҳ���Ľ��Ҳ��2������2��׼ȷ���ϼ�1.
			if(k>=15&&k<=19&&index_row>=15&&index_row<=19){
				three++;accuracy++;}//�����ǰ�Ĳ���������3  ���Ҳ���Ľ��Ҳ��3������3��׼ȷ���ϼ�1.
			if(k>=20&&k<=24&&index_row>=20&&index_row<=24){
				four++;accuracy++;}//�����ǰ�Ĳ���������4 ���Ҳ���Ľ��Ҳ��4������4��׼ȷ���ϼ�1.
			if(k>=25&&k<=29&&index_row>=25&&index_row<=29){
				five++;accuracy++;}//�����ǰ�Ĳ���������5  ���Ҳ���Ľ��Ҳ��5������5��׼ȷ���ϼ�1.
			if(k>=30&&k<=34&&index_row>=30&&index_row<=34){
				six++;accuracy++;}//�����ǰ�Ĳ���������6  ���Ҳ���Ľ��Ҳ��6������6��׼ȷ���ϼ�1.
			if(k>=35&&k<=39&&index_row>=35&&index_row<=39){
				seven++;accuracy++;}//�����ǰ�Ĳ���������7  ���Ҳ���Ľ��Ҳ��7������7��׼ȷ���ϼ�1.
			if(k>=40&&k<=44&&index_row>=40&&index_row<=44){
				eight++;accuracy++;}//�����ǰ�Ĳ���������8  ���Ҳ���Ľ��Ҳ��8������8��׼ȷ���ϼ�1.
			if(k>=45&&k<=49&&index_row>=45&&index_row<=49){
				nine++;accuracy++;}//�����ǰ�Ĳ���������9  ���Ҳ���Ľ��Ҳ��9������9��׼ȷ���ϼ�1.
		}
	}
	cout<<accuracy<<endl;
	}
	cout<<accuracy<<endl;
	cout<<setw(6)<<"zero = "<<zero<<endl<<setw(6)<<"one = "<<one<<endl<<setw(6)<<"two = "<<two<<endl;
	cout<<setw(6)<<"three = "<<three<<endl<<setw(6)<<"four = "<<four<<endl<<setw(6)<<"five = "<<five<<endl;
	cout<<"six = "<<six<<endl<<"seven = "<<seven<<endl<<"eight = "<<eight<<endl;
	cout<<setw(6)<<"nine = "<<nine<<endl;
	}
}