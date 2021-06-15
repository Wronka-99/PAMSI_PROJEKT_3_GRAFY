#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <string>
#include <fstream>
#include <queue>
#include "Edge.h"
#include "KruskalVertice.h"
#include <algorithm>


class GraphList						//klasa przechowuje graf na liscie sasiadow
{
private:
	
	class Node						//klasa wezel
	{
	public:
		
		Node(int verticeNum, int weight);		//konstruktor
		int verticeNum;							//numer wierzcholka
		int weight;								//waga krawedzi
	};

	std::vector<std::list<Node>> vec;			//wektor z listami sasiadow dla wierzcholkow
	int numberOfVertices;						//liczba wierzcholkow
	int numberOfEdges;							//liczba krawedzi grafu
	std::vector<KruskalVertice> vertices;		//wektor zawierajacy krawedzie w algorytmie Kruskala
	int startingVertice;						//wierzcholek poczatkowy
	int FindSet(int verticeNum);
	void Union(int verOne, int verTwo);
public:
	~GraphList();

	void generateRandomMST(std::vector<Edge> edges, int  numberOfVertices);			//analogiczne metody jak dla macierzy
	void display();
	void PrimAlgorithm();
	void KruskalAlgorithm();
};
