#include "stdafx.h"
#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include <fstream>
#include<iomanip>
#include <ostream>
using namespace std;

	int get_distance(int trelly[][50], string templ,string input){
	int    ally;
	int    trelly1;
	int    trelly2;
	int    trelly3;

	int row = templ.length();
	int coloum= input.length();

	//判断输入字符串的最后一个是不是标点符号
	if(input[coloum-1] == ','||input[coloum-1]=='.'||input[coloum-1]=='!')
		input.erase(input.end());


	//判断两个字符串的首字母是否相同，不相同使得他们的首字母相同为0
	if(tolower(templ[0])!=tolower(input[0])){
		templ = " "+templ;
		input = " "+input;
	}
	
#if   fixed_boundary
	{
	//初始化trelly第一行和第一列的数据
	for(int j=0;j<input.length();j++)
		trelly[0][j] = j;
	
		
		
	for(int i=0;i<templ.length();i++){
		trelly[i][0] = i;
		if(trelly[i][0]>3)
			trelly[i][0] = 10000;}
		
	////从这里开始计算trelly的每一格的数值

	for(int j=1;j<input.length();j++){
		for(int i = 1;i<templ.length();i++){
			if(templ[i] == input[j])
				ally = 0;
			else 
				ally = 1;
	trelly1 = trelly[i-1][j-1] + ally;
	trelly2 = trelly[i-1][j] + 1;
	trelly3 = trelly[i][j-1] + 1;
	trelly[i][j] = get_least(trelly1,trelly2,trelly3);  
		}
		for(int n=0;n<templ.length();n++)
			if(trelly[n][j]>3)
				trelly[n][j] = 10000;
		
	}
	/*cout<<endl<<"The distance between two strings is: "<<trelly[templ.length()-1][input.length()]<<endl;*/
	
	//通过C++来制作表格
	/*cout<<left;
	cout<<setw(templ_vector.size())<<" ";
	for(int i=0;i<input_vector.size();i++)
		cout<<setw(templ_vector.size())<<input_vector.at(i);
	    cout<<endl;
	for(int i=0;i<templ_vector.size();i++){
		cout<<setw(templ_vector.size())<<templ_vector.at(i);
		for(int j=0;j<input_vector.size();j++)
	        cout<<setw(templ_vector.size())<<trelly[i][j];
		cout<<endl;
	}*/
	}
#endif

#if  beam_boundary
	{
	//初始化trelly第一行和第一列的数据
		for(int j=0;j<input.length();j++)
		   trelly[0][j] = j;
		
		for(int i=0;i<templ.length();i++){
		trelly[i][0] = i;
		if(trelly[i][0]>3)
			trelly[i][0] = 10000;
		}
		
	////从这里开始计算trelly的每一格的数值

	for(int j=1;j<input.length();j++){
		int    min = 100000;
		for(int i = 1;i<templ.length();i++){
			if(tolower(templ[i]) == tolower(input[j]))
				ally = 0;
			else 
				ally = 1;
		
	trelly1 = trelly[i-1][j-1] + ally;
			
	trelly2 = trelly[i-1][j] + 1;
			
	trelly3 = trelly[i][j-1] + 1;

	trelly[i][j] = get_least(trelly1,trelly2,trelly3);  
	if(trelly[i][j]<min)
		min = trelly[i][j];
		}
		if(trelly[0][j]<min)
			min = trelly[0][j];
       for(int i = 0;i<input.length();i++)
		   if(trelly[i][j]>(min+3))
			   trelly[i][j] = 10000;
	}
	//cout<<endl<<"The distance between two strings is: "<<trelly[templ.length()-1][input.length()-1]<<endl;
	//
	////通过C++来制作表格
	//cout<<left;
	//cout<<setw(templ_vector.size())<<" ";
	//for(int i=0;i<input_vector.size();i++)
	//	cout<<setw(templ_vector.size())<<input_vector.at(i);
	//    cout<<endl;
	//for(int i=0;i<templ_vector.size();i++){
	//	cout<<setw(templ_vector.size())<<templ_vector.at(i);
	//	for(int j=0;j<input_vector.size();j++)
	//        cout<<setw(templ_vector.size())<<trelly[i][j];
	//	cout<<endl;
	//}
	}
#endif

	return trelly[templ.length()-1][input.length()-1];



}