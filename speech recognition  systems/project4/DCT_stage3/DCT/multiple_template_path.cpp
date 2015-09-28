#include "stdafx.h"
#include "multiple_template_path.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#include <direct.h>


multiple_template_path::multiple_template_path(void)
{
}


multiple_template_path::~multiple_template_path(void)
{
}


//本函数返回多模板数据的路径，并且按照0——9的顺序依次存放在一维vector里面
vector<string> multiple_template_path::path_of_multiple_temps()
{
	
	/*char   buffer[100];   
		getcwd(buffer, 100);   
		ifstream inputfile;
		string filename = buffer;
		filename = filename + "\\one\\";
		char t = i+1+48;
		filename = filename + t;
		filename = filename + "\\delta.txt";*/
	//Generate a path array to store pathes of different test data..
	vector<string>path_of_templates;
	char current_path_templates[100];

	for(int i = 0;i<10;i++){
		switch(i){
		case 0:{
		_getcwd(current_path_templates,100);
		for(int j = 0;j<5;j++){
			string filename = current_path_templates;
			filename = filename + "\\template\\";
			filename = filename + "\zero\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\digit_number_0.txt";
			path_of_templates.push_back(filename);
		} 
			   }
			   break;

	    case 1:{
		_getcwd(current_path_templates,100);
		for(int j = 0;j<5;j++){
			string filename = current_path_templates;
			filename = filename + "\\template\\";
			filename = filename + "\one\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\digit_number_1.txt";
			path_of_templates.push_back(filename);
		} 
			   }
			   break;

		case 2:{
		_getcwd(current_path_templates,100);
		for(int j = 0;j<5;j++){
			string filename = current_path_templates;
			filename = filename + "\\template\\";
			filename = filename + "two\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\digit_number_2.txt";
			path_of_templates.push_back(filename);
		} 
			   }
			   break;

	 case 3:{
		_getcwd(current_path_templates,100);
		for(int j = 0;j<5;j++){
			string filename = current_path_templates;
			filename = filename + "\\template\\";
			filename = filename + "three\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\digit_number_3.txt";
			path_of_templates.push_back(filename);
		} 
			   }
			   break;

		case 4:{
		_getcwd(current_path_templates,100);
		for(int j = 0;j<5;j++){
			string filename = current_path_templates;
			filename = filename + "\\template\\";
			filename = filename + "four\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\digit_number_4.txt";
			path_of_templates.push_back(filename);
		} 
			   }
			   break;

		case 5:{
		_getcwd(current_path_templates,100);
		for(int j = 0;j<5;j++){
			string filename = current_path_templates;
			filename = filename + "\\template\\";
			filename = filename + "five\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\digit_number_5.txt";
			path_of_templates.push_back(filename);
		} 
			   }
			   break;

		case 6:{
		_getcwd(current_path_templates,100);
		for(int j = 0;j<5;j++){
			string filename = current_path_templates;
			filename = filename + "\\template\\";
			filename = filename + "six\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\digit_number_6.txt";
			path_of_templates.push_back(filename);
		} 
			   }
			   break;

		case 7:{
		_getcwd(current_path_templates,100);
		for(int j = 0;j<5;j++){
			string filename = current_path_templates;
			filename = filename + "\\template\\";
			filename = filename + "seven\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\digit_number_7.txt";
			path_of_templates.push_back(filename);
		} 
			   }
			   break;

	    case 8:{
		_getcwd(current_path_templates,100);
		for(int j = 0;j<5;j++){
			string filename = current_path_templates;
			filename = filename + "\\template\\";
			filename = filename + "eight\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\digit_number_8.txt";
			path_of_templates.push_back(filename);
		} 
			   }
			   break;

        case 9:{
		_getcwd(current_path_templates,100);
		for(int j = 0;j<5;j++){
			string filename = current_path_templates;
			filename = filename + "\\template\\";
			filename = filename + "nine\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\digit_number_9.txt";
			path_of_templates.push_back(filename);
		} 
			   }
			   break;

		default:break;
		}

}
//cout<<path_of_templates.size()<<endl;
//for(int i=0;i<path_of_templates.size();i++)
//	cout<<path_of_templates.at(i)<<endl;
//system("pause");
return path_of_templates;
}
