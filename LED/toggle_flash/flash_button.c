//the speed of the cpu (not required but I like it here ;D)
#define F_CPU 1000000

#include <avr/interrupt.h>
#include <avr/io.h>

ISR(TIMER0_OVF_vect) {
	//set these variables static so they stay in here and won't change
	//this way we won't need global variables
	static uint8_t prevState = 0x00;
	static uint8_t activeState = 0x00;

	//check if the button is still pressed (debounce)
	if(prevState != PINA) {
		//put the changes in active state
		activeState ^= ~PINA;

		//Put the inverted into the PORT so the lights will be off when not
		//chosen for blinking
		PORTB = ~activeState;
	}

	//store PINA in the previous state
	prevState = PINA;

	//toggle the LEDs
	PORTB ^= (activeState);
}

void main() {

	//set the prescaler to 1024
	TCCR0 |= (1 << CS02) | (1 << CS00);

	//enable fast PWM
	TCCR0 |= (1 << WGM01) | (1 << WGM00);

	//enable timer0 overflow
	TIMSK |= (1 << TOIE0);

	//enable interrupts
	sei();

	//set register B to output
	DDRB = 0xFF;

	//set register A to input
	DDRA = 0x00;

	PORTB = 0xFF;

	while(1) {}

}
