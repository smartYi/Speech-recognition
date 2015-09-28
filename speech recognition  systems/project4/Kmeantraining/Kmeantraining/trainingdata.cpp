#include "trainingdata.h"
#include <iostream>
#include <fstream>
#include <istream>
using namespace std;

trainingdata::trainingdata(void)
{
	frame_count = 0;
}


trainingdata::~trainingdata(void)
{
}

trainingdata::trainingdata(string filename)
{
	ifstream inputfile;
	inputfile.open(filename);
	int count = 0;
	
	while(! inputfile.eof())
	{
		double tem[39];
		double temnumber;
		inputfile >> temnumber;
		tem[count++] = temnumber;
		if(count == 39)
		{
			count = 0;
			framedata a(tem);
			dctdata.push_back(a);
		}
	}
	frame_count = dctdata.size();
}

int trainingdata::get_framecount()
{
	return frame_count;
}
