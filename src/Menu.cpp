#include "../inc/Menu.h"
#include <iostream>



void Menu::menuMSTProblem()
{
	bool running = true;
	while (running)
	 {
		
		std::cout << "1. Wygeneruj graf losowo." << std::endl;
		std::cout << "2. Wyswietl listowo i macierzowo" << std::endl;
		std::cout << "3. Algorytm Prima." << std::endl;
		std::cout << "4. Algorytm Kruskala." << std::endl;
		std::cout << "5. Zakoncz program." << std::endl;
		int choice;
		std::cin >> choice;
		switch (choice) {
		
		case 1:
		{
			if (matrix == nullptr) {
				matrix = new GraphMatrix();
				list = new GraphList();
			}
			else {
				delete matrix;
				delete list;
				matrix = new GraphMatrix();
				list = new GraphList();
			}
			std::cout << "Podaj ilosc wierzcholkow grafu:" << std::endl;
			int numberOfVertices = -1;
			std::cin >> numberOfVertices;
			std::cout << "Podaj w procentach gestosc grafu:" << std::endl;
			int densityPercentage = -1;
			std::cin >> densityPercentage;
			std::vector<Edge> edges = randGenerator.generateMST(numberOfVertices, densityPercentage);
			matrix->generateRandomMST(edges, numberOfVertices);
			list->generateRandomMST(edges, numberOfVertices);
			matrix->display();
			list->display();
			waitingScreen();
		}
		break;


		case 2:
		{
			if (list != nullptr) 
			{
				
				list->display();
				matrix->display();
				waitingScreen();
			}
			else 
			{
				
				std::cout << "Brak stworzonego grafu";
				waitingScreen();
			}
		}
		break;


		case 3:
		{
			//long tab_list[100];
			//long tab_matrix[100];
			long *tab_matrix=new long[100];
			long *tab_list=new long[100];
			long average_matrix=0;
			long average_list=0;
			
			std::cout << "Podaj ilosc wierzcholkow grafu:" << std::endl;
			int numberOfVertices = -1;
			std::cin >> numberOfVertices;
			std::cout << "Podaj w procentach gestosc grafu:" << std::endl;
			int densityPercentage = -1;
			std::cin >> densityPercentage;

			
			
		
			for(int index = 0; index<100; index++)
			{
				matrix = new GraphMatrix();
				list = new GraphList();

				std::vector<Edge> edges = randGenerator.generateMST(numberOfVertices, densityPercentage);
				matrix->generateRandomMST(edges, numberOfVertices);
				list->generateRandomMST(edges, numberOfVertices);

				clock.start();
				matrix->PrimAlgorithm();
				clock.stop();
				clock.printResult();
				tab_matrix[index]=clock.time;

				clock.start();
				list->PrimAlgorithm();
				clock.stop();
				clock.printResult();
				tab_list[index]=clock.time;	

				delete matrix;
				delete list;
			}

			for (int i = 0; i < 100; i++)
			{
				average_list=tab_list[i]+average_list;
				average_matrix=tab_matrix[i]+average_matrix;
			}


			average_matrix=average_matrix/100;
			average_list=average_list/100;


			std::cout<<std::endl<<std::endl<<"Algorytm Prima"<<std::endl;
			std::cout<<"Gęstość grafu to: "<<densityPercentage<<"%. Liczba wierzchołków to: "<<numberOfVertices<<"."<<std::endl;
			std::cout<<"Średnia algorytmu dla 100 losowych instancji grafu opartego na macierzy sąsiedztwa wyniosla "<<average_matrix<<" us."<<std::endl;
			std::cout<<"Średnia algorytmu dla 100 losowych instancji grafu opartego na liście sąsiedztwa wyniosla "<<average_list<<" us."<<std::endl<<std::endl<<std::endl;


			delete [] tab_matrix;
			delete [] tab_list;

		}
		break;

		case 4:
		{
			

			long *tab_matrix=new long[100];
			long *tab_list=new long[100];
			long average_matrix=0;
			long average_list=0;
			
			std::cout << "Podaj ilosc wierzcholkow grafu:" << std::endl;
			int numberOfVertices = -1;
			std::cin >> numberOfVertices;
			std::cout << "Podaj w procentach gestosc grafu:" << std::endl;
			int densityPercentage = -1;
			std::cin >> densityPercentage;

			
			
		
			for(int index = 0; index<100; index++)
			{
				
				matrix = new GraphMatrix();
				list = new GraphList();

				std::vector<Edge> edges = randGenerator.generateMST(numberOfVertices, densityPercentage);
				matrix->generateRandomMST(edges, numberOfVertices);
				list->generateRandomMST(edges, numberOfVertices);

				clock.start();
				matrix->KruskalAlgorithm();
				clock.stop();
				clock.printResult();
				tab_matrix[index]=clock.time;

				clock.start();
				list->KruskalAlgorithm();
				clock.stop();
				clock.printResult();
				tab_list[index]=clock.time;	
				
				delete matrix;
				delete list;
			}

			for (int i = 0; i < 100; i++)
			{
				average_list=tab_list[i]+average_list;
				average_matrix=tab_matrix[i]+average_matrix;
			}


			average_matrix=average_matrix/100;
			average_list=average_list/100;


			std::cout<<std::endl<<std::endl<<"Algorytm Kruskala"<<std::endl;
			std::cout<<"Gęstość grafu to: "<<densityPercentage<<"%. Liczba wierzchołków to: "<<numberOfVertices<<"."<<std::endl;
			std::cout<<"Średnia algorytmu dla 100 losowych instancji grafu opartego na macierzy sąsiedztwa wyniosla "<<average_matrix<<" us."<<std::endl;
			std::cout<<"Średnia algorytmu dla 100 losowych instancji grafu opartego na liście sąsiedztwa wyniosla "<<average_list<<" us."<<std::endl<<std::endl<<std::endl;


			delete [] tab_matrix;
			delete [] tab_list;

		}
		break;

		case 5:
		{
			if (matrix != nullptr) {
				delete matrix;
				delete list;
				matrix = nullptr;
				list = nullptr;
			}
			running = false;
			break;
		}

		default:
		{
			break;
		}
		}
	}
}



void Menu::waitingScreen()
{
	std::cout << std::endl << std::endl << "Nacisnij dowolony przycisk aby przejsc dalej." << std::endl << std::endl;
	int choice;
	std::cin >> choice;
}
