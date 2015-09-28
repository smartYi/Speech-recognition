// try.cpp : 定义控制台应用程序的入口点。
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


//读取字典txt文件//

//
//ifstream templread("dict.txt");
//string maintempl;
//while(templread>>maintempl){
//	templs_vector.push_back(maintempl);
//	cout<<maintempl<<endl;
//}

//读取input txt文件
 ifstream  input_read("story.txt");
 string inputs;
 while(input_read>>inputs){
	 inputs_vector.push_back(inputs);
 }
 cout<<inputs_vector.at(3)<<" "<<inputs_vector.size();
	
 return 0;
}