#include "../inc/GraphMatrix.h"

int GraphMatrix::FindSet(int verticeNum1)
{
	
	if (verticeNum1 != vertices.at(verticeNum1).parent) 
	{																					//rekurencyjne szukanie rodzica
		vertices.at(verticeNum1).parent = FindSet(vertices.at(verticeNum1).parent);
	}

	return vertices.at(verticeNum1).parent;												//zwracanie rodzica
}



GraphMatrix::~GraphMatrix() {	
															//dekonstruktor
	for (int i = 0; i < numberOfVertices; i++) 
	{
		delete[] tab[i];
	}

	delete[] tab;
}



void GraphMatrix::Union(int a, int b)
{
	int aroot = FindSet(a);
	int broot = FindSet(b);

	if (vertices.at(aroot).rank < vertices.at(vertices.at(broot).parent).rank) 
	{ 																			//komenda at zwraca referencję na element napodanej pozycji
		vertices.at(aroot).parent = broot;
	}
	else 
	{
		vertices.at(broot).parent = aroot;
	}

	if (vertices.at(aroot).rank == vertices.at(broot).rank) 
	{
		vertices.at(aroot).rank++;
	}
}



void GraphMatrix::generateRandomMST(std::vector<Edge> edges, int numberOfVertices)
{
	this->numberOfVertices = numberOfVertices;
	tab = new int* [numberOfVertices] {0};
	tab = new int* [numberOfVertices];

	for (int i = 0; i < numberOfVertices; i++) 
	{
		tab[i] = new int[numberOfVertices] {0};
	}

	for (int i = 0; i < (int)edges.size(); i++)
	{
		tab[edges.at(i).startVertice][edges.at(i).endVertice] = edges.at(i).weight;
		tab[edges.at(i).endVertice][edges.at(i).startVertice] = edges.at(i).weight;
	}
}



void GraphMatrix::display()
{
	std::cout << "Graf w postaci macierzy:" << std::endl << std::endl;
	for (int i = 0; i < numberOfVertices; i++) 
	{
		for (int j = 0; j < numberOfVertices; j++) 
		{
			std::cout << tab[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void GraphMatrix::PrimAlgorithm()
{
	int* parent = new int[numberOfVertices] {-1};			//tablica przechowuje ostatniego rodzica każdego wierzcholka
	int* key = new int[numberOfVertices] {INT_MAX};			//tablica zawierajaca koncowe wartosci key danego wierzcholka
	std::vector<std::pair<int, int>> queue;					//wektor wierzcholkow nierozpatrzonych

	
	for (int i = 0; i < numberOfVertices; i++) 				//petla dodaje do kolejki wierzcholki (para key i numer wierzcholka)
	{			
		queue.push_back(std::make_pair(INT_MAX, i));
	}

	srand(time_t(NULL));									
	
	int startV = rand() % numberOfVertices;					//losowy wierzcholek
	
	parent[startV] = -1;									//rodzic startowego wierzcholka jako -1
	queue.at(startV).first = 0;								//key startowego wierzcholka ustawiamy na 0
	key[startV] = 0;

	
	std::make_heap(queue.begin(), queue.end(), std::greater<>{});			//kopiec minimalny
	std::pair<int, int> extractedVertice;									//wierzcholek z minimalnym key, ktory będzie rozpatrywany w danym obiegu

	while (!queue.empty()) {
		extractedVertice = queue.front();					//wyciagamy wierzcholek z minimalnym key
		queue.erase(queue.begin());							//usuwamy go z kolejki
	
		int verticeNum = extractedVertice.second;			//szukanie sasiadow extractedVertex
															//czytanie numeru wierzcholka ktory wyjelismy z kopca
		std::vector<int> neighbours;						//wektor sasiadow

		for (int i = 0; i < numberOfVertices; i++) 
		{
			if (tab[i][verticeNum] != 0) 
			{
				neighbours.push_back(i);
			}
		}
		
		for (int j = 0; j < (int)queue.size(); j++) 		//przeszukujemy wektor sasiadow i kolejki wierzcholkow nierozpatrzonych
		{
			for (int i = 0; i < (int)neighbours.size(); i++) 
			{
				if (neighbours.at(i) == queue.at(j).second && tab[neighbours.at(i)][verticeNum] < queue.at(j).first) 
				{
					key[neighbours.at(i)] = tab[neighbours.at(i)][verticeNum];
					parent[neighbours.at(i)] = verticeNum;
					queue.at(j).first = key[neighbours.at(i)];
					break;
				}
			}
		}

		
		std::make_heap(queue.begin(), queue.end(), std::greater<>{});		//przywracanie kopca
	}
	std::cout << "Minimalne drzewo rozpinajace dla reprezentacji macierzowej:" << std::endl;
	std::cout << std::endl << "Krawedz      Waga" << std::endl;
	int sum = 0;
	for (int i = 0; i < numberOfVertices; i++) {
		if (parent[i] != -1) {
			std::cout << "(" << i << ", " << parent[i] << ")      " << key[i] << std::endl;
			sum += key[i];
		}
	}
	std::cout << std::endl << "Suma krawedzi minimalnego drzewa rozpinajacego: " << sum << std::endl;
	delete[] key;
	delete[] parent;
}

void GraphMatrix::KruskalAlgorithm()
{
	vertices.clear();
	
	std::vector<Edge> result;											//tworzymy wektor bedacy zbiorem krawedzi tworzacych rozwiazanie
	
	for (int i = 0; i < numberOfVertices; i++) 							//dla kazdego wierzcholka tworzymy graf z jednym wierzcholkiem wskazujacym na samego siebie i dodajemy do wektora wierzcholkow
	{		
		KruskalVertice kruskalVer(i, 0, i);
		vertices.push_back(kruskalVer);
	}

	
	std::vector<Edge> edges;											//dla kazdej krawedzi tworzymy krawedz i dodajemy do wektora krawedzi
	
	for (int i = 0; i < numberOfVertices; i++) 							//petla sprawdza wiersze macierzy i dodaje krawedzie
	{
		for (int j = i + 1; j < numberOfVertices; j++) 
		{
			if (tab[i][j] != 0) 
			{
				edges.push_back(Edge(i, j, tab[i][j]));
			}
		}
	}
	
	std::sort(edges.begin(), edges.end(), std::greater<Edge>());		//sortowanie listy krawedzi (niemalejace wagi)
	
	while (result.size() != (numberOfVertices - 1)) 					//petla pobiera kolejne krawedie dopoki nie znajdzie krawedzi = liczba wierzcholkow -1
	{					
		Edge currentEdge = edges.at(0);
		if (FindSet(currentEdge.startVertice) != FindSet(currentEdge.endVertice)) 
		{
			result.push_back(currentEdge);
			Union(currentEdge.startVertice, currentEdge.endVertice);
		}
		
		edges.erase(edges.begin());										//usuwanie rozpatrzonej krawedzi
	}

	std::cout << std::endl << "Minimalne drzewo rozpinajace dla reprezentacji macierzowej:" << std::endl;
	std::cout << std::endl << "Krawedz     Waga" << std::endl;

	int sum = 0;
	for (int i = 0; i < (int)result.size(); i++) {
		std::cout << "(" << result.at(i).startVertice << ", " << result.at(i).endVertice << ")      " << result.at(i).weight << std::endl;
		sum += result.at(i).weight;
	}
	std::cout << std::endl << "Suma krawedzi minimalnego drzeewa rozpinajacego: " << sum << std::endl;
}
