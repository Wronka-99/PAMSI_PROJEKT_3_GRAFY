#include "../inc/GraphList.h"

GraphList::~GraphList() {
	vec.clear();
}

int GraphList::FindSet(int verticeNum1)
{
	if (verticeNum1 != vertices.at(verticeNum1).parent) 
	{
		vertices.at(verticeNum1).parent = FindSet(vertices.at(verticeNum1).parent);
	}
	return vertices.at(verticeNum1).parent;
}

void GraphList::Union(int a, int b)
{
	int aroot = FindSet(a);
	int broot = FindSet(b);
	if (vertices.at(aroot).rank < vertices.at(vertices.at(broot).parent).rank)
	 {
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

void GraphList::generateRandomMST(std::vector<Edge> edges, int numberOfVertices)
{
	this->numberOfVertices = numberOfVertices;
	for (int i = 0; i < numberOfVertices; i++) 
	{
		std::list<Node> list;
		vec.push_back(list);
	}

	for (int i = 0; i < (int)(int)edges.size(); i++) 
	{
		vec.at(edges.at(i).startVertice).push_back(Node(edges.at(i).endVertice, edges.at(i).weight));
		vec.at(edges.at(i).endVertice).push_back(Node(edges.at(i).startVertice, edges.at(i).weight));
	}
}






void GraphList::display()
{
	std::cout << std::endl << std::endl << "Graf w postaci listy sasiedztwa:" << std::endl << std::endl;
	for (int i = 0; i < (int)vec.size(); i++) 
	{
		std::list<Node> currentList = vec.at(i);
		std::cout << "Wierzcholek " << i << ": ";

		for (auto it = currentList.begin(); it != currentList.end(); ++it) 
		{
			std::cout << (*it).verticeNum << "|" << (*it).weight << "-->";
		}

		std::cout << std::endl;
	}
}


void GraphList::PrimAlgorithm()
{
	
	int* parent = new int[numberOfVertices] {-1};				//tablica zwiera ostatniego rodzica kazdego wierzcholka
	int* key = new int[numberOfVertices] { INT_MAX };			//tablica przechowuje wartosci key kazdego wierzcholka
	
	std::vector<std::pair<int, int>> queue;						//wektor z wierzcholkami nierozpatrzonymi
	
	for (int i = 0; i < numberOfVertices; i++) 					//petla dodaje do kolejki wierzcholki (para key i numer wierzcholka)
	{
		queue.push_back(std::make_pair(INT_MAX, i));
	}
	
	int startV = rand() % numberOfVertices;						//losowy wierzcholek
	
	parent[startV] = -1;										//rodzic startowego wierzcholka jako -1
	
	queue.at(startV).first = 0;									//key startowego wierzcholka ustawiamy na 0
	key[startV] = 0;
	
	std::make_heap(queue.begin(), queue.end(), std::greater<>{});		//tworzymy kopiec minimalny
	std::pair<int, int> extractedVertice;								//wierzcholek z minimalnym key, ktory będzie rozpatrywany w danym obiegu

	while (!queue.empty()) 
	{
		
		extractedVertice = queue.front();				//wyciagamy wierzcholek z minimalnym key
		queue.erase(queue.begin());						//usuwamy go z kolejki
		int verticeNum = extractedVertice.second;		//szukanie sasiadow extractedVertex
		std::vector<int> neighbours;					//wektor sasiadow

		std::list<Node> currentList = vec.at(verticeNum);	//wypelninie listy sasiadow

		for (auto it = currentList.begin(); it != currentList.end(); ++it) 
		{
			neighbours.push_back((*it).verticeNum);
		}
		
		for (int j = 0; j < (int)queue.size(); j++) 				//przeszukujemy wektor sasiadow i kolejki wierzcholkow nierozpatrzonych
		{
			for (int i = 0; i < (int)neighbours.size(); i++) 
			{
				
				if (neighbours.at(i) == queue.at(j).second) 			//jesli znalezlismy sasiada w kolejce nierozpatrzonych wierzcholkow
				{
					for (auto it = currentList.begin(); it != currentList.end(); ++it) 
					{
						
						if ((*it).verticeNum == neighbours.at(i) && (*it).weight < queue.at(j).first) 		//jesli podczas przegladania listy trafimy na sasiada
						{
							key[neighbours.at(i)] = (*it).weight;
							parent[neighbours.at(i)] = verticeNum;
							queue.at(j).first = key[neighbours.at(i)];
							break;
						}
					}
				}
			}
		}
		std::make_heap(queue.begin(), queue.end(), std::greater<>{});				//przywracanie kopca
	}

	std::cout << std::endl << "Minimalne drzewo rozpinajace dla reprezentacji listowej:" << std::endl;
	std::cout << std::endl << "Krawedz      Waga" << std::endl;
	int sum = 0;

	for (int i = 0; i < numberOfVertices; i++) {
		if (parent[i] != -1) {
			std::cout << "(" << i << ", " << parent[i] << ")      " << key[i] << std::endl;
			sum += key[i];
		}
	}
	std::cout << std::endl << "Suma krawedzi minimalnego drzewa rozpinajacego: " << sum << std::endl;
	delete[] parent;
	delete[] key;
}

void GraphList::KruskalAlgorithm()
{
	vertices.clear();
	
	std::vector<Edge> result;			//tworzymy wektor bedacy zbiorem krawedzi tworzacych rozwiazanie
	
	for (int i = 0; i < numberOfVertices; i++) 		//dla kazdego wierzcholka tworzymy graf z jednym wierzcholkiem wskazujacym na samego siebie i dodajemy do wektora wierzcholkow
	{
		KruskalVertice kruskalVer(i, 0, i);
		vertices.push_back(kruskalVer);
	}
	
	std::vector<Edge> edges;						//dla kazdej krawedzi tworzymy krawedz i dodajemy do wektora krawedzi
	
	std::list<Node> currentList;			
	for (int i = 0; i < numberOfVertices; i++) 		//petla przeglada liste sasiadow dla kazdego wierzcholka
	{
		currentList = vec.at(i);
		for (auto it = currentList.begin(); it != currentList.end(); ++it) 
		{
			if ((*it).verticeNum > i) 
			{
				edges.push_back(Edge(i, (*it).verticeNum, (*it).weight));
			}
		}
	}
	
	std::sort(edges.begin(), edges.end(), std::greater<Edge>());		//sortowanie listy krawedzi (niemalejace wagi)

	while (result.size() != (numberOfVertices - 1)) 			//petla pobiera kolejne krawedie dopoki nie znajdzie krawedzi = liczba wierzcholkow -1
	{
		Edge currentEdge = edges.at(0);
		if (FindSet(currentEdge.startVertice) != FindSet(currentEdge.endVertice)) 
		{
			result.push_back(currentEdge);
			Union(currentEdge.startVertice, currentEdge.endVertice);
		}
		edges.erase(edges.begin());
	}

	std::cout << std::endl << "Minimalne drzewo rozpinajace dla reprezentacji listowej:" << std::endl;
	std::cout << std::endl << "Krawedz     Waga" << std::endl;
	int sum = 0;

	for (int i = 0; i < (int)result.size(); i++) 
	{
		std::cout << "(" << result.at(i).startVertice << ", " << result.at(i).endVertice << ")      " << result.at(i).weight << std::endl;
		sum += result.at(i).weight;
	}
	std::cout << std::endl << "Suma krawedzi minimalnego drzeewa rozpinajacego:" << sum << std::endl;
}

GraphList::Node::Node(int verticeNum, int weight)
{
	this->verticeNum = verticeNum;
	this->weight = weight;
}


