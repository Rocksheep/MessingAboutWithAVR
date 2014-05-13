#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

#include "hc595_shift.h"

void hc595_init() {
	DDRD |= (1 << PD0 | 1 << PD1 | 1 << PD2 | 1 << PD3);
	PORTD &= ~(1 << PD0 | 1 << PD1 | 1 << PD2 | 1 << PD3);
	hc595_dataHigh();
	hc595_dataRedHigh();
}

void hc595_shiftByte(uint8_t data) {
	hc595_latchLow();

	int i;
	for(i = 0; i < 8; i++) {
		if(data & 1)
			hc595_dataHigh();
		else
			hc595_dataLow();

		hc595_clk();
		data = data >> 1;
	}
	hc595_latchHigh();
}

void hc595_shiftBit(uint8_t data, uint8_t bit) {
	hc595_latchLow();

	data = data >> bit;

	if(data & 1)
		hc595_dataHigh();
	else
		hc595_dataLow();

	hc595_clk();

	hc595_latchHigh();
}

void hc595_clk() {
	PORTD |= (1 << PD3);
	PORTD &= ~(1 << PD3);
}

void hc595_dataLow() {
	PORTD &= ~(1 << PD0);
}

void hc595_dataHigh() {
	PORTD |= (1 << PD0);
}

void hc595_dataRedLow() {
	PORTD &= ~(1 << PD1);
}

void hc595_dataRedHigh() {
	PORTD |= (1 << PD1);
}

void hc595_latchLow() {
	PORTD &= ~(1 << PD2);
}

void hc595_latchHigh() {
	PORTD |= (1 << PD2);
}

