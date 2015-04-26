#include "ConsoleGraphics.h"
#include <Windows.h>
#include <conio.h>
#include <stdio.h>

ConsoleGraphics::ConsoleGraphics()
{
	initConsole();
	bitline = new int*[breite]; // Erstes Array initialisieren

	for (int i = 0; i < breite; i++)
	{
		bitline[i] = new int[hoehe]; // Für jedes Arrayfeld des ersten, ein weiteres Array initialisieren
		for (int j = 0; j < hoehe; j++) {
			this->bitline[i][j] = '0x20';
		}
	}
}

ConsoleGraphics::ConsoleGraphics(int breite, int hoehe)
{
	/*bitline = new int[(breite) * hoehe];
	for (int i = 0; i < breite * hoehe; i++) {
		this->bitline[i] = '0x20';
	}
	*/
	bitline = new int*[breite]; // Erstes Array initialisieren

	for (int i = 0; i < breite; i++)
	{
		bitline[i] = new int[hoehe]; // Für jedes Arrayfeld des ersten, ein weiteres Array initialisieren
	}
}


ConsoleGraphics::~ConsoleGraphics()
{
	delete[] this->bitline;
}

void ConsoleGraphics::initConsole() {
	
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
	{
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
	}

	srctWindow = csbiInfo.srWindow;
	
	this->breite = srctWindow.Right +1;
	this->hoehe = srctWindow.Bottom +1;
}

void ConsoleGraphics::clear() {
	jump2Pos(0, 0);
	for (int i = 0; i < (this->breite + 1) * this->hoehe; i++) {
		printf("%c", 0x20);
	}
	jump2Pos(0, 0);
}

void ConsoleGraphics::jump2Pos(int x, int y) {
	
	COORD coordDest;
	coordDest.X = x;
	coordDest.Y = y;
	SetConsoleCursorPosition(this->hStdout, coordDest);

}

bool ConsoleGraphics::drawPoint(int x, int y) {
	drawPoint(x, y, FULL);
	return 0;
}

bool ConsoleGraphics::drawPoint(int x, int y, ConsoleGraphics::zeichen z) {
	int code = 0x20;
	jump2Pos(x, y);
	switch (z) {
		case EMPTY: code = 0x20; break;
		case UPPER: code = 0xdf; break;
		case LOWER: code = 0xdc; break;
		case FULL: code = 0xdb; break;
		DEFAULT: code = 0x20; break;
	}
	printf("%c", code);
	return 0;
}

ConsoleGraphics::zeichen ConsoleGraphics::decideCode(double y1) {
	double var = y1 - 0.5;
	var = y1 - (int)var;
 	if (y1 < 1.4) {
		return UPPER;
	} else if (y1 > 1.6) {
		return LOWER;
	} else {
		return FULL;
	}
}

bool ConsoleGraphics::undrawPoint(int x, int y) {
	drawPoint(x, y, EMPTY);
	return 0;
}

void ConsoleGraphics::tausch(int* eins, int* zwei) {
	int tausch;
	tausch = *eins;
	*zwei = *eins;
	*eins = tausch;
}

bool ConsoleGraphics::drawLine(int x1, int y1, int x2, int y2) {
	double targetY;
	(x1 > x2) ? tausch(&x1, &x2) : false;
	(y1 > y2) ? tausch(&y1, &y2) : false;

	double m = ((double)y2 - (double)y1) / ((double)x2 - (double)x1);
	for (double i = x1; i <= x2; i++) {
		targetY = (m * (i - (double)x1) + (double)y1);
		drawPoint(i, (int)targetY , decideCode(targetY));
	}


	return 0;
}
bool ConsoleGraphics::drawRectangle(int x1, int y1, int x2, int y2) {
	return 0;
}
bool ConsoleGraphics::printString(int x, int y, const char text[]) {
	return 0;
}