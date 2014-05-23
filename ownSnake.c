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
//zeile schieberegister
//zukünftige Funktionen
//void gameover(void);   //stellt ein Bild dar, wenn das Spiel vorbei ist
void set_pixel(uint8_t,uint8_t);  //setzt ein Pixel auf dem Display, übergeben wird die x und y Position.
void clear_pixel(uint8_t,uint8_t); //das Gegenteil von set_pixel
void setup();
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
	int x = 0;
	int y = 0;

		for (x=0;x<10;x++)		//Spalten
		{
			set_pixel(x,y);
			x = x + 2;
			for (x=0;x<10;x++)  //Zeilen
			{
				set_pixel(x,y);
				y++;
			}
		}
	_delay_ms(5000);
		
	while (1)
	{
	}
}


void setup()
{
	DDRD = 0b11110111; //******
	DDRB = 0b11111011; //*Output festlegen
	DDRA = 0b00011000; //******
	DDRC = 0b11111100; //******
}


void set_pixel(uint8_t x, uint8_t y)
{
	spalte[x] |= (1 << y); 
}

void clear_pixel(uint8_t x,uint8_t y)
{
	spalte[x]&=~(1<<y); 
}