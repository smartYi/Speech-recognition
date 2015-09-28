// stringtest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include <fstream>
#include<iomanip>
#include <ostream>

#define story           (1);
#define spell_check     (0);
using namespace std;



int get_least(int a,int b,int c){
     int temp;
	 temp = (a < b ? a:b);
	 temp = (temp < c ? temp:c);
	 return temp;
}

//定义一个结构体，内含元素返回距离值，insertion，deletion，substitution。
typedef struct 
{
	int leastdistance;
	int insertion;
	int deletion;
	int sunstitution;
}component;

component get_distance(int trelly[][100], vector<string> templ,vector<string> input){
	int    ally;
	int    trelly1;
	int    trelly2;
	int    trelly3;
	component TD;	

//判断首单词是否相同
	if(templ.at(0) != input.at(0)){
		templ.insert(templ.begin(),"0");
		input.insert(input.begin(),"0");
	}

	//初始化trelly第一行和第一列的数据
		for(int j=0;j<input.size();j++)
		   trelly[0][j] = j;
		
		for(int i=0;i<templ.size();i++)
		trelly[i][0] = i;
		
		
	////从这里开始计算trelly的每一格的数值

		for(int j=1;j<input.size();j++){
		int    min = 100000;
		for(int i = 1;i<templ.size();i++){
			if(input.at(j)==templ.at(i))
				ally = 0;
			else 
				ally = 1;
		
	trelly1 = trelly[i-1][j-1] + ally;
			
	trelly2 = trelly[i-1][j] + 1;
			
	trelly3 = trelly[i][j-1] + 1;

	trelly[i][j] = get_least(trelly1,trelly2,trelly3);  
		}
			}
	
	TD.leastdistance = trelly[templ.size()-1][input.size()-1];
	
		//构造数组每个元素的标识符
		int tag[100][100]={0};

	//对最短距离路径上的元素进行颜色tag标示
	int m = templ.size()-1;
	int n = input.size()-1;
	int deletion = 0;
	int insertion = 0;
	int substitution = 0;
	tag[m][n] = 1;
	tag[0][0] = 1;
	while(m>0||n>0){
    
	if(n>0&&trelly[m][n-1] ==trelly[m][n]-1){
	 n = n-1;
	 tag[m][n] = 1;
	 insertion++;
	}
	else if(m>0&&trelly[m-1][n] ==trelly[m][n]-1){
		m = m-1;
		tag[m][n] = 1;
		deletion++;
	}
	else{
		m = m-1;n = n-1;
		tag[m][n] = 1;
		if(trelly[m][n] != trelly[m+1][n+1])
			substitution++;
	}
	}
	TD.sunstitution = substitution;
	TD.deletion = deletion;
	TD.insertion = insertion;

		
	return TD;

	}


int main(){

#if story
	{
	int static_trelly[100][100] = {0};

	//构造一个两层vector
	vector<string>words1;//储存单词
	vector<vector<string>>sentence;//储存句子
	char ch;
	string temp ;

	ifstream txt_read("storycorrect.txt");
	while(!txt_read.eof()){
		ch = txt_read.get();
		if(ch ==','||ch =='"'||ch==':'||ch ==' '||ch ==';'||ch == '\n'){
			if(temp != "")
			words1.push_back(temp);
			temp.clear();
		}
		else if(ch =='.'||ch =='!'||ch =='?'){
			words1.push_back(temp);
			sentence.push_back(words1);
			temp.clear();
			words1.clear();			
		}
		else {
		temp = temp + ch;
		}
	}
	
	//读入input
//构造一个两层vector

	vector<string>words2;//储存单词
	vector<vector<string>>input;//储存句子
	char ch2;
	string temp2 ;

	ifstream txt2_read("story.txt");
	while(!txt2_read.eof()){
		ch2 = txt2_read.get();
		if(ch2 ==','||ch2 =='"'||ch==':'||ch2 ==' '||ch2 ==';'||ch2 =='\n'){
			if(temp2 != "")
			words2.push_back(temp2);
			temp2.clear();}
		else if(ch2 =='.'||ch2 =='!'||ch2 =='?'){
		words2.push_back(temp2);
		input.push_back(words2);
		temp2.clear();
		words2.clear();
		}
		else {
		temp2 = temp2 + ch2;
		}
	}
	
 //判断句子与句子之间的距离，并且计算句子之间的insertion、deletion、substitution。
 
     int            deletion = 0 ;
	 int            insertion = 0;
	 int            substitution = 0;
	 component      mycmponent;
	 int distance[100] = {0};
	for(int i=0;i<input.size();i++){
	 int            small_distance=1000;
	 vector<string>tempor1;
	 vector<string>tempor2;
	  tempor2 = input.at(i);
	  tempor1 = sentence.at(i);
		 mycmponent = get_distance(static_trelly,tempor1,tempor2);
		 distance[i] = mycmponent.leastdistance;
		 substitution+=mycmponent.sunstitution;
		 insertion+=mycmponent.insertion;
		 deletion+=mycmponent.deletion;
		
		
	}
	cout<<"deletion = "<<deletion<<endl<<"insertion = "<<insertion<<endl<<"substitution = "<<substitution<<endl;
	}
#endif

#if spell_check
	{
	int static_trelly[100][100] = {0};

	//构造一个两层vector
	vector<string>words1;//储存单词
	vector<vector<string>>sentence;//储存句子
	char ch;
	string temp ;

	ifstream txt_read("storycorrect.txt");
	while(!txt_read.eof()){
		ch = txt_read.get();
		if(ch ==','||ch==':'||ch =='"'||ch ==' '||ch ==';'||ch == '\n'){
			if(temp !="")
			words1.push_back(temp);
			temp.clear();
		}
		else if(ch =='.'||ch =='!'||ch =='?'){
			words1.push_back(temp);
			sentence.push_back(words1);
			temp.clear();
			words1.clear();			
		}
		else {
		temp = temp + ch;
		}
	}
	
	//读入input
//构造一个两层vector

	//构造一个两层vector
	vector<string>words2;//储存单词
	vector<vector<string>>input;//储存句子
	char ch2;
	string temp2 ;

	ifstream txt_read2("spell_check.txt");
	while(!txt_read2.eof()){
		ch2 = txt_read2.get();
		if(ch2 ==' '||ch2 == '\n'){
			if(temp2 !="")
			words2.push_back(temp2);
			temp2.clear();
		}
		else if(ch2 =='.'){
			if(temp != "")
			words1.push_back(temp);
			input.push_back(words2);
			temp2.clear();
			words2.clear();			
		}
		else {
		temp2 = temp2 + ch2;
		}
	}
	
 //判断句子与句子之间的距离，并且计算句子之间的insertion、deletion、substitution。
 
     int            deletion = 0 ;
	 int            insertion = 0;
	 int            substitution = 0;
	 component      mycmponent;
	 int distance[100] = {0};
	for(int i=0;i<input.size();i++){
	 int            small_distance=1000;
	 vector<string>tempor1;
	 vector<string>tempor2;
	  tempor2 = input.at(i);
	  tempor1 = sentence.at(i);
		 mycmponent = get_distance(static_trelly,tempor1,tempor2);
		 distance[i] = mycmponent.leastdistance;
		 substitution+=mycmponent.sunstitution;
		 insertion+=mycmponent.insertion;
		 deletion+=mycmponent.deletion;
		
		
	}

	cout<<"deletion = "<<deletion<<endl<<"insertion = "<<insertion<<endl<<"substitution = "<<substitution<<endl;
	}
#endif

 return 0;
 }


