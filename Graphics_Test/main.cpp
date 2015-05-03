#include "zeichencodes.h"
#include "testfunktionen.h"
#include "ConsoleGraphics.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

// Klemens Arndt, Maximilian Hoppe, Daniel Henneberg

int main(void) {

	printf("zeit das fenster zu verändern\n"); system("PAUSE"); 
	printTable();
	system("PAUSE");

	ConsoleGraphics* bla = new ConsoleGraphics; 
	bla->clear();

	/*for (int i = 0; i <= breite * hoehe; i++) {
		bla.bitline[i] = 0x21;
	}*/
	
	bla->printWindowSize();
	system("PAUSE");
	bla->clear();
	//bla->drawPoint(79, 200);
	testfunktion(bla);
	
	bla->clearStatus();
	system("PAUSE");
	bla->clearStatus();
	delete bla;

	return 0;
}