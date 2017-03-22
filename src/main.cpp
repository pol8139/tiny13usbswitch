#include "Arduino.h"
#include "BasicSerial3.h"
#include "tinyCapSensor.h"
#include <stdlib.h>

#define TOUCHSEND 0
#define TOUCHRECEIVE 1
#define OUT1 2
#define OUT2 4

int state[2] = {};
int touch_thresh = 100;
int touch_in = 0;
int out = 0;

void serOut(const char* str) {
	while (*str) TxByte (*str++);
}

void setup() {
	pinMode(OUT1, OUTPUT);
	pinMode(OUT2, OUTPUT);
	digitalWrite(OUT1, out);
	digitalWrite(OUT2, out ^ 1);
}

void loop() {
	touch_in = tinyCapSensor(TOUCHSEND, TOUCHRECEIVE);
	char s[16];
	itoa(touch_in, s, 10);
	serOut(s);
	state[0] = state[1];
	if(touch_in > touch_thresh) {
		state[1] = 1;
	} else {
		state[1] = 0;
	}
	if(state[0] == 0 && state[1] == 1) {
		out ^= 1;
		digitalWrite(OUT1, 0);
		digitalWrite(OUT2, 0);
		digitalWrite(OUT1, out);
		digitalWrite(OUT2, out ^ 1);
	}
	serOut("\r\n");
	delay(2);
}
