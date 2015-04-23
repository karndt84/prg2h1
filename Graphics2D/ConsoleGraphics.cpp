#include "ConsoleGraphics.h"
#include <Windows.h>
#include <conio.h>
#include <stdio.h>

ConsoleGraphics::ConsoleGraphics()
{
	initConsole();
	bitline = new int[(breite +1) * hoehe];
	for (int i = 0; i < breite * hoehe; i++) {
		this->bitline[i] = 0x20;
	}
}

ConsoleGraphics::ConsoleGraphics(int breite, int hoehe)
{
	bitline = new int[(breite) * hoehe];
	for (int i = 0; i < breite * hoehe; i++) {
		this->bitline[i] = '0x20';
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

	this->breite = srctWindow.Right;
	this->hoehe = srctWindow.Bottom;
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