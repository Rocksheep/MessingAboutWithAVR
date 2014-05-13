#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>

//#include "hc595_shift.h"
#include "atoh.h"

uint8_t chars [][5] = {
	{0x7C, 0x90, 0X90, 0x90, 0x7C}, //A
	{0xFC, 0xA4, 0xA4, 0xA4, 0x58}, //B
	{0x78, 0x84, 0x84, 0x84, 0x84}, //C
	{0xFC, 0x84, 0x84, 0x84, 0x78}, //D
	{0xFC, 0xA4, 0xA4, 0xA4, 0x84}, //E
	{0xFC, 0xA0, 0xA0, 0xA0, 0x80}, //F
	{0x7C, 0x84, 0x84, 0x94, 0x9C}, //G
	{0xFC, 0x20, 0x20, 0x20, 0xFC}, //H
	{0x00, 0x84, 0xFC, 0x84, 0x00}, //I
	{0x08, 0x84, 0x84, 0xF8, 0x00}, //J
	{0xFC, 0x30, 0x48, 0x84, 0x00}, //K
	{0xFC, 0x04, 0x04, 0x04, 0x04}, //L
	{0xFC, 0x40, 0x20, 0x40, 0xFC}, //M
	{0xFC, 0x40, 0x30, 0x08, 0xFC}, //N
	{0x78, 0x84, 0x84, 0x84, 0x78}, //O
	{0xFC, 0xA0, 0xA0, 0xA0, 0x40}, //P
	{0x40, 0xA0, 0xA0, 0xA0, 0xFC}, //Q
	{0xFC, 0xA0, 0xA0, 0xB0, 0x4C}, //R
	{0x48, 0xA4, 0xA4, 0xA4, 0x18}, //S
	{0x80, 0x80, 0xFC, 0x80, 0x80}, //T
	{0xF8, 0x04, 0x04, 0x04, 0xF8}, //U
	{0xC0, 0x30, 0x0C, 0x30, 0xC0}, //V
	{0xFC, 0x08, 0x10, 0x08, 0xFC}, //W
	{0x84, 0x48, 0x30, 0x48, 0x84}, //X
	{0x80, 0x40, 0x3C, 0x40, 0x80}, //Y
	{0x84, 0x8C, 0x94, 0xA4, 0xC4}  //Z
};

uint8_t text[] = {
	0x84, 0xA4, 0xA4, 0xA4, 0xFC, //E [rev]
	0x00, 0xF4, 0x00, 0x00, //!
	0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, //space
	0x00,
	0x80, 0x80, 0xFC, 0x80, 0x80, //T
	0x00,
	0x00, 0x84, 0xFC, 0x84, 0x00, //I
	0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, //space
	0x00,
	0xFC, 0x84, 0x84, 0x84, 0x78, //D
	0x00,
	0xFC, 0xA4, 0xA4, 0xA4, 0x84, //E
	0x00,
	0xFC, 0x04, 0x04, 0x04, 0x04, //L
	0x00,
	0xFC, 0xA0, 0xA0, 0xA0, 0x80, //F
	0x00,
	0x80, 0x80, 0xFC, 0x80, 0x80, //T
	0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, //space
	0x00,
	0x84, 0xA4, 0xA4, 0xA4, 0xFC, //E [rev]
	0x00, 0xF4, 0x00, 0x00, //!
	0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, //space
	0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, //space
	0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, //space
	0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, //space
	0x00,
	0xFC, 0x20, 0x20, 0x20, 0xFC, //H
	0x00,
	0x7C, 0x90, 0X90, 0x90, 0x7C, //A
	0x00,
	0x78, 0x84, 0x84, 0x84, 0x84, //C
	0x00,
	0xFC, 0x30, 0x48, 0x84, 0x00, //K
	0x00,
	0xFC, 0xA4, 0xA4, 0xA4, 0x84, //E
	0x00,
	0xFC, 0x40, 0x30, 0x08, 0xFC, //N
	0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, //space
	0x00,
	0x00, 0x84, 0xFC, 0x84, 0x00, //I
	0x00,
	0x48, 0xA4, 0xA4, 0xA4, 0x18, //S
	0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, //space
	0x00,
	0x78, 0x84, 0x84, 0x84, 0x84, //C
	0x00,
	0x78, 0x84, 0x84, 0x84, 0x78, //O
	0x00,
	0x78, 0x84, 0x84, 0x84, 0x78, //O
	0x00,
	0xFC, 0x04, 0x04, 0x04, 0x04, //L
	0x00,
	0x00, 0x00, 0xF4, 0x00, 0x00, //!

	/*0xFC, 0xA0, 0xA0, 0xB0, 0x4C, //R*/
	/*0x00,*/
	/*0xFC, 0xA4, 0xA4, 0xA4, 0x84, //E*/
	/*0x00,*/
	/*0xC0, 0x30, 0x0C, 0X30, 0xC0, //V*/
	/*0x00,*/
	/*0x48, 0xA4, 0xA4, 0xA4, 0x18, //S*/
	/*0x00,*/
	/*0xFC, 0xA0, 0xA0, 0xA0, 0x40, //P*/
	/*0x00,*/
	/*0x7C, 0x90, 0X90, 0x90, 0x7C, //A*/
	/*0x00,*/
	/*0x78, 0x84, 0x84, 0x84, 0x84, //C*/
	/*0x00,*/
	/*0xFC, 0xA4, 0xA4, 0xA4, 0x84 //E*/
};

volatile int16_t shiftIn = 0;

ISR(TIMER1_OVF_vect) {
	static int counter = 0;
	if(counter >= 3) {
		counter = 0;
		shiftIn += 1;
	}
	counter += 1;
}

void initTimer0();


int main() {

	hc595_init();
	initTimer0();

	int8_t shiftCounter = 0x00;

	int16_t curShift, curMaxShift;
	int16_t charCol, row;
	int16_t col;
	//revspace: 47 cols
	uint8_t textLength = 190;//77 + 113+;//198;

	//test length
	// strlen(s) * 6

	//all output
	DDRD = 0xFF;
	DDRA = 0xFF;

	char text[] = "nee";
	textLength = strlen(text);//10 * 5 + 9;
	int8_t j, i;

	while(1) {
		if(shiftIn > 80 + textLength)
			shiftIn = 0;
		curMaxShift = shiftIn;

		//scan the rows
		for(row = 7; row > 0; row--) {
			charCol = textLength; //word length
			PORTA = row;

			hc595_latchLow();
			// all the columns + the length of the text
			for(col = 80 + textLength; col >= 0; ){
				if(80 + textLength - curMaxShift > col && charCol >= 0) {
					for(i = strlen(text) - 1; i >= 0; i--) {
						for(j = 4; j >= 0; j--) {
							if(~chars[text[i] - 'a'][j] & (1 << row)) {
								hc595_dataHigh();
							}
							else {
								hc595_dataLow();
							}
							charCol--;
							hc595_clk();
						}
						hc595_dataHigh();
						hc595_clk();
					}
				}
				else {
					hc595_dataHigh();
				}
				col--;
				hc595_clk();
			}
				
			
			hc595_latchHigh();

			// hc595_latchLow();
			// for(col = 80 + textLength; col >= 0; col--){
			// 	if( textLength + 80 - curMaxShift > col && charCol >= 0) {
			// 		if(~text[charCol] & (1 << row))
			// 			hc595_dataHigh();
			// 		else
			// 			hc595_dataLow();
			// 		// [>if(~orange[charCol] & (1 << row))<]
			// 			// [>hc595_dataRedHigh();<]
			// 		// [>else<]
			// 			// [>hc595_dataRedLow();<]
			// 		charCol -= 1;
			// 	}
			// 	else {
			// 		hc595_dataHigh();
			// 	}
			// 	hc595_clk();
			// }
			// hc595_latchHigh();
		}
	}

}

void initTimer0() {
	//set the prescaler to 1
	TCCR1B |= (1 << CS10);

	//enable timer1 overflow
	TIMSK |= (1 << TOIE1);

	sei();
}

