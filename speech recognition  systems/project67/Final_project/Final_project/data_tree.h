#ifndef DATA_TREE_H
#define DATA_TREE_H
#pragma once

typedef struct 
{
	double hmm[100][39];
}Node;
class data_tree
{
public:
	data_tree(void);
	~data_tree(void);
private:
	Node* next;
};
#endif

