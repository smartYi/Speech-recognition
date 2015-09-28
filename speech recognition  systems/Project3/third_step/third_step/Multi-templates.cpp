// Second_Step.cpp : �������̨Ӧ�ó������ڵ㡣
//
//

#include "stdafx.h"
#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include <fstream>
#include<iomanip>
#include <ostream>
#define fixed_boundary  (0);
#define beam_boundary   (1);
const int num           (3);
using namespace std;

//�ҳ��ڶ�ģ����̾�����һ��

int find_least(int*a){
	for(int i=0;i<10;i++)
		for(int j=i+1;j<10;j++)
			if(a[i]>a[j]){
			int tem = a[i];
			a[i] = a[j];
			a[j] = tem;
			}
			return a[0];
}
 
int get_least(int a,int b,int c){
     int temp;
	 temp = (a < b ? a:b);
	 temp = (temp < c ? temp:c);
	 return temp;
}

int get_distance(string templ,string input){
	int    ally;
	int    trelly1;
	int    trelly2;
	int    trelly3;

	//���������ַ���vector
	vector<char>   templ_vector;
	vector<char>   input_vector;//Ӧ����main��������������

	
	/////�����ַ������������һ��������·������
	


	/////�������ַ������Ϊvector��ʽ//
	for(int i = 0;i<templ.length();i++)
		templ_vector.push_back(templ[i]);
	for(int i=0;i<input.length();i++)
		input_vector.push_back(input[i]);

	//�ж������ַ���������ĸ�Ƿ���ͬ������ͬʹ�����ǵ�����ĸ��ͬΪ0
	if(templ_vector.at(0)!=input_vector.at(0)){
		templ_vector.insert(templ_vector.begin(),0);
		input_vector.insert(input_vector.begin(),0);}
	//�����ά��̬�������洢trelly//
	int** trelly;
	trelly = new int*[templ_vector.size()];
	for(int i=0;i<templ_vector.size();i++){
		trelly[i] = new int[input_vector.size()];}

#if   fixed_boundary
	{
	//��ʼ��trelly��һ�к͵�һ�е�����
	for(int j=0;j<input_vector.size();j++)
		trelly[0][j] = j;
	
		
		
	for(int i=0;i<templ_vector.size();i++){
		trelly[i][0] = i;
		if(trelly[i][0]>3)
			trelly[i][0] = 10000;}
		
	////�����￪ʼ����trelly��ÿһ�����ֵ

	for(int j=1;j<input_vector.size();j++){
		for(int i = 1;i<templ_vector.size();i++){
			if(templ_vector.at(i) == input_vector.at(j))
				ally = 0;
			else 
				ally = 1;
	trelly1 = trelly[i-1][j-1] + ally;
	trelly2 = trelly[i-1][j] + 1;
	trelly3 = trelly[i][j-1] + 1;
	trelly[i][j] = get_least(trelly1,trelly2,trelly3);  
		}
		for(int n=0;n<templ_vector.size();n++)
			if(trelly[n][j]>3)
				trelly[n][j] = 10000;
		
	}
	cout<<endl<<"The distance between two strings is: "<<trelly[templ_vector.size()-1][input_vector.size()-1]<<endl;
	
	//ͨ��C++���������
	cout<<left;
	cout<<setw(templ_vector.size())<<" ";
	for(int i=0;i<input_vector.size();i++)
		cout<<setw(templ_vector.size())<<input_vector.at(i);
	    cout<<endl;
	for(int i=0;i<templ_vector.size();i++){
		cout<<setw(templ_vector.size())<<templ_vector.at(i);
		for(int j=0;j<input_vector.size();j++)
	        cout<<setw(templ_vector.size())<<trelly[i][j];
		cout<<endl;
	}
	}
#endif

#if  beam_boundary
	{
	//��ʼ��trelly��һ�к͵�һ�е�����
	for(int j=0;j<input_vector.size();j++)
		trelly[0][j] = j;
		
		
	for(int i=0;i<templ_vector.size();i++){
		trelly[i][0] = i;
		if(trelly[i][0]>3)
			trelly[i][0] = 10000;}
		
	////�����￪ʼ����trelly��ÿһ�����ֵ

	for(int j=1;j<input_vector.size();j++){
		int    min = 100000;
		for(int i = 1;i<templ_vector.size();i++){
			if(templ_vector.at(i) == input_vector.at(j))
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
       for(int i = 0;i<templ_vector.size();i++)
		   if(trelly[i][j]>(min+3))
			   trelly[i][j] = 10000;
	}
	cout<<endl<<"The distance between two strings is: "<<trelly[templ_vector.size()-1][input_vector.size()-1]<<endl;
	
	//ͨ��C++���������
	cout<<left;
	cout<<setw(templ_vector.size())<<" ";
	for(int i=0;i<input_vector.size();i++)
		cout<<setw(templ_vector.size())<<input_vector.at(i);
	    cout<<endl;
	for(int i=0;i<templ_vector.size();i++){
		cout<<setw(templ_vector.size())<<templ_vector.at(i);
		for(int j=0;j<input_vector.size();j++)
	        cout<<setw(templ_vector.size())<<trelly[i][j];
		cout<<endl;
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
	return trelly[templ_vector.size()-1][input_vector.size()-1];

}


///
int main(){

vector<string> templs;
vector<string> inputs;
int*           point_distance;
               point_distance[templs]
int    small_distance;

cout<<endl<<"Enter templates: "<<endl;
for(int i=0;i<num;i++)
	getline(cin,templs[i],'#');

cout<<endl<<"Enter an input string: "<<endl;
getline(cin,inputs,'#');

//����ÿ��template��input֮��ľ���

for(int i=0;i<num;i++)
	distance[i] = get_distance(templs[i],inputs);

small_distance = find_least(distance);

//�ҳ���̾����Ӧ���Ǹ�ģ���ַ���

for(int i=0;i<num;i++)
	if(distance[i] == small_distance)
		cout<<endl<<"Do you mean : "<<templs[i]<<" "<<"?"<<endl;



}