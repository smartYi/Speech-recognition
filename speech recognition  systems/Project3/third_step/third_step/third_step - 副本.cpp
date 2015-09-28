// stringtest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "get_least.h"
#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include <fstream>
#include<iomanip>
#include <ostream>
#define fixed_boundary  (0);
#define beam_boundary   (1);
using namespace std;



int get_least(int a,int b,int c){
     int temp;
	 temp = (a < b ? a:b);
	 temp = (temp < c ? temp:c);
	 return temp;
}



int get_distance(int trelly[][50], string templ,string input){
	int    ally;
	int    trelly1;
	int    trelly2;
	int    trelly3;

	/////将两个字符串输出为vector形式//
	//for(int i = 0;i<templ.length();i++)
	//	templ_vector.push_back(templ[i]);
	//for(int j=0;j<input.length();j++)
	//	if((input[j]!=',')&&(input[j]!='.')&&input[j]!='\n')////注意这里的是单引号
	//	input_vector.push_back(input[j]);
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
	/*{
	ofstream write_to_txt1;
	write_to_txt1.open("trelly.txt");
	write_to_txt1.clear();
	write_to_txt1.close();
	ofstream write_to_txt2;
	write_to_txt2.open("trelly.txt",ios::app);
	for(int i=0;i<templ_vector.size();i++){
		for(int j = 0;j<input_vector.size();j++)
			write_to_txt2<<trelly[i][j]<<" ";
		    write_to_txt2<<endl;
	}
			write_to_txt2.close();
	}*/
	return trelly[templ.length()-1][input.length()-1];


}



int main(){

vector <string>  templs_vector;
vector <string>  inputs_vector;

//构造一个固定矩阵大小，确保进行的字符串比较不大过矩阵
int            static_trelly[30][50];
int            counter = 0;


//读取字典txt文件//
{
ofstream write_to_txt1;
	write_to_txt1.open("spell_check.txt");
	write_to_txt1.clear();
	write_to_txt1.close();
}


ifstream templread("dict.txt");
string maintempl;
while(templread>>maintempl)
	templs_vector.push_back(maintempl);

//读取input txt文件
 ifstream  input_read("story.txt");
 string inputs;
 while(input_read>>inputs)
	 inputs_vector.push_back (inputs);

 ///判断input每个字符串与dict中所有模板的距离，并且输出最短距离对应的那个字符串
 

 for(int i=0;i<inputs_vector.size();i++){
	 int            small_distance=1000;
	 string tempor = inputs_vector.at(i);
	 int distance[6618] = {0};
	 for(int j = 0;j<templs_vector.size();j++){
		 distance[j] = get_distance(static_trelly,templs_vector.at(j),tempor);
		 
		 if(distance[j] < small_distance)
			 small_distance = distance[j];
		
	 }
///找出最短距离对应那个字符串，也即模板
	
	/* for(int k=0;k<6618;k++)
    	if(distance[k] == small_distance){
			cout<<templs_vector.at(k)<<" ";
		    break;
		}*/

	 //将纠正文本写入txt
	 {
	ofstream write_to_txt2;
	write_to_txt2.open("spell_check.txt",ios::app);
	 for(int k=0;k<templs_vector.size();k++)
    	if(distance[k] == small_distance){
			cout<<templs_vector.at(k)<<" ";
			write_to_txt2<<templs_vector.at(k)<<" ";
			counter++;
		    break;
		}
		  
			write_to_txt2.close();
	 }
      

	  
 }
 cout<<counter;
 cout<<endl;
return 0;
 }


