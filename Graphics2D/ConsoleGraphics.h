#ifndef CONSOLEGRAPHICS_H

#define CONSOLEGRAPHICS_H

#include <Windows.h>
#include <conio.h>



class ConsoleGraphics
{
public:
	ConsoleGraphics();
	ConsoleGraphics(int breite, int hoehe);
	~ConsoleGraphics();	
	void clear();
	bool drawPoint(int x, int y);
	bool undrawPoint(int x, int y);
	bool drawLine(int x1, int y1, int x2, int y2);
	bool drawRectangle(int x1, int y1, int x2, int y2);
	bool printString(int x, int y, const char text[]);

//private:
	int **bitline;
	int breite, hoehe;
private:
	enum zeichen { EMPTY, UPPER, LOWER, FULL };
	ConsoleGraphics::zeichen ConsoleGraphics::decideCode(double y1);
	bool drawPoint(int x, int y, ConsoleGraphics::zeichen z);
	void initConsole();
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	SMALL_RECT srctWindow;
	HANDLE hStdout;

	void jump2Pos(int x, int y);
	void tausch(int* eins, int* zwei);

};

#endif