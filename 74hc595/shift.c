#define F_CPU 1000000

#include <avr/io.h>

typedef struct {
	uint8_t pinNumber;
	uint8_t port;
} Pin;

int main() {

	DDRB = 0xFF;
	Pin p;
	p.pinNumber = PB1;
	p.port = PORTB;

	while(1) {

	}
}
