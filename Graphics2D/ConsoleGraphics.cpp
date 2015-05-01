#include "ConsoleGraphics.h"
#include <Windows.h>
#include <conio.h>
#include <stdio.h>

ConsoleGraphics::ConsoleGraphics()
{
	initConsole();
	this->lastStatusChar = 0;
	bitline = new int*[breite]; // Erstes Array initialisieren

	for (int i = 0; i < breite; i++)
	{
		bitline[i] = new int[hoehe]; // F�r jedes Arrayfeld des ersten, ein weiteres Array initialisieren
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
		bitline[i] = new int[hoehe]; // F�r jedes Arrayfeld des ersten, ein weiteres Array initialisieren
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
	clearStatus();
	jump2Pos(this->lastStatusChar, this->hoehe);
}

void ConsoleGraphics::clearStatus() {
	jump2Pos(this->lastStatusChar, this->hoehe);
	for (int i = this->lastStatusChar; i < this->breite; i++) { // �brig gebliebene Zeichen auf der Statuszeile entfernen.
		drawPoint(i, this->hoehe, ConsoleGraphics::EMPTY);
	}
}

void ConsoleGraphics::printWindowSize(void) {
	jump2Pos(0, this->hoehe);
	printf("Fenstergroesse: %ix%i", this->breite, this->hoehe);
	GetConsoleScreenBufferInfo(hStdout, &csbiInfo); // aktuellen status holen
	this->lastStatusChar = this->csbiInfo.dwCursorPosition.X; 

}

void ConsoleGraphics::jump2Pos(int x, int y) {
	
	COORD coordDest;
	coordDest.X = x;
	coordDest.Y = y;
	SetConsoleCursorPosition(this->hStdout, coordDest);

}

bool ConsoleGraphics::verifyCoord(int x, int y) {
	
	if (this->breite < x || this->hoehe - 1 < y) {
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
	for (int x = 0; x <= x2 - x1; ++x)
	{
		int yOben = y1 + x * m;
		int yUnten;
		if (x > 0) { // alle weiteren pixel
			yUnten = y1 + (x - 1) * m;
			if (yUnten < yOben)
				yUnten += 1;
		} else // erster pixel
			yUnten = y1;

		if (m > 0) {
			for (int y = yUnten; y <= yOben; ++y) {
				drawPoint(x1 + x, y);
			}
		} else {
			for (int y = yUnten; y >= yOben; --y) {
				drawPoint(x1 + x, y);
			}
		}
		
	}
}

bool ConsoleGraphics::drawLine(int x1, int y1, int x2, int y2) {
	if (!verifyCoord(x1, y1)) { return false; }
	if (!verifyCoord(x2, y2)) { return false; }

	if (x1 > x2) {
		tausch(&x1, &x2);
		tausch(&y1, &y2);
	}

	if (x1 == x2) {	// Horizontale Linie
		if (y1 > y2) // immer von unten nach oben laufen
			tausch(&y1, &y2);
		for (int y = y1; y <= y2; ++y) {
			drawPoint(x1, y);
		}
	} else {
		double m = ((double)y2 - (double)y1) / ((double)x2 - (double)x1);
		fillGap(x1, y1, x2, y2, m);
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