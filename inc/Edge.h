#pragma once
#include <climits>

class Edge
{
public:
	Edge(int startVertice, int endVertice, int weight);  //konstruktor
	int startVertice;									 // wierzcholek poczatkowy
	int endVertice;										 // wierzcholek koncowy
	int weight;										     // waga krawedzi
	bool operator > (const Edge& str) const				 // operator niezbedny podczas sortowania, porownuje wagi krawedzi
	{
		return (weight < str.weight);
	}
};


