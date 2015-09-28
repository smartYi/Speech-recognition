// Allinall.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include"First_step.h"
#include"Multi-templates.h"
#include"third_step.h"
#include"last_step.h"

#define first       (0)
#define second      (0)
#define third       (1)
#define last        (0)
using namespace std;



int main(){
#if first
	 first_step();
#endif

#if second
		Multi_templates();
#endif

#if third
		third_step();
#endif

#if last
		last_step();
#endif
		return 0;
}