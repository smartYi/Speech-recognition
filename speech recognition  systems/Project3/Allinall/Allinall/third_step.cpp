// stringtest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include <fstream>
#include<iomanip>
#include <ostream>
#include<time.h>
#include"get_least.h"
#define fixed_boundary  (0);
#define beam_boundary   (1);
using namespace std;



int& get_distance(int trelly[][100], string templ,string input);

 int& get_distance(int trelly[][100], string templ,string input){
	int    ally;
	int    trelly1;
	int    trelly2;
	int    trelly3;

	int row = templ.length();
	int coloum= input.length();

	//�ж������ַ��������һ���ǲ��Ǳ�����
	char ch = input[coloum-1];
	if(ch == ','|| ch =='.'|| ch =='!'|| ch == ';'|| ch == '?')
		input.erase(input.end());


	//�ж������ַ���������ĸ�Ƿ���ͬ������ͬʹ�����ǵ�����ĸ��ͬΪ0
	if(templ[0]!=input[0]){
		templ = " "+templ;
		input = " "+input;
	}
	
#if   fixed_boundary
	{
	//��ʼ��trelly��һ�к͵�һ�е�����
	for(int j=0;j<input.length();j++){
		trelly[0][j] = j;
	if(trelly[0][j] > 3){
		trelly[0][j] = 10000;
	break;
	}
	}
	
		
		
	for(int i=0;i<templ.length();i++){
		trelly[i][0] = i;
		if(trelly[i][0]>3){
			trelly[i][0] = 10000;
		break;
		}
	}
		
	////�����￪ʼ����trelly��ÿһ�����ֵ

	for(int j=1;j<input.length();j++){
		for(int i = 1;i<templ.length();i++){
			if(templ[i] == input[j])
				ally = 0;
			else 
				ally = 1;
	    if(trelly[i-1][j-1] !=10000)
	    trelly1 = trelly[i-1][j-1] + ally;
		if(trelly[i-1][j] !=10000)	
	    trelly2 = trelly[i-1][j] + 1;
		if(trelly[i][j-1] !=10000)	
	    trelly3 = trelly[i][j-1] + 1;
	   trelly[i][j] = get_least(trelly1,trelly2,trelly3);  
		}
		for(int n=0;n<templ.length();n++)
			if(trelly[n][j]>3)
				trelly[n][j] = 10000;
		
	}
	
	}
#endif

#if  beam_boundary
	{
	//��ʼ��trelly��һ�к͵�һ�е�����
		for(int j=0;j<input.length();j++)
		   trelly[0][j] = j;
		
		for(int i=0;i<templ.length();i++){
		trelly[i][0] = i;
		if(trelly[i][0]>3)
			trelly[i][0] = 10000;
		}
		
	////�����￪ʼ����trelly��ÿһ�����ֵ

	for(int j=1;j<input.length();j++){
		int    min = 100000;
		for(int i = 1;i<templ.length();i++){
			if(tolower(templ[i]) == tolower(input[j]))
				ally = 0;
			else 
				ally = 1;
		if(trelly[i-1][j-1] !=10000)
	    trelly1 = trelly[i-1][j-1] + ally;
		if(trelly[i-1][j] !=10000)	
	    trelly2 = trelly[i-1][j] + 1;
		if(trelly[i][j-1] !=10000)	
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
	}
#endif

	return trelly[templ.length()-1][input.length()-1];


}



void third_step(){



vector <string>  templs_vector;
vector <string>  inputs_vector;

//����һ���̶������С��ȷ�����е��ַ����Ƚϲ��������
int            static_trelly[100][100];
for(int i=0;i<100;i++)
	for(int j=0;j<100;j++)
		static_trelly[i][j] = 10000;
int            counter = 0;


//��ȡ�ֵ�txt�ļ�//
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

//��ȡinput txt�ļ�
    vector<string>words2;//���浥��
	vector<vector<string>>input;//�������
	char ch2;
	string temp2 ;

	ifstream txt2_read("story.txt");
	while(!txt2_read.eof()){
		ch2 = txt2_read.get();
		if(ch2 ==','||ch2 =='"'||ch2 ==' '||ch2 ==';'||ch2=='\n'||ch2==':'){
			if(temp2 !="")
			words2.push_back(temp2);
			temp2.clear();}
		else if(ch2 =='.'||ch2 =='!'||ch2 =='?'){
		if(temp2!="")
		words2.push_back(temp2);
		input.push_back(words2);
		temp2.clear();
		words2.clear();
		}
		else {
		temp2 = temp2 + ch2;
		}
	}

 ///�ж�inputÿ���ַ�����dict������ģ��ľ��룬���������̾����Ӧ���Ǹ��ַ���


	for(int n=0;n<input.size();n++){
		
		for(int i = 0;i<input.at(n).size();i++){
			 int            small_distance=1000;
			 int            distance[6618] ={0};
			  string tempor = input.at(n).at(i);
			  
			for(int j = 0;j<templs_vector.size();j++){
				
				distance[j] = get_distance(static_trelly,templs_vector.at(j),tempor);
			
				if(distance[j] < small_distance)
					small_distance = distance[j];
			}
	/*	
	system("pause");
	cout<<"here1";
				*/
///�ҳ���̾����Ӧ�Ǹ��ַ�����Ҳ��ģ��
	 //�������ı�д��txt
	 {/*system("pause");
		cout<<input.size();*/
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
	 tempor.erase();
		}
		 {
	ofstream write_to_txt3;
	write_to_txt3.open("spell_check.txt",ios::app);
			write_to_txt3<<"."<<" ";
			write_to_txt3.close();
	 }
		 
		
	}
		
 }
	