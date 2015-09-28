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
	TD.read();/////这个是单模板的数据
	vector<string> TB;
	vector<string> TP;
	input_file inputfile;
	TB = inputfile.read_input_compare();////这个是测试数据的路径

	multiple_template_path path_of_templates;

	TP = path_of_templates.path_of_multiple_temps();//这个是多模板数据的路径
	
	//首先将读取测试数据
	

	double least[10] = {0.0};
	double minimum = 1000.0;
	int accuracy = 0;
	int zero= 0, one = 0,two=0,three=0,four=0,five=0,six=0,seven=0,eight=0,nine=0;
	//Read input feature vectors
	//Choose template style
	int choice;
	cout<<"Single template to push 1: "<<endl<<"Multiple templates to push 2: ";
	cin>>choice;
    if(choice == 1)/////这个是单一模板的比较
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

	if(choice == 2)///这个是多模板比较
	{
		int a=0;
	double distance_between [50][50] = {0.0};
	for(int index_row = 0;index_row<TB.size();index_row++){///TB 存放的是测试数据的路径
		///构建一个数组用来存放50个测试数据和50个模板之间的距离,这个是用来判断最后的准确率的
	//读取当前要进行比较的测试数据到example 数组中
	double minimum = 1000.0;
	double example[100][39] = {0.0};
	int count_input = 0;//测试数据的的帧数
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
	//至此当前比较的数据已经读取完毕，接下来要进行一个50次的循环来依次比较测试数据和模板数据的距离
	
	for(int index_coloum = 0;index_coloum<50;index_coloum++){
		//首先读取存放在TP里面的模板数据路径，并且将其中的数据读取到要比较的一个数组中
		double current_template_data[100][39] = {0.0};
		int current_template_row = 0;////模板的帧数
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
	}///至此当前的模板数据已经读取到current_template_data 数组中
		//调用DTW 函数返回当前的两个比较的最短路径
		distance_between[index_row][index_coloum] = DTW(current_template_data,example,current_template_row,count_input);
		if(distance_between[index_row][index_coloum]<minimum)
			minimum = distance_between[index_row][index_coloum];///找出当前测试数据最小的那个距离
	}
	//在换到下一个测试数据之前，必须判断当前的测试结果是否准确无误
	for(int k=0;k<50;k++){
		if(minimum == distance_between[index_row][k]){
			if(k>=0&&k<=4&&index_row>=0&&index_row<=4){
				zero++;accuracy++;}//如果当前的测试数据是0  而且测出的结果也是0，则在0的准确率上加1.
			if(k>=5&&k<=9&&index_row>=5&&index_row<=9){
				one++;accuracy++;}//如果当前的测试数据是1  而且测出的结果也是1，则在1的准确率上加1.
			if(k>=10&&k<=14&&index_row>=10&&index_row<=14){
				two++;accuracy++;}//如果当前的测试数据是2  而且测出的结果也是2，则在2的准确率上加1.
			if(k>=15&&k<=19&&index_row>=15&&index_row<=19){
				three++;accuracy++;}//如果当前的测试数据是3  而且测出的结果也是3，则在3的准确率上加1.
			if(k>=20&&k<=24&&index_row>=20&&index_row<=24){
				four++;accuracy++;}//如果当前的测试数据是4 而且测出的结果也是4，则在4的准确率上加1.
			if(k>=25&&k<=29&&index_row>=25&&index_row<=29){
				five++;accuracy++;}//如果当前的测试数据是5  而且测出的结果也是5，则在5的准确率上加1.
			if(k>=30&&k<=34&&index_row>=30&&index_row<=34){
				six++;accuracy++;}//如果当前的测试数据是6  而且测出的结果也是6，则在6的准确率上加1.
			if(k>=35&&k<=39&&index_row>=35&&index_row<=39){
				seven++;accuracy++;}//如果当前的测试数据是7  而且测出的结果也是7，则在7的准确率上加1.
			if(k>=40&&k<=44&&index_row>=40&&index_row<=44){
				eight++;accuracy++;}//如果当前的测试数据是8  而且测出的结果也是8，则在8的准确率上加1.
			if(k>=45&&k<=49&&index_row>=45&&index_row<=49){
				nine++;accuracy++;}//如果当前的测试数据是9  而且测出的结果也是9，则在9的准确率上加1.
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