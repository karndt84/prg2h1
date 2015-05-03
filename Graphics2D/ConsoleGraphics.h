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
	void clearStatus(void);
	bool drawPoint(int x, int y);
	bool undrawPoint(int x, int y);
	bool drawLine(int x1, int y1, int x2, int y2);
	bool drawRectangle(int x1, int y1, int x2, int y2);
	bool printString(int x, int y, const char text[]);

	void printWindowSize(void); // Gibt die Gr��e des Fensters auf der Statuszeile aus


private:
	int **bitline; // Array zum abspeichern der schon gezeichneten Zeichens
	int breite, hoehe; // Breite und H�he des Fensters, letzte Zeile wird f�r status benutzt
	int lastStatusChar; // Letzte Position auf der Zeile des aktuell angezeigten Status 
private:
	enum zeichen { EMPTY, UPPER, LOWER, FULL };
	ConsoleGraphics::zeichen ConsoleGraphics::decideCode(double y1);
	bool drawPoint(int x, int y, ConsoleGraphics::zeichen z);
	bool drawPoint(int x, int y, ConsoleGraphics::zeichen z, bool override);
	void initConsole();
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	SMALL_RECT srctWindow;
	HANDLE hStdout;
	
	bool verifyCoord(int x, int y); // Fkt. zur Vermeidung des Zeichnens ausserhalb des Konsolenfensters
	void jump2Pos(int x, int y); // setzt den cursor an die stelle x,y
	void tausch(int* eins, int* zwei); // Tauscht zwei �bergebene int Variablen
	void fillGap(int x1, int y1, int x2, int y2, double m); // F�llt bei einer zu steilen Linie den Zwischenraum von x und x+1

};

#endif