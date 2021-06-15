#include "../inc/Edge.h"

Edge::Edge(int startVertice, int endVertice, int weight)
{
	this->startVertice = startVertice;					//wiercholek poczatkowy
	this->endVertice = endVertice;						//wierzcholek koncowy
	this->weight = weight;								//waga
}
