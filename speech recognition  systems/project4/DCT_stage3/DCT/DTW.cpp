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

	double distance[100][100] = {0.0};//����ǵ��������
	double cost[100][100] = {0.0};//����ǲ���֦��cost����
	double pruning_cost[100][100] = {0.0};//����Ǽ�֦��cost����
		
	
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
		//ֻ�������С·����ص���Щcostֵ�����Ľ���ǳ��˵�һ����ֻ����С���costֵ֮�⣬������ֻ������costֵ
		//��Ϊÿ�εıȽ϶��Ǵ����½ǳ����������Ͻǣ����ұ������в�����·����ֱ������
		//Ҳ�����ܽ���ģ����С
	//Calculate the DTW distances
	//First coloum is the same
		
		for(int i=0;i<=pruning;i++){
			pruning_cost[i][0] = distance[i][0];//��һ�е�cost��distance��ͬ
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
		   }//Ŀǰ�Ѿ�������ϼ�֦��խ��

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



	//����ֻ�������½��Ǹ�����ȥ�������㣬Ҳ��pruning_cost[i][j]ֻ��ȥpruning_cost[i+1][j+1]
		//pruning_cost[i][j+1]��pruning_cost[i+2][j+1]
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
		////������ڵ�·���Ѿ��ߵ��˵����ڶ��У�����һ·��ֻ����������
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

		////����������һ�У���ôֻ��һ���������
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
