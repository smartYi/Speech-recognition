#include "stdafx.h"
#include "input_file.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#include <direct.h>

input_file::input_file(void)
{
}


input_file::~input_file(void)
{
}
//本函数返回测试数据的路径，并且按照0——9 的顺序依次存放在一维vector里面
vector<string> input_file::read_input_compare()
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
	vector<string>path;
	char current_path[100];

	for(int i = 0;i<10;i++){
		switch(i){
		case 0:{
		_getcwd(current_path,100);
		for(int j = 0;j<5;j++){
			string filename = current_path;
			filename = filename + "\\zero\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\input_record.txt";
			path.push_back(filename);
		} 
			   }
			   break;

	    case 1:{
		_getcwd(current_path,100);
		for(int j = 0;j<5;j++){
			string filename = current_path;
			filename = filename + "\\one\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\input_record.txt";
			path.push_back(filename);
		} 
			   }
			   break;

		case 2:{
		_getcwd(current_path,100);
		for(int j = 0;j<5;j++){
			string filename = current_path;
			filename = filename + "\\two\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\input_record.txt";
			path.push_back(filename);
		} 
			   }
			   break;

	 case 3:{
		_getcwd(current_path,100);
		for(int j = 0;j<5;j++){
			string filename = current_path;
			filename = filename + "\\three\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\input_record.txt";
			path.push_back(filename);
		} 
			   }
			   break;

		case 4:{
		_getcwd(current_path,100);
		for(int j = 0;j<5;j++){
			string filename = current_path;
			filename = filename + "\\four\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\input_record.txt";
			path.push_back(filename);
		} 
			   }
			   break;

		case 5:{
		_getcwd(current_path,100);
		for(int j = 0;j<5;j++){
			string filename = current_path;
			filename = filename + "\\five\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\input_record.txt";
			path.push_back(filename);
		} 
			   }
			   break;

		case 6:{
		_getcwd(current_path,100);
		for(int j = 0;j<5;j++){
			string filename = current_path;
			filename = filename + "\\six\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\input_record.txt";
			path.push_back(filename);
		} 
			   }
			   break;

		case 7:{
		_getcwd(current_path,100);
		for(int j = 0;j<5;j++){
			string filename = current_path;
			filename = filename + "\\seven\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\input_record.txt";
			path.push_back(filename);
		} 
			   }
			   break;

	    case 8:{
		_getcwd(current_path,100);
		for(int j = 0;j<5;j++){
			string filename = current_path;
			filename = filename + "\\eight\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\input_record.txt";
			path.push_back(filename);
		} 
			   }
			   break;

        case 9:{
		_getcwd(current_path,100);
		for(int j = 0;j<5;j++){
			string filename = current_path;
			filename = filename + "\\nine\\";
			char t = j+1+48;
			filename = filename + t;
			filename = filename + "\\input_record.txt";
			path.push_back(filename);
		} 
			   }
			   break;

		default:break;
		}

}
return path;
}
