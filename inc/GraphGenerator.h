#pragma once
#include "Edge.h"
#include <vector>
#include <time.h>
#include <iostream>
class GraphGenerator
{
public:
	std::vector<Edge> generateMST(int numberOfVertices, int densityPercentage);     //metoda tworzaca graf 
};

