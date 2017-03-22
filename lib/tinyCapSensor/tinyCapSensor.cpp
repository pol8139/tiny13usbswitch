#include "Arduino.h"
#include "tinyCapSensor.h"

long tinyCapSensor(int send, int receive) {
	DDRB |= _BV(send);
	DDRB &= ~_BV(receive);
	PORTB &= ~(_BV(send) | _BV(receive));

	long sensed_total = 0;
	int i;
	for(i = 0; i < SIMPLELOWPASS; i++) {
		delay(1);
		PORTB |= _BV(send);
		long sensed_value = 0;
		while((!(PINB & _BV(receive))) && (sensed_value < TIMEOUT)) {
			sensed_value++;
		}
		if(sensed_value >= TIMEOUT) {
			return 1;
		}
		PORTB &= ~_BV(send);
		sensed_total += sensed_value;
	}
	return sensed_total / SIMPLELOWPASS;
}
