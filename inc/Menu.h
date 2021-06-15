#pragma once
#include "GraphMatrix.h"
#include "GraphList.h"
#include "Clock.h"
#include "GraphGenerator.h"




class Menu {

private:
	
	GraphMatrix* matrix = nullptr;		//wskaznik na graf macierzowy
	GraphList* list = nullptr;			//wskaznik na graf listowy
	Clock clock;						//referencja do zegara
	GraphGenerator randGenerator;
	

public:
	void menuMSTProblem();				//funkcja menu
	void waitingScreen();				//kaze uzytkownikowi nacisnac przycisk
};



