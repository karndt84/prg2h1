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
	for (int i = 0; i < bla->breite; i++) {
		for (int i = 0; i < bla->hoehe; i++) {
			printf("%c", 0x21);
		}
	}
	system("PAUSE");

	bla->clear();

	bla->drawPoint(1, 1);
	bla->undrawPoint(1, 1);
	system("PAUSE");

	//bla.~ConsoleGraphics();
	delete bla;

	return 0;
}