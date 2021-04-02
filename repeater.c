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
	//Set pin 4 to output and pin 5 to input
	initialize();
	while(1)
		//WRite whatever the value is being read from pin 5 into port 4
		writeOutput(readInput());


}

void initialize(){
	DDRC &= ~(1<<PC5);
	DDRC |= (1<<PC5);
}
int readInput(){
	return ((PINC & (1 << PC5)) >> PC5);
}

void writeOutput(int value){
	if(value == 1){
		PORTB |= (1 << PC4);
	} else {
		PORTB &= ~(1 << PC4);
	}
	return;
}
