#include"stdafx.h"
#include<iostream>
#include<vector>
#include<fstream>
#include"DCT.h"
#define row (51)
#define coloum (1000)
#define loop_back_cost (300)
double  instant_test_data[row][coloum]={0.0};
double  trelly[row][coloum]={0.0};
double  flag[row][coloum]={0.0};

using namespace std;


double Minimum(double a, double b, double c) 
{ 
 double mi; 
 
 mi = a; 
 if (b < mi) { 
  mi = b; 
 } 
 if (c < mi) { 
  mi = c; 
 } 
 return mi; 
}

int main(){
	DCT();
	double instant;
	vector<double>data;
	ifstream infile;
	//infile.open("E:\\JIE course\\speech recognition  systems\\project4\\DCT_stage3\\DCT\\whole_node_cost.txt");
	infile.open("whole_node_cost.txt");
	if(!infile)
		cout<<"can not open a file.";
	while(!infile.eof()){
	infile>>instant;
	data.push_back(instant);
	}

	int coloum_size = data.size()/50;
	for(int i=1;i<row;i++)
		for(int j=0;j<coloum_size;j++)
			instant_test_data[i][j] = data.at((i-1)*coloum_size+j);


	//×öDTW
	trelly[0][0] = 0.0;
	for(int i=1;i<row;i++){
		if((i-1)%5==0)
			trelly[i][0] = trelly[0][0] + instant_test_data[i][0];
		else
			trelly[i][0] = trelly[i-1][0] + instant_test_data[i][0];
	}
	double minimum = 100000.0;
	for(int i=1;i<row;i++){
		if(i%5==0&&trelly[i][0]<minimum)
			minimum = trelly[i][0];
	}
	trelly[0][1] = minimum + loop_back_cost;

		for(int j=1;j<coloum_size;j++){
			double mini = 100000.0;
			for(int i=1;i<row;i++){
			if((i-1)%5==0){
				double cost1 = trelly[0][j]+instant_test_data[i][j];
				double cost2 = trelly[i][j-1]+instant_test_data[i][j];
				trelly[i][j] = cost1<cost2?cost1:cost2;
			}
			else{
				double cost1 = trelly[i-1][j]+instant_test_data[i][j];
				double cost2 = trelly[i-1][j-1]+instant_test_data[i][j];
				double cost3 = trelly[i][j-1]+instant_test_data[i][j];
				trelly[i][j] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
			}
		}
			for(int i=1;i<row;i++)
				if(i%5==0&&trelly[i][j]<mini)
					mini = trelly[i][j];
			trelly[0][j+1] = mini+loop_back_cost;
	}

	for(int i=2;i<row;i++)
		for(int j=1;j<coloum_size;j++)
		{
			if(trelly[i][j-1]==Minimum(trelly[i][j-1],trelly[i-1][j-1],trelly[i-1][j]))
				flag[i][j]=1;
			else if (trelly[i-1][j]==Minimum(trelly[i][j-1],trelly[i-1][j-1],trelly[i-1][j]))
				      flag[i][j]=2;
			else flag[i][j]=3;
		}
		for(int i=0;i<row;i++)
		    flag[i][0]=2;
	for(int i=0;i<11;i++)
		for(int j=0;j<coloum_size;j++)
			flag[i*5+1][j]=1;



		int mark=0;
		int row_number=1;
		double	mam_rownumber=trelly[1][coloum_size-1];
		for(int i=2;i<row;i++)
		{
			if(trelly[i][coloum_size-1]<mam_rownumber)
			{
				mam_rownumber=trelly[i][coloum_size-1];
				row_number=i;
			}
		}

		int change_row=row_number,change_coloum=coloum_size-1;

		for(int i=coloum_size-1;i>0;i--) //»ØËÝ
		{
			if((change_row%5)==0&&mark==0)
				cout<<change_row/5<<endl;
		if(flag[change_row][change_coloum]==1)
		{
			change_coloum-=1;
			mark=1;
		}
		if(flag[change_row][change_coloum]==2)
		{
			change_row-=1;
			mark=0;
		}
		if(flag[change_row][change_coloum]==3)
		{
			change_coloum-=1;
			change_row-=1;
			mark=0;
		}
		if((change_row-1)%5==0)
		{
			mam_rownumber=trelly[1][change_coloum-1];
			for(int j=2;j<row;j++)
		{
			
			if(trelly[j][change_coloum-1]<mam_rownumber)
			{
				mam_rownumber=trelly[j][change_coloum-1];
				change_row=j;
				
			}
			change_coloum=change_coloum-1;
		}
		}
		}
	return 0;
}