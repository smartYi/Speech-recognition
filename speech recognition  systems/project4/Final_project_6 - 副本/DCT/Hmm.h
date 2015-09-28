#include "stdafx.h"
#pragma once
#include "framedata.h"
#include <vector>
using namespace std;
class Hmm
{
public:
	Hmm(void);
	~Hmm(void);
	framedata means[5];
	framedata cov[5];
};

