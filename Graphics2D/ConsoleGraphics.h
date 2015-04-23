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

//private:
	int **bitline;
	int breite, hoehe;
private:
	void initConsole();
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	SMALL_RECT srctWindow;
	HANDLE hStdout;

	void jump2Pos(int x, int y);

};

#endif