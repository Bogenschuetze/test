/*
 * ownSnake.c
 *
 * Created: 23.05.2014 08:27:26
 *  Author: Meyerr
 */ 

//LED-Matrix mit Beschleunigungssensor


//Transistoren Spalten[20] PB0,PB1,PB3,PB4,PB5,PB6,PB7,PC2,PC3,PC4,PC5,PC6,PC7,PD0,PD1,PD2,PD4,PD5,PD6,PD7
//Transistoren Zeilen [10] Pin15=QA,Pin1=QB,Pin2=QC,Pin3=QD,Pin4=QE,Pin5=QF,Pin6=QG,Pin7=QH,PA3,PA4
//Schieberegister: 14-PA0,11-PA1,12-PA2
//Sensor: PA5,PB2,PC0,PC1,PD3
//Taster: PA6,PA7



#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//zukünftige Funktionen
//void gameover(void);   //stellt ein Bild dar, wenn das Spiel vorbei ist
//void set_pixel(uint8_t,uint8_t);  //setzt ein Pixel auf dem Display, übergeben wird die x und y Position.
//void clear_pixel(uint8_t,uint8_t); //das Gegenteil von set_pixel
//void clear_display(void); //Löscht das Display
//uint8_t getkay(void);//Fragt die Tasten ab
//void shift(void); //schiebt die Schlange eine Stelle weiter
//uint8_t check_if_point_on_snake(uint8_t,uint8_t,uint8_t); //Wenn die übergebenen Koordinate auf der Schlange liegt wird eine 1 zurückgegeben
//void set_point(void); //setzt einen neuen Fangpunkt

// Spalten und Zeilen Anzahl definieren
const int spalten_anzahl = 10;
const int zeilen_anzahl = 10;
volatile uint8_t spalte[20] = { PB0, PB1, PB3, PB4, PB5, PB6, PB7, PC2, PC3, PC4, PC5, PC6, PC7, PD0, PD1, PD2, PD4, PD5, PD6, PD7 };//Displayspalten definieren als Array
volatile uint8_t zeile[10] = { 15, 1, 2, 3, 4, 5, 6, 7, PA3, PA4 };//Displayzeilen als Array. Zahlen stellen Pins dar.
int main (void)
{
	setup();
	loop();
}


void setup()
{
	int r = 0;
	int c = 0;
	// Zeilen initialisieren
	for (int i = 0; i < zeilen_anzahl; i++)
	{
		pinMode(spalte[1+r], OUTPUT);
		digitalWrite(spalte[1 + r], LOW);
		r = r + 2;
	}

	// Spalten initialisieren
	for (int i = 0; i < spalten_anzahl; i++)
	{
		pinMode(zeile[1+c], OUTPUT);
		digitalWrite(zeile[1+c], LOW);
		c = c + 1;
	}
}
void loop()
{
	// Bild anzeigen , alle LEDS leuchten.
	for (int i = 0; i < 500; i++)					// Imitieren einer "Endlos" Schleife
	{
		// für alle Zeilen
		for (int r = 0; r < zeilen_anzahl; r++)
		{
			// Zeile einschalten
			int c = 0;
			digitalWrite(zeile[1+c], HIGH);
			c++;
			// alle Spalten der Zeile einschalten
			for (int c = 0; c < spalten_anzahl; c++)            
			{   
				int r = 0;
				digitalWrite(spalte[1+r], HIGH);
				r = r + 2;
				else
					digitalWrite(spalte[1+r], LOW);
					r = r + 2;
			}

			// für alle Spalten
			for (int c = 0; c < spalten_anzahl; c++)
			{
				// Spalte ausschalten
				int r = 0;
				digitalWrite(spalte[1 + r], LOW);
				r = r + 2;
			}

			// alle Zeilen der Spalte ausschalten
			c = 0;
			digitalWrite(zeile[1 + c], LOW);
			c++;
		}
	}
}

//void set_pixel(uint8_t x, uint8_t y)
//{
	//spalte[x] |= (1 << y); // PORTD |= (1<<PD7);
//}

//void clear_pixel(uint8_t x,uint8_t y)
//{
//spalte[x]&=~(1<<y); // PORTD &= ~(1<<PD7)
//}