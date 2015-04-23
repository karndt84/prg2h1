#include "zeichencodes.h"
#include <stdio.h>

void printTable(void) {
	const int nColumns = 0xF; // Spaltenanzahl
	// Kopfzeile
	printf("\n     | ");
	for (int i = 0x0; i <= nColumns; i++) {
		printf("%x ", i);
	}
	// Trennzeile
	printf("\n-----+");
	for (int i = 0x0; i <= nColumns; i++) {
		printf("--", i);
	}
	printf("\n");
	// Tabelle
	for (int i = 0x20; i <= 0xFE; i += nColumns +1) {
		printf("0x%x | ", i);
		for (int z = 0x0; z <= nColumns; z++) {
			printf("%c ", i + z);

		}
		printf("\n");
	}
	printf("\n\n");
}