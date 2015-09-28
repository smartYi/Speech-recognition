#include "stdafx.h"
#include"read_template.h"
#include"Synchronous.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>

using namespace std;


Synchronous::Synchronous(void)
{
}


Synchronous::~Synchronous(void)
{
}

	
void Synchronous::synchronous()
{
	multiple TD;
	TD.read();
	 zero = TD.number_0 ; one = TD.number_1; two= TD.number_2;three=TD.number_3;
	 four=TD.number_4; five= TD.number_5; six=TD.number_6; seven=TD.number_7;
	 eight =TD.number_8; nine = TD.number_9;
	/* int zero = TD.number_0 , one = TD.number_1, two= TD.number_2,three=TD.number_3;
	 int four=TD.number_4, five= TD.number_5, six=TD.number_6, seven=TD.number_7;
	 int eight =TD.number_8, nine = TD.number_9;*/

	pile_row = zero+one+two+three+four+five+six+seven+eight+nine;
	
	//Pile up all template arrays.
	for(int i=0;i<zero;i++)
		for(int j = 0;j<39;j++){
			pile_template[i][j] = TD.temp_0[i][j];
		}

	for(int i=zero;i<zero+one;i++)
		for(int j = 0;j<39;j++){
			pile_template[i][j] = TD.temp_1[i-zero][j];
		}

	for(int i=zero+one;i<zero+one+two;i++)
		for(int j = 0;j<39;j++){
			pile_template[i][j] = TD.temp_2[i-zero-one][j];
		}

	for(int i=zero+one+two;i<zero+one+two+three;i++)
		for(int j = 0;j<39;j++){
			pile_template[i][j] = TD.temp_3[i-zero-one-two][j];
		}

	for(int i=zero+one+two+three;i<zero+one+two+three+four;i++)
		for(int j = 0;j<39;j++){
			pile_template[i][j] = TD.temp_4[i-zero-one-two-three][j];
		}

	for(int i=zero+one+two+three+four;i<zero+one+two+three+four+five;i++)
		for(int j = 0;j<39;j++){
			pile_template[i][j] = TD.temp_5[i-zero-one-two-three-four][j];
		}

	for(int i=zero+one+two+three+four+five;i<zero+one+two+three+four+five+six;i++)
		for(int j = 0;j<39;j++){
			pile_template[i][j] = TD.temp_6[i-zero-one-two-three-four-five][j];
		}

	for(int i=zero+one+two+three+four+five+six;i<zero+one+two+three+four+five+six+seven;i++)
		for(int j = 0;j<39;j++){
			pile_template[i][j] = TD.temp_7[i-zero-one-two-three-four-five-six][j];
		}

	for(int i=zero+one+two+three+four+five+six+seven;i<zero+one+two+three+four+five+six+seven+eight;i++)
		for(int j = 0;j<39;j++){
			pile_template[i][j] = TD.temp_8[i-zero-one-two-three-four-five-six-seven][j];
		}

	for(int i=zero+one+two+three+four+five+six+seven+eight;i<zero+one+two+three+four+five+six+seven+eight+nine;i++)
		for(int j = 0;j<39;j++){
			pile_template[i][j] = TD.temp_9[i-zero-one-two-three-four-five-six-seven-eight][j];
		}


		


}

