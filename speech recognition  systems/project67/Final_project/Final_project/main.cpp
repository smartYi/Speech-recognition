#include<iostream>
#include<vector>
#include<fstream>
#define row (51)
#define coloum (1000)
#define loop_back_cost (300)
double  instant_test_data[row][coloum]={0.0};
double  trelly[row][coloum]={0.0};

using namespace std;


int main(){
	double instant;
	vector<double>data;
	ifstream infile;
	infile.open("E:\\JIE course\\speech recognition  systems\\project4\\DCT_stage3\\DCT\\whole_node_cost.txt");
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


	//做DTW
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

	//开始回溯
		vector<int>result;
		double mini_number=100000.0;
		int  index ; 
		int  row_index, coloum_index;
		for(int i=1;i<row;i++)
			if(i%5==0&&trelly[i][coloum_size-1]<mini_number){
				mini_number = trelly[i][coloum_size-1];
				index = i;
			}
		row_index =index;
		coloum_index = coloum_size-1;
		while(coloum_index>0){
			if((row_index-1)%5==0){
				double least  = 100000.0;
				if(trelly[row_index][coloum_index] == trelly[0][coloum_index]+instant_test_data[row_index][coloum_index]){
					result.push_back((row_index-1)/5);
				for(int i=1;i<row;i++)
					if(i%5==0&&trelly[i][coloum_index-1]<least){
						least = trelly[i][coloum_index-1];
						row_index = i;
					}
					coloum_index--;}
				else 
					coloum_index--;
			}
			else{
				if(trelly[row_index-1][coloum_index-1]<trelly[row_index][coloum_index-1]&&trelly[row_index-1][coloum_index-1]<trelly[row_index-1][coloum_index]){
					row_index--;
					coloum_index--;
				}
				else if(trelly[row_index][coloum_index-1]<trelly[row_index-1][coloum_index-1]&&trelly[row_index][coloum_index-1]<trelly[row_index-1][coloum_index])
					coloum_index--;
				else
					row_index--;
			}
		}
				
	cout<<result.size()<<endl;
	for(int i=result.size()-1;i>=0;i--)
		cout<<result.at(i)<<" ";
	system("pause");
	return 0;
}