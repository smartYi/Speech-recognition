#pragma once
#include "kmeandata.h"
#include "kmeanprocess.h"
class dtw
{
public:
	dtw(void);
	~dtw(void);

	void get_segmental(kmeandata *data, kmeanprocess pro);
};

