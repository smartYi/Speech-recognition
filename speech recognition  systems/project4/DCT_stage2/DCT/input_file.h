#pragma once
#include"stdafx.h"
#include <vector>
#include <string>
using namespace std;

class input_file
{
public:
	input_file(void);
	~input_file(void);
	vector<string> read_input_compare();
};

