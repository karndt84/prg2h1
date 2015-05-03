#include "testfunktionen.h"
#include "ConsoleGraphics.h"

void testfunktion(ConsoleGraphics* consolegraphics) {
	consolegraphics->drawRectangle(10, 10, 36, 23);
	consolegraphics->drawLine(10, 10, 23, 1);
	consolegraphics->drawLine(23, 1, 36, 10);
	consolegraphics->drawLine(10, 10, 36, 23);
	consolegraphics->drawLine(36, 10, 10, 23);

	/*
	consolegraphics->drawRectangle(10, 10, 60, 50);
	consolegraphics->drawLine(10, 10, 35, 1);
	consolegraphics->drawLine(35, 1, 60, 10);
	consolegraphics->drawLine(10, 10, 60, 50);
	consolegraphics->drawLine(60, 10, 10, 50);
	*/
}