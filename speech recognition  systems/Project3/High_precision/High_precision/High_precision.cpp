// High_precision.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>

using  namespace std;;

int main(){

	int a[1000] = {0};
	     a[0] = 1;
		 int m ;

	for(int i = 0;i<100;i++){  //����100��2
		int c =0;
		for(int n = 0;n<1000;n++){
			int s = a[n] * 2 + c;
		a[n] = s % 10;
		c = s/10;
		}
	}
	for(int i=999;i>=0;i--)
		if(a[i]!=0){	
			m= i;
			break;
		}
		cout<<m;
		cout<<endl;
	for(int j=m;j>=0;j--)
		cout<<a[j];
}