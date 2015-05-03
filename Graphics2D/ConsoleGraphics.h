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
	// leert die Konsole
	void clear();
	// löscht die Zeichen nach dem letzten status
	void clearStatus(void);
	// zeichnet einen vollen Punkt
	bool drawPoint(int x, int y);
	// leert einen Punkt
	bool undrawPoint(int x, int y);
	// zeichnet eine Linie zwischen zwei Punkten
	bool drawLine(int x1, int y1, int x2, int y2);
	// zeichnet ein Rechteck, ober linke und untere rechte ecke werden übergeben
	bool drawRectangle(int x1, int y1, int x2, int y2);
	// schreibt einen string an die angegebene Position
	bool printString(int x, int y, const char text[]);
	// Gibt die Größe des Fensters auf der Statuszeile aus
	void printWindowSize(void); 


private:
	int **bitline; // Array zum abspeichern der schon gezeichneten Zeichens
	int breite, hoehe; // Breite und Höhe des Fensters, letzte Zeile wird für status benutzt
	int lastStatusChar; // Letzte Position auf der Zeile des aktuell angezeigten Status 
	
	enum zeichen { EMPTY, UPPER, LOWER, FULL }; // code für ausgabezeichen

	// gibt einen zeichencode zurück, je nachdem wo der punkt liegt
	ConsoleGraphics::zeichen ConsoleGraphics::decideCode(double y1);
	// zeichnet einen punkt, zusätzlich kann das zu zeichnende Symbol angegeben werden
	bool drawPoint(int x, int y, ConsoleGraphics::zeichen z);
	// zeichnet einen punkt, zusätzlich kann das zu zeichnende Symbol angegeben werden und die Überprüfung der Koordinaten übergangen werden
	bool drawPoint(int x, int y, ConsoleGraphics::zeichen z, bool override);
	// initialisiert die Konsolen-Werte des Objektes + den HANDLE
	void initConsole();
	// initialisiert das Array des Bildes
	void initArray();
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; // konsoleninfo
	SMALL_RECT srctWindow; // fenstergröße
	HANDLE hStdout; // Konsolen-handle
	// Fkt. zur Vermeidung des Zeichnens ausserhalb des Konsolenfensters
	bool verifyCoord(int x, int y);
	// setzt den cursor an die stelle x,y
	void jump2Pos(int x, int y);
	// Tauscht zwei übergebene int Variablen
	void tausch(int* eins, int* zwei);
	// Füllt bei einer zu steilen Linie den Zwischenraum von x und x+1
	void fillGap(int x1, int y1, int x2, int y2, double m);
	// akualisiert den laststatusChar mit aktueller x position
	void ConsoleGraphics::updateLaststatusPosition(void);

};

#endif