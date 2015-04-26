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
	COORD coordDest = { x, y };
	SetConsoleCursorPosition(this->hStdout, coordDest);
	printf("%c", 0xdb);
	return 0;
}
bool ConsoleGraphics::undrawPoint(int x, int y) {
	COORD coordDest = { x, y };
	SetConsoleCursorPosition(this->hStdout, coordDest);
	printf("%c", 0x20);
	return 0;
}
bool ConsoleGraphics::drawLine(int x1, int y1, int x2, int y2) {
	return 0;
}
bool ConsoleGraphics::drawRectangle(int x1, int y1, int x2, int y2) {
	return 0;
}
bool ConsoleGraphics::printString(int x, int y, const char text[]) {
	return 0;
}