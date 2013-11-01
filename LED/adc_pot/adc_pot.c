#define F_CPU 1000000

#include <avr/interrupt.h>
#include <avr/io.h>

ISR(ADC_vect) {
	uint8_t data = ADCH;
	PORTB = ~(data);
	ADCSRA |= (1 << ADSC);
}

int main(void) {

	//configure the ADC
	//Enable interrupts function in ADC
	//8-bit or 10-bit results
	DDRB = 0xFF;

	//Turn on ADC
	ADCSRA |= (1 << ADPS2);
	ADMUX |= (1 << ADLAR);
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1 << ADIE);
	ADCSRA |= (1 << ADEN);

	sei();

	ADCSRA |= (1 << ADSC);

	while(1) {

	}
}
