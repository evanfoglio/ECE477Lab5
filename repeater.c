#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include <math.h>
#include <avr/sleep.h>


void initialize();
void writeOutput();
int readInput();

int main(){
	initialize();
	while(1)
		writeOutput(readInput());


}

void initialize(){
	DDRC &= ~(1<<PC5);
	DDRC |= ~(1<<PC5);
}
int readInput(){
	return (PINC & (1 << PC5) >> PC5);
}

void writeOutput(int value){
	PORTB |= (value << PC4);
	PORTB &= (value << PC4);
	return;
}
