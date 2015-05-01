#include "zeichencodes.h"
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

	//CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	//SMALL_RECT srctWindow;

	/* hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
	{
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
		return 0;
	}

	srctWindow = csbiInfo.srWindow;

	printf("%i %i %i %i", srctWindow.Top, srctWindow.Bottom , srctWindow.Left, srctWindow.Right);
	*/

	//ConsoleGraphics bla = ConsoleGraphics::ConsoleGraphics(breite, hoehe);

	ConsoleGraphics* bla = new ConsoleGraphics; 
	bla->clear();

	/*for (int i = 0; i <= breite * hoehe; i++) {
		bla.bitline[i] = 0x21;
	}*/
	
	bla->printWindowSize();
	system("PAUSE");
	bla->clearStatus();
	bla->clear();
	//bla->drawLine(2, 2, 70, 10);
	//bla->drawLine(0, 0, 0, 3);
	//la->drawLine(0, 0, 3, 0);
	bla->drawLine(2, 23 , 8, 0);

	//bool error = bla->drawLine(2, 2, 79, 4);
	//error = bla->printString(77, 5, "test");

	system("PAUSE");
	bla->clearStatus();
	//bla.~ConsoleGraphics();
	delete bla;

	return 0;
}