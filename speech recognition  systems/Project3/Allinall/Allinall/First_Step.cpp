// Dynamic_Programming.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<Windows.h>
#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include <fstream>
#include<iomanip>
#include <ostream>
#include"get_least.h"

#define fixed_boundary  (0);
#define beam_boundary   (1);
using  namespace std;

//设置颜色句柄
static void  SetConsoleColor(WORD wAttribute)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, wAttribute);
}
 
inline ostream&  defcolor(ostream& ostr)
{
    SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    return ostr;
}
 
inline ostream&  greencolor(ostream& ostr)
{
    SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return ostr;
}
 
inline ostream&  bluecolor(ostream& ostr)
{
    SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    return ostr;
}
 
inline ostream&  redcolor(ostream& ostr)
{
    SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    return ostr;
}
 
inline ostream&  lredcolor(ostream& ostr)
{
    SetConsoleColor(FOREGROUND_RED);
    return ostr;
}
 

//
//int get_least(int a,int b,int c){
//     int temp;
//	 temp = (a < b ? a:b);
//	 temp = (temp < c ? temp:c);
//	 return temp;
//}

void first_step(){
	int    ally;
	string templ;
	string input;               //定义两个字符串

	cout<<endl<<"Enter a template: "<<endl;
	getline(cin,templ);
	cout<<endl<<"Enter an input word: "<<endl;
	getline(cin,input);
	

	//判断两个字符串的首字母是否相同，不相同使得他们的首字母相同为0
	
		templ = " " + templ;
	    input = " " +input;
	
	//构造二维数组来存储trelly//

	int  trelly[50][50] ;
	
	for(int i =0 ;i<50;i++){
		for(int j =0;j<50;j++)
			trelly[i][j] = 10000;
		}
	
#if   beam_boundary


	{
	//初始化trelly第一行和第一列的数据	
		trelly[0][1] = 1;
		for(int i=0;i<templ.length();i++){
		trelly[i][0] = i;
		if(trelly[i][0]>3){
		trelly[i][0] = 10000;
		break;
		}
		}
	////从这里开始计算trelly的每一格的数值
		for(int j=1;j<input.length();j++){
		    int small_distance = 10000;
			for(int i = 0;i<templ.length();i++){
			int    trelly1 = 10000;
	        int    trelly2 = 10000;
	        int    trelly3 = 10000;

			//如果是第一行的数据，他只能是左边数据加1得到
			if(i == 0){
				trelly[i][j] = trelly[i][j-1]+1; 
				if(trelly[i][j] < small_distance)
					small_distance = trelly[i][j];
				continue;
			}
			if(templ[i] == input[j])
				ally = 0;
			else 
				ally = 1;
			
			if(trelly[i-1][j-1] != 10000)
	        trelly1 = trelly[i-1][j-1] + ally;
			if(trelly[i-1][j] != 10000)
	        trelly2 = trelly[i-1][j] + 1;
			if(trelly[i][j-1] != 10000)
	        trelly3 = trelly[i][j-1] + 1;
	       trelly[i][j] = get_least(trelly1,trelly2,trelly3);  
		   if(small_distance > trelly[i][j])
			   small_distance = trelly[i][j];
		   }
			for(int n=0;n<templ.length();n++)
				if(trelly[n][j] > small_distance+3)
					trelly[n][j] = 10000;
		}
	
		cout<<endl<<"The distance between two strings is: "<<trelly[templ.length()-1][input.length()-1]<<endl;
	
	//构造数组每个元素的标识符
	int tag[50][50] = {0};

	//对最短距离路径上的元素进行颜色tag标示
	int m = templ.length()-1;
	int n = input.length()-1;
	tag[m][n] = 1;
	tag[0][0] = 1;
	while(m>0||n>0){
    
	if(n>0&&trelly[m][n-1] ==trelly[m][n]-1){
	 n = n-1;
	 tag[m][n] = 1;}
	else if(m>0&&trelly[m-1][n] ==trelly[m][n]-1){
		m = m-1;
		tag[m][n] = 1;}
	else{
		m = m-1;n = n-1;
		tag[m][n] = 1;
	}
	}
	
	//通过C++来制作表格
	cout<<left;
	cout<<setw(6)<<" ";
	for(int i=0;i<input.length();i++)
		cout<<defcolor<<setw(6)<<input[i];
	    cout<<endl;
		for(int i=0;i<templ.length();i++){
		cout<<setw(6)<<templ[i];
		for(int j=0;j<input.length();j++){
			if(tag[i][j] == 1)
	        cout<<greencolor<<setw(6)<<trelly[i][j];
			else
			cout<<defcolor<<setw(6)<<trelly[i][j];
		}
		cout<<defcolor<<endl;
	}
	}
#endif

#if  fixed_boundary
	int tag_row;
	int tag_coloum;

	{
	//初始化trelly第一行和第一列的数据
		for(int j=0;j<input.length();j++){
		trelly[0][j] = j;
		if(trelly[0][j] > 3){
			trelly[0][j] = 10000;
		    tag_row = j;
		    break;
		}
		}
		
		
		for(int i=0;i<templ.length();i++){
		trelly[i][0] = i;
		if(trelly[i][0]>3){
			trelly[i][0] = 10000 ;
			tag_coloum = i;
		    break;
		}

		}
		
	////从这里开始计算trelly的每一格的数值

		for(int j=1;j<input.length();j++){
		int    min = 100000;
		for(int i = 1;i<templ.length();i++){
			int    trelly1 = 10000;
	        int    trelly2 = 10000;
	        int    trelly3 = 10000;
			if(templ[i] == input[j])
				ally = 0;
			else 
				ally = 1;
			//判断接下来要求解的点是否已经超出两条斜线之外，如果超出，跳过计算。
	    if((j-i)>tag_row || (i-j) > tag_coloum)
			continue;
		else {
			if(trelly[i-1][j-1] != 10000)
	        trelly1 = trelly[i-1][j-1] + ally;
			if(trelly[i-1][j] != 10000)
	        trelly2 = trelly[i-1][j] + 1;
			if(trelly[i][j-1] != 10000)
	        trelly3 = trelly[i][j-1] + 1;
			trelly[i][j] = get_least(trelly1,trelly2,trelly3);  
			if(trelly[i][j] > 3){
				trelly[i][j] = 10000;
				if(j-i > 0)
					tag_row = j-i;
				if(i-j > 0)
					tag_coloum = i-j;
			}
	 
		}
		}
	}
		cout<<endl<<"The distance between two strings is: "<<trelly[templ.length()-1][input.length()-1]<<endl;
	///找出最短距离路径
	
	
	//构造数组每个元素的标识符
	int tag[50][50] = {0};

	//对最短距离路径上的元素进行颜色tag标示
	int m = templ.length()-1;
	int n = input.length()-1;
	tag[m][n] = 1;
	tag[0][0] = 1;
	while(m>0||n>0){
    
	if(n>0&&trelly[m][n-1] ==trelly[m][n]-1){
	 n = n-1;
	 tag[m][n] = 1;}
	else if(m>0&&trelly[m-1][n] ==trelly[m][n]-1){
		m = m-1;
		tag[m][n] = 1;}
	else{
		m = m-1;n = n-1;
		tag[m][n] = 1;
	}
	}
	
	//通过C++来制作表格
	cout<<left;
	cout<<setw(6)<<" ";
	for(int i=0;i<input.length();i++)
		cout<<defcolor<<setw(6)<<input[i];
	    cout<<endl;
		for(int i=0;i<templ.length();i++){
		cout<<setw(6)<<templ[i];
		for(int j=0;j<input.length();j++){
			if(tag[i][j] == 1)
	        cout<<greencolor<<setw(6)<<trelly[i][j];
			else
			cout<<defcolor<<setw(6)<<trelly[i][j];
		}
		cout<<defcolor<<endl;
	}
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
	

}