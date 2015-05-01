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
			this->bitline[i][j] = 0x20;
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
	
	this->breite = srctWindow.Right ;
	this->hoehe = srctWindow.Bottom ;
}

void ConsoleGraphics::clear() {
	jump2Pos(0, 0);
	for (int i = 0; i <= this->breite; i++) {
		for (int i2 = 0; i2 <= this->hoehe -1; i2++) {
			printf("%c", 0x20);
		}
	}
	jump2Pos(0, 0);
}

void ConsoleGraphics::jump2Pos(int x, int y) {
	
	COORD coordDest;
	coordDest.X = x;
	coordDest.Y = y;
	SetConsoleCursorPosition(this->hStdout, coordDest);

}

bool ConsoleGraphics::verifyCoord(int x, int y) {
	
	if (this->breite < x || this->hoehe < y) {
		jump2Pos(0, this->hoehe);
		printf("Error: coords %i,%i out of borders\t", x, y);
		return false;
	}
	
	return true;
}

bool ConsoleGraphics::drawPoint(int x, int y) {
	if (!verifyCoord(x, y)) {	return false;	}
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
	}
	printf("%c", code);
	return 0;
}

ConsoleGraphics::zeichen ConsoleGraphics::decideCode(double y1) {
	double var = y1 - 0.5;
	var = y1 - (int)var;
 	if (var < 1.0) {
		return LOWER;
	} else if (var > 1.0) {
		return UPPER;
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

void ConsoleGraphics::fillGap(int x1, int y1, int x2, int y2, double m) {
	bool aufwaerts;
	int targetX, x;
	if (m > 0)
		aufwaerts = true;
	else
		aufwaerts = false;

	int actY = y1;
	m = ((double)y2 - (double)y1) / ((double)x2 - (double)x1);
	m = m * 2;
	while (!(actY == y2+1)) {
		x =  x1+ ((double)actY / m);
		drawPoint(x, actY);

		if (aufwaerts)
			actY++;
		else
			actY--;
	}
	
}

bool ConsoleGraphics::drawLine(int x1, int y1, int x2, int y2) {
	if (!verifyCoord(x1, y1)) { return false; }
	if (!verifyCoord(x2, y2)) { return false; }
	double targetY, prevY = y1;
	if (x1 > x2) {
		tausch(&x1, &x2);
		tausch(&y1, &y2);
	}
	bool gap;
	int vergleich;
	double m = ((double)y2 - (double)y1) / ((double)x2 - (double)x1);
	for (double i = x1; i <= x2; i++) { // x werte durchgehen und den y wert zeichnen
		targetY = (m * (i - (double)x1) + (double)y1);
		
		if (m > 1 || m < -1) {
			gap = true;
		}
		else {
			gap = false;
		}
		if (gap)
			fillGap(i - 1, prevY, i, targetY, m);
		else
			drawPoint(i, (int)targetY , decideCode(targetY));

		//drawPoint(i, (int)targetY);
		prevY = targetY;
	}


	return true;
}
bool ConsoleGraphics::drawRectangle(int x1, int y1, int x2, int y2) {
	if (!verifyCoord(x1, y1)) { return false; }
	if (!verifyCoord(x2, y2)) { return false; }

	return true;
}
bool ConsoleGraphics::printString(int x, int y, const char text[]) {
	if (!verifyCoord(x + strlen(text), y)) { return false; }
	jump2Pos(x, y);
	printf("%s", text);

	return true;
}