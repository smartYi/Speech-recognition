#include"stdafx.h"
#include"read_template.h"
#include "input_file.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;
//Generate a struct that contains feature vectors all of templates

//Functions of reading all feature vectors of all numbers
//Read all numbers

multiple::multiple(void)
{}

multiple::~multiple(void)
{}

void multiple::read(){

	


	//Read number 0
	number_0 = 0;
	double a0;
	ifstream number0;
	number0.open("digit_number_0.txt");
	for(int i = 0;i<100;i++,number_0++){
		for(int j = 0;j < 39;j++){
			number0>>a0;
			temp_0[i][j] = a0;	
		}
		if(number0.eof())
				break;
	}
	//Read number 1
	number_1 = 0;
	double a1;
	ifstream number1;
	number1.open("digit_number_1.txt");
	for(int i = 0;i<100;i++,number_1++){
		for(int j = 0;j < 39;j++){
			number1>>a1;
			temp_1[i][j] = a1;	
		}
		if(number1.eof())
				break;
	}
	//Read number 2
	number_2 = 0;
	double a2;
	ifstream number2;
	number2.open("digit_number_2.txt");
	for(int i = 0;i<100;i++,number_2++){
		for(int j = 0;j < 39;j++){
			number2>>a2;
			temp_2[i][j] = a2;	
		}
		if(number2.eof())
				break;
	}
	//Read number 3
	number_3 = 0;
	double a3;
	ifstream number3;
	number3.open("digit_number_3.txt");
	for(int i = 0;i<100;i++,number_3++){
		for(int j = 0;j < 39;j++){
			number3>>a3;
			temp_3[i][j] = a3;	
		}
		if(number3.eof())
				break;
	}
	//Read number 4
	number_4 = 0;
	double a4;
	ifstream number4;
	number4.open("digit_number_4.txt");
	for(int i = 0;i<100;i++,number_4++){
		for(int j = 0;j < 39;j++){
			number4>>a4;
			temp_4[i][j] = a4;	
		}
		if(number4.eof())
				break;
	}
	//Read number 5
	number_5 = 0;
	double a5;
	ifstream number5;
	number5.open("digit_number_5.txt");
	for(int i = 0;i<100;i++,number_5++){
		for(int j = 0;j < 39;j++){
			number5>>a5;
			temp_5[i][j] = a5;	
		}
		if(number5.eof())
				break;
	}
	//Read number 6
	number_6 = 0;
	double a6;
	ifstream number6;
	number6.open("digit_number_6.txt");
	for(int i = 0;i<100;i++,number_6++){
		for(int j = 0;j < 39;j++){
			number6>>a6;
			temp_6[i][j] = a6;	
		}
		if(number6.eof())
				break;
	}
	//Read number 7
	number_7 = 0;
	double a7;
	ifstream number7;
	number7.open("digit_number_7.txt");
	for(int i = 0;i<100;i++,number_7++){
		for(int j = 0;j < 39;j++){
			number7>>a7;
			temp_7[i][j] = a7;	
		}
		if(number7.eof())
				break;
	}
	//Read number 8
	number_8 = 0;
	double a8;
	ifstream number8;
	number8.open("digit_number_8.txt");
	for(int i = 0;i<100;i++,number_8++){
		for(int j = 0;j < 39;j++){
			number8>>a8;
			temp_8[i][j] = a8;	
		}
		if(number8.eof())
				break;
	}
	//Read number 9
	number_9 = 0;
	double a9;
	ifstream number9;
	number9.open("digit_number_9.txt");
	for(int i = 0;i<100;i++,number_9++){
		for(int j = 0;j < 39;j++){
			number9>>a9;
			temp_9[i][j] = a9;	
		}
		if(number9.eof())
				break;
	}
	
}