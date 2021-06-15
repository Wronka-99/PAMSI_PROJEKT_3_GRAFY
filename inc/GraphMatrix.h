#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "Edge.h"
#include "KruskalVertice.h"
#include <algorithm>



class GraphMatrix							//klasa macierz sasiedztwa
{
private:
	
	int** tab;								//wskaznik na tablice dwuwymiarowa zawierajaca macierz sasiedztwa
	int numberOfVertices;					//liczba wierzcholkow
	int numberOfEdges;						//liczba krawedzi
	std::vector<KruskalVertice> vertices;	//wektor krawedzi potrzebny w algorytmie kruskala
	int startingVertice;					//krawedz poczatkowa
	int FindSet(int verticeNum);			
	void Union(int verOne, int verTwo);
public:
	~GraphMatrix();
	
	void generateRandomMST(std::vector<Edge> edges, int  numberOfVertices);			
	void display();
	void PrimAlgorithm();
	void KruskalAlgorithm();

};

