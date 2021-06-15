#include "../inc/KruskalVertice.h"

KruskalVertice::KruskalVertice(int verticeNum, int rank, int parent)
{
	this->parent = parent;
	this->rank = rank;
	this->verticeNum = verticeNum;
}