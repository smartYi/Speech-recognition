#include"stdafx.h"
#include"DCT.h"
#include"read_template.h"
#include"multiple_template_path.h"
#include"DTW.h"
#include"input_file.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<direct.h>
#include "framedata.h"
#include "Hmm.h"
#include "trainingdata.h"


using namespace std;

//三维数组来储存测试数据和模板数据
double multiple_test_data[50][100][39] = {0.0};
double multiple_template_data[50][100][39] = {0.0};

int main(){

	
	multiple TD;
	TD.read();/////这个是单模板的数据
	vector<string> TB;
	vector<string> TP;
	input_file inputfile;
	TB = inputfile.read_input_compare();////这个是多个测试数据的路径
	multiple_template_path path_of_templates;
	TP = path_of_templates.path_of_multiple_temps();//这个是多模板数据的路径

	//将测试数据存入测试数据三维数组
	int test_row[50] = {0};
	for(int index = 0;index<TB.size();index++){
	double temp = 0.0;
	string filename = TB.at(index);
	ifstream number_input;
	number_input.open(filename,ios::in);
	if(!number_input){
		cout<<"can not open a file."<<endl;
		exit(1);
	}
	for(int i = 0;i<100;i++,test_row[index]++){
		for(int j = 0;j < 39;j++){
			number_input>>temp;
			multiple_test_data[index][i][j] = temp;	
		}
		if(number_input.eof())
				break;
	}
	}


	//将模板数据存入模板数据三维数组
	int template_row[50] = {0};
	for(int index = 0;index<TP.size();index++){
	double temp = 0.0;
	string filename = TP.at(index);
	ifstream number_template;
	number_template.open(filename,ios::in);
	if(!number_template){
		cout<<"can not open a file."<<endl;
		exit(1);
	}
	for(int i = 0;i<100;i++,template_row[index]++){
		for(int j = 0;j < 39;j++){
			number_template>>temp;
			multiple_template_data[index][i][j] = temp;	
		}
		if(number_template.eof())
				break;
	}
	}
	int termination ;
	do{
	//进行比较
	int accuracy = 0;
	int zero= 0, one = 0,two=0,three=0,four=0,five=0,six=0,seven=0,eight=0,nine=0;
	int choice;
	cout<<"Single template, multiple input to push 1; "<<endl<<"Multiple templates,multiple input to push 2; "<<endl;
	cout<<"Test an instant record to push 3; "<<endl;
	cin>>choice;
	termination = choice;
	switch(choice){
	case 1:
		{
	//多输入单模板比较
	double single_template_distance[50][10] = {0.0};//储存距离，用来判断准确率
	       int a=0;
			cout<<"1 to do without pruning, 2 to do with pruning: "<<endl;
			cin>>a;
			int pruning = 0;//选择剪枝的宽度
		 cout<<"Chooose the width of pruning: ";
		  cout<<"Especially 0 of pruning to do without pruning:";
		 cin>>pruning;
	for(int i=0;i<TB.size();i++){
		double minimum = 1000.0;
		int tag = 0;
		{
			single_template_distance[i][0] = DTW(TD.temp_0,multiple_test_data[i],TD.number_0,test_row[i],a,pruning);
			single_template_distance[i][1] = DTW(TD.temp_1,multiple_test_data[i],TD.number_1,test_row[i],a,pruning);
			single_template_distance[i][2] = DTW(TD.temp_2,multiple_test_data[i],TD.number_2,test_row[i],a,pruning);
			single_template_distance[i][3] = DTW(TD.temp_3,multiple_test_data[i],TD.number_3,test_row[i],a,pruning);
			single_template_distance[i][4] = DTW(TD.temp_4,multiple_test_data[i],TD.number_4,test_row[i],a,pruning);
			single_template_distance[i][5] = DTW(TD.temp_5,multiple_test_data[i],TD.number_5,test_row[i],a,pruning);
			single_template_distance[i][6] = DTW(TD.temp_6,multiple_test_data[i],TD.number_6,test_row[i],a,pruning);
			single_template_distance[i][7] = DTW(TD.temp_7,multiple_test_data[i],TD.number_7,test_row[i],a,pruning);
			single_template_distance[i][8] = DTW(TD.temp_8,multiple_test_data[i],TD.number_8,test_row[i],a,pruning);
			single_template_distance[i][9] = DTW(TD.temp_9,multiple_test_data[i],TD.number_9,test_row[i],a,pruning);
	}
	    for(int j=0;j<10;j++)
		if(single_template_distance[i][j]<minimum){
			minimum = single_template_distance[i][j];
			tag = j;
		}
	if (tag==0&&i>=0&&i<=4&&minimum!=0){
		zero++;
		accuracy++;
	}
	if (tag==1&&i>=5&&i<=9&&minimum!=0){
		one++;
		accuracy++;
	}
	if (tag==2&&i>=10&&i<=15&&minimum!=0){
		two++;
		accuracy++;
	}
	if (tag==3&&i>=15&&i<=19&&minimum!=0){
		three++;
		accuracy++;
	}
	if (tag==4&&i>=20&&i<=24&&minimum!=0){
		four++;
		accuracy++;
	}
	if (tag==5&&i>=25&&i<=29&&minimum!=0){
		five++;
		accuracy++;
	}
	if (tag==6&&i>=30&&i<=34&&minimum!=0){
		six++;
		accuracy++;
	}
	if (tag==7&&i>=35&&i<=39&&minimum!=0){
		seven++;
		accuracy++;
	}
	if (tag==8&&i>=40&&i<=44&&minimum!=0){
		eight++;
		accuracy++;
	}
	if (tag==9&&i>=45&&i<=49&&minimum!=0){
		nine++;
		accuracy++;
	}
	}
	cout<<accuracy<<endl;
	cout<<setw(6)<<"zero = "<<zero<<endl<<setw(6)<<"one = "<<one<<endl<<setw(6)<<"two = "<<two<<endl;
	cout<<setw(6)<<"three = "<<three<<endl<<setw(6)<<"four = "<<four<<endl<<setw(6)<<"five = "<<five<<endl;
	cout<<"six = "<<six<<endl<<"seven = "<<seven<<endl<<"eight = "<<eight<<endl;
	cout<<setw(6)<<"nine = "<<nine<<endl;
		   }break;

	//多输入多模板比较
	//TB储存测试数据，TP储存模板数据

	case 2:
		{
	double multiple_template_distance[50][50] = {0.0};//储存距离，用来判断准确率
	        int b=0;
			cout<<"1 to do without pruning, 2 to do with pruning: "<<endl;
			cin>>b;
			int pruning = 0;//选择剪枝的宽度
		 cout<<"Chooose the width of pruning: ";
		  cout<<"Especially 0 of pruning to do without pruning:";
		 cin>>pruning;
	for(int i=0;i<TB.size();i++){
		double minimum  = 1000.0;
		int tag = 0;
		for(int j=0;j<TP.size();j++)
		{
			multiple_template_distance[i][j] = DTW(multiple_template_data[j],multiple_test_data[i],template_row[j],test_row[i],b,pruning);
			if(multiple_template_distance[i][j]<minimum){
			minimum = multiple_template_distance[i][j];
			tag = j;
	}
		}
		if (tag>=0&&tag<=4&&i>=0&&i<=4&&minimum!=0){
		zero++;
		accuracy++;
	}
		if (tag>=5&&tag<=9&&i>=5&&i<=9&&minimum!=0){
		one++;
		accuracy++;
	}
	if (tag>=10&&tag<=14&&i>=10&&i<=14&&minimum!=0){
		two++;
		accuracy++;
	}
	if (tag>=15&&tag<=19&&i>=15&&i<=19&&minimum!=0){
		three++;
		accuracy++;
	}
	if (tag>=20&&tag<=24&&i>=20&&i<=24&&minimum!=0){
		four++;
		accuracy++;
	}
	if (tag>=25&&tag<=29&&i>=25&&i<=29&&minimum!=0){
		five++;
		accuracy++;
	}
	if (tag>=30&&tag<=34&&i>=30&&i<=34&&minimum!=0){
		six++;
		accuracy++;
	}
	if (tag>=35&&tag<=39&&i>=35&&i<=39&&minimum!=0){
		seven++;
		accuracy++;
	}
	if (tag>=40&&tag<=44&&i>=40&&i<=44&&minimum!=0){
		eight++;
		accuracy++;
	}
	if (tag>=45&&tag<=49&&i>=45&&i<=49&&minimum!=0){
		nine++;
		accuracy++;
	}
	}
	cout<<accuracy<<endl;
	cout<<setw(6)<<"zero = "<<zero<<endl<<setw(6)<<"one = "<<one<<endl<<setw(6)<<"two = "<<two<<endl;
	cout<<setw(6)<<"three = "<<three<<endl<<setw(6)<<"four = "<<four<<endl<<setw(6)<<"five = "<<five<<endl;
	cout<<"six = "<<six<<endl<<"seven = "<<seven<<endl<<"eight = "<<eight<<endl;
	cout<<setw(6)<<"nine = "<<nine<<endl;
		}
		break;
	
	//即时单词录音，并且比对与单一模板结果
	case 3:
		{
	   double least[10] = {0.0};
	   double minimum =1000.0;
	   int tag = 0;
       DCT();
	//Read instant number
	int instant_number = 0;
	double instant_test_data[100][39] = {0.0};
	double instant;
	ifstream infile;
	infile.open("input_record.txt");
	for(int i = 0;i<100;i++,instant_number++){
		for(int j = 0;j < 39;j++){
			infile>>instant;
			instant_test_data[i][j] = instant;	
		}
		if(infile.eof())
				break;
	}

	int selection = 0;
	cout<<"Do without pruning to push 1: "<<endl<<"Do with pruning to push 2: "<<endl;
	cout<<"Pruning or not? ";
	cin>>selection;
	int pruning = 0;//选择剪枝的宽度
		 cout<<"Chooose the width of pruning: ";
		 cout<<"Especially 0 of pruning to do without pruning:";
		 cin>>pruning;
	//求得即时数据与单一模板之间的距离，共10个
	least[0] = DTW(TD.temp_0,instant_test_data,TD.number_0,instant_number,selection,pruning);
	least[1] = DTW(TD.temp_1,instant_test_data,TD.number_1,instant_number,selection,pruning);
	least[2] = DTW(TD.temp_2,instant_test_data,TD.number_2,instant_number,selection,pruning);
	least[3] = DTW(TD.temp_3,instant_test_data,TD.number_3,instant_number,selection,pruning);
	least[4] = DTW(TD.temp_4,instant_test_data,TD.number_4,instant_number,selection,pruning);
	least[5] = DTW(TD.temp_5,instant_test_data,TD.number_5,instant_number,selection,pruning);
	least[6] = DTW(TD.temp_6,instant_test_data,TD.number_6,instant_number,selection,pruning);
	least[7] = DTW(TD.temp_7,instant_test_data,TD.number_7,instant_number,selection,pruning);
	least[8] = DTW(TD.temp_8,instant_test_data,TD.number_8,instant_number,selection,pruning);
	least[9] = DTW(TD.temp_9,instant_test_data,TD.number_9,instant_number,selection,pruning);

	//找出最小的距离
	for(int i=0;i<10;i++)
		if(least[i]<minimum){
			minimum = least[i];
			tag = i;
		}
		if(minimum==0)
			tag = 10;
		cout<<endl;
		//输出判断结果
		switch (tag)
		{
		case 0: cout<<"Do you say 0 ? ";break;
		case 1: cout<<"Do you say 1 ? ";break;
		case 2: cout<<"Do you say 2 ? ";break;
		case 3: cout<<"Do you say 3 ? ";break;
		case 4: cout<<"Do you say 4 ? ";break;
		case 5: cout<<"Do you say 5 ? ";break;
		case 6: cout<<"Do you say 6 ? ";break;
		case 7: cout<<"Do you say 7 ? ";break;
		case 8: cout<<"Do you say 8 ? ";break;
		case 9: cout<<"Do you say 9 ? ";break;
		case 10:cout<<"Can not identify the recording!";break;
		default:
			break;
		}
		}
		default:
		break;
		}
		system("pause");
		}while(termination);
return 0;

}
	
		
	
	