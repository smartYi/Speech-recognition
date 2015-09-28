#include"stdafx.h"
#include<stdio.h>
#include<iostream>

int get_least(int a,int b,int c){
     int temp;
	 temp = (a < b ? a:b);
	 temp = (temp < c ? temp:c);
	 return temp;
}