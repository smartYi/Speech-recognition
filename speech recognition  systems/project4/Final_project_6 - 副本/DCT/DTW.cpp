#include"stdafx.h"
#include<iostream>
#include<ctime>
#include<conio.h>
#include<iomanip>
#include"get_distance.h"
#include"color.h"
#include"DTW.h"

using namespace std;


double DTW(double a[][39], double b[][39],int template_length,int input_length,int selection,int pruning){

	
	int length_of_template;
	int length_of_input;
	//Calculate the rows of template and input
	length_of_template = template_length;
	length_of_input = input_length;

	double distance[100][100] = {0.0};//这个是点距离数组
	double cost[100][100] = {0.0};//这个是不剪枝的cost数组
	double pruning_cost[100][100] = {0.0};//这个是剪枝的cost数组
		
	
	//Calculate the node costs
	for(int i = 0;i<length_of_template;i++)	
		for(int j = 0;j<length_of_input;j++)
	distance[i][j] = get_distance(a[i],b[j]);

	switch(selection){
	case 1:{

	//Calculate the DTW distances
	//First coloum is the same
	for(int i = 0;i<length_of_template;i++)
		cost[i][0] = distance[i][0];
	//Special for the first row
	for(int j = 1;j<length_of_input;j++)
		cost[0][j] = cost[0][j-1] + distance[0][j];
	//Special for 2nd row
	double cost1;
	double cost2;
	double cost3;
	for(int j = 1;j<length_of_input;j++){
		cost1 = cost[0][j-1] + distance[1][j];
		cost2 = cost[1][j-1] + distance[1][j];
		cost[1][j] = ( cost1<cost2?cost1:cost2 );
	}
	
		//For the rest of rows
	for(int i = 2;i<length_of_template;i++)
		for(int j = 1;j<length_of_input;j++){
		cost1 = cost[i-1][j-1] + distance[i][j];
		cost2 = cost[i-2][j-1] + distance[i][j];
		cost3 = cost[i][j-1] + distance[i][j];
		cost[i][j] = (cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3));
		}

		return cost[length_of_template-1][length_of_input-1];
		   }
		   break;

	case 2:{
		//只计算和最小路径相关的那些cost值，最后的结果是除了第一列是只有最小面的cost值之外，其余列只有三个cost值
		//因为每次的比较都是从左下角出发到最右上角，而且本程序中不允许路径垂直方向走
		//也即不能进行模板缩小
	//Calculate the DTW distances
	//First coloum is the same
		
		for(int i=0;i<=pruning;i++){
			pruning_cost[i][0] = distance[i][0];//第一列的cost和distance相同
			if(i>0)
			pruning_cost[0][i] = pruning_cost[0][i-1] + distance[0][i];
		}

	
		int tag_coloum = 0;
		for(tag_coloum=1;tag_coloum<pruning;tag_coloum++){
			for(int i=0;i<pruning+tag_coloum+1;i++){
				if(i==0)
					pruning_cost[i][tag_coloum] = pruning_cost[0][tag_coloum] + distance[0][tag_coloum];
				if(i==1){
					double cost1 = pruning_cost[i-1][tag_coloum-1] + distance[i][tag_coloum];
					double cost2 = pruning_cost[i][tag_coloum-1] + distance[i][tag_coloum];
					pruning_cost[i][tag_coloum] = cost1<cost2?cost1:cost2;
				}
				if(i > 1 && i != (pruning+tag_coloum)){
					double cost1 = pruning_cost[i-1][tag_coloum-1] + distance[i][tag_coloum];
					double cost2 = pruning_cost[i][tag_coloum-1] + distance[i][tag_coloum];
					double cost3 = pruning_cost[i-2][tag_coloum-1] + distance[i][tag_coloum];
					pruning_cost[i][tag_coloum] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
				}
				if(i > 1 && i == (pruning+tag_coloum)){
					double cost1 = pruning_cost[i-1][tag_coloum-1] + distance[i][tag_coloum];
					double cost2 = pruning_cost[i-2][tag_coloum-1] + distance[i][tag_coloum];
					pruning_cost[i][tag_coloum] = cost1<cost2?cost1:cost2;
				}
					
			}
		   }//目前已经计算完毕剪枝的窄边

			for(int tag_coloum=pruning;tag_coloum<length_of_input;tag_coloum++)
				for(int i=tag_coloum-pruning;i<pruning+tag_coloum+1;i++){
					if(i==0)
					pruning_cost[i][tag_coloum] = pruning_cost[0][tag_coloum] + distance[0][tag_coloum];
				   if(i==1){
					double cost1 = pruning_cost[i-1][tag_coloum-1] + distance[i][tag_coloum];
					double cost2 = pruning_cost[i][tag_coloum-1] + distance[i][tag_coloum];
					pruning_cost[i][tag_coloum] = cost1<cost2?cost1:cost2;
				}
				if(i > 1 && i != (pruning+tag_coloum)){
					double cost1 = pruning_cost[i-1][tag_coloum-1] + distance[i][tag_coloum];
					double cost2 = pruning_cost[i][tag_coloum-1] + distance[i][tag_coloum];
					double cost3 = pruning_cost[i-2][tag_coloum-1] + distance[i][tag_coloum];
					pruning_cost[i][tag_coloum] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
				}
				if(i > 1 && i == (pruning+tag_coloum)){
					double cost1 = cost[i-1][tag_coloum-1] + distance[i][tag_coloum];
					double cost2 = cost[i-2][tag_coloum-1] + distance[i][tag_coloum];
					pruning_cost[i][tag_coloum] = cost1<cost2?cost1:cost2;
				}
				}



	//现在只计算左下角那个店能去的三个点，也即pruning_cost[i][j]只能去pruning_cost[i+1][j+1]
		//pruning_cost[i][j+1]和pruning_cost[i+2][j+1]
		//int tag_row = 0;
		//int tag_coloum = 0;
		//if(tag_row<length_of_template-2&&tag_coloum<length_of_input-1){{
		//		int i = tag_row;
		//		int j = tag_coloum;
		//		double cost1 = pruning_cost[i][j] + distance[i+1][j+1];
		//		double cost2 = pruning_cost[i][j] + distance[i+2][j+1];
		//		double cost3 = pruning_cost[i][j] + distance[i][j+1];
		//		if(cost1<cost2&&cost1<cost3){
		//			pruning_cost[i+1][j+1] = cost1;
		//			tag_row = i+1;
		//		    tag_coloum = j+1;
		//		}
		//		if(cost2<cost1&&cost2<cost3){
		//			pruning_cost[i+2][j+1] = cost2;
		//			tag_row = i+2;
		//		    tag_coloum = j+1;
		//		}
		//		if(cost3<cost1&&cost3<cost2){
		//			pruning_cost[i][j+1] = cost3;
		//			tag_row = i;
		//		    tag_coloum = j+1;
		//		}
		//	}
		//}
		////如果现在的路径已经走到了倒数第二行，则下一路径只有两个方向
		// if(tag_row == length_of_template-2&&tag_coloum<length_of_input-1){
		//	int i=tag_row;
		//	int j = tag_coloum;
		//	double cost1 = pruning_cost[i][j] +distance[i][j+1];
		//	double cost2 = pruning_cost[i][j] +distance[i+1][j+1];
		//	if(cost1<cost2){
		//		pruning_cost[i][j+1] = cost1;
		//		tag_row = i;
		//		tag_coloum = j+1;
		//	}
		//	else{
		//		pruning_cost[i+1][j+1] = cost2;
		//		tag_row = i+1;
		//		tag_coloum = j+1;
		//	}
		//}

		////如果到了最后一行，那么只有一个方向可走
		//if((tag_row == length_of_template-1)&&tag_coloum < length_of_input-1){
		//	int i=tag_row;
		//	int j = tag_coloum;
		//	double cost1 = pruning_cost[i][j] + distance[i][j+1];
		//	pruning_cost[i][j+1] = cost1;
		//	tag_coloum = j+1;
		//}
			/*	cout<<pruning_cost[length_of_template-1][length_of_input-1];
		system("pause");*/
		return pruning_cost[length_of_template-1][length_of_input-1];
		   }
		   break;
	default:break;
	}
	
	
}
