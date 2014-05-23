//Transistoren Spalten[20] PB0,PB1,PB3,PB4,PB5,PB6,PB7,PC2,PC3,PC4,PC5,PC6,PC7,PD0,PD1,PD2,PD4,PD5,PD6,PD7
//Transistoren Zeilen [10] Pin15=QA,Pin1=QB,Pin2=QC,Pin3=QD,Pin4=QE,Pin5=QF,Pin6=QG,Pin7=QH,PA3,PA4
//Schieberegister: 14-PA0,11-PA1,12-PA2
//Sensor: PA5,PB2,PC0,PC1,PD3
//Taster: PA6,PA7
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//void gameover(void);   //stellt ein Bild dar, wenn das Spiel vorbei ist
void set_pixel(uint8_t,uint8_t);  //setzt ein Pixel auf dem Display, übergeben wird die x und y Position.
void clear_pixel(uint8_t,uint8_t); //das Gegenteil von set_pixel
void setup();
void shift(uint8_t x);
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
	set_pixel(0,0);
	set_pixel(1,1);
	set_pixel(10,5);
	while (1)
	{
		// erste LED = set_pixel(0,0);
	}
}


void setup()
{
	DDRD = 0b11110111; //******
	DDRB = 0b11111011; //*Output festlegen
	DDRA = 0b00011111; //******
	DDRC = 0b11111100; //******

}


void set_pixel(uint8_t x, uint8_t y)
{
PORTA  &=~ (1<<PA0);
PORTA  &=~ (1<<PA1);
PORTA  &=~ (1<<PA2);
if (spalte[x]==PB0){PORTB |= (1<<PB0);};
if (spalte[x]==PB1){PORTB |=(1<<PB1);};
if (spalte[x]==PB3){PORTB |=(1<<PB3);};
if (spalte[x]==PB4){PORTB |=(1<<PB4);};
if (spalte[x]==PB5){PORTB |=(1<<PB5);};
if (spalte[x]==PB6){PORTB |=(1<<PB6);};
if (spalte[x]==PB7){PORTB |=(1<<PB7);};
if (spalte[x]==PC2){PORTC |=(1<<PC2);};
if (spalte[x]==PC3){PORTC |=(1<<PC3);};						//PORTA |= (1<<PA0);		//Serial In: 1 oder 0							
if (spalte[x]==PC4){PORTC |=(1<<PC4);};						//PORTA |= (1<<PA1);		//shift, Serial in als neuer Bit0 Wert
if (spalte[x]==PC5){PORTC |=(1<<PC5);};						//PORTA |= (1<<PA2);		//Inhalt Schieberegister in Ausgangsregister
if (spalte[x]==PC6){PORTC |=(1<<PC6);};			//Schieberegister: 14-PA0,11-PA1,12-PA2
if (spalte[x]==PC7){PORTC |=(1<<PC7);};			//Transistoren Zeilen [10] Pin15=QA,Pin1=QB,Pin2=QC,Pin3=QD,Pin4=QE,Pin5=QF,Pin6=QG,Pin7=QH,PA3,PA4
if (spalte[x]==PD0){PORTD |=(1<<PD0);};
if (spalte[x]==PD1){PORTD |=(1<<PD1);};			//volatile uint8_t zeile[10] = { 15, 1, 2, 3, 4, 5, 6, 7, PA3, PA4 };//Displayzeilen als Array. Zahlen stellen Pins dar.
if (spalte[x]==PD2){PORTD |=(1<<PD2);};
if (spalte[x]==PD4){PORTD |=(1<<PD4);};
if (spalte[x]==PD5){PORTD |=(1<<PD5);};
if (spalte[x]==PD6){PORTD |=(1<<PD6);};
if (spalte[x]==PD7){PORTD |=(1<<PD7);};
if (zeile[y]==PA3){PORTA |= (1<<PA3);};
if (zeile[y]==PA4){PORTA |= (1<<PA4);};	
if (zeile[y]==7){shift(7);};
if (zeile[y]==6){shift(6);}
if (zeile[y]==5){shift(5);}
if (zeile[y]==4){shift(4);}
if (zeile[y]==3){shift(3);}
if (zeile[y]==2){shift(2);}
if (zeile[y]==1){shift(1);}
if (zeile[y]==15){shift(0);}
}

void shift(uint8_t x)
{
		PORTA |= (1<<PA0);			//Serial In: 1 oder 0	
		PORTA |= (1<<PA1);			//shift, Serial in als neuer Bit0 Wert
		for (uint8_t i=0;i<x;i++)	//x=Anzahl Shifts
		{
			PORTA |= (0<<PA0);		//Serial In: 0
			PORTA |= (1<<PA1);		// shift
		}
		PORTA |= (1<<PA2);			//Inhalt Schieberegister in Ausgangsregister
}