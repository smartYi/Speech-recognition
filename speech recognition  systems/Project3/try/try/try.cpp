// try.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include <fstream>
#include<iomanip>
#include <ostream>
using namespace std;


int main(){

vector <string>  templs_vector;
vector <string>  inputs_vector;
int            small_distance=1000;


//��ȡ�ֵ�txt�ļ�//

//
//ifstream templread("dict.txt");
//string maintempl;
//while(templread>>maintempl){
//	templs_vector.push_back(maintempl);
//	cout<<maintempl<<endl;
//}

//��ȡinput txt�ļ�
 ifstream  input_read("story.txt");
 string inputs;
 while(input_read>>inputs){
	 inputs_vector.push_back(inputs);
 }
 cout<<inputs_vector.at(3)<<" "<<inputs_vector.size();
	
 return 0;
}