#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include <math.h>
#include <avr/sleep.h>

void initialize();
void writeOutput();
int readInput();
void init_pwm(void);
void update_clock_speed(void);

int main()
{
	initialize(); //Set pin 5 as input and pin 4 as output
	update_clock_speed();  //adjust OSCCAL
	init_pwm();            //set up hardware PWM
	while(1){
		//Write value of pin 4 to pin 5 of c
		writeOutput(readInput());
	}
}

void update_clock_speed(void)
{
        char temp;
        temp=eeprom_read_byte((void *)1); //read oscillator offset sign
        if(temp==0||temp==1)      //if sign is invalid, don't change oscillator
        {
                if(temp==0)
                {
                        temp=eeprom_read_byte((void *)0);
                        if(temp != 0xff) OSCCAL+=temp;
                }
                else
                {
                        temp=eeprom_read_byte((void *)0);
                        if(temp!=0xff) OSCCAL -=temp;
                }
        }
}

void init_pwm(void)
{
        DDRB |= (1<<PB1);  //set OC1A as an output
        OCR1A=19999;    //set initial compare at 50%
        ICR1=39999U; // 8 MHz /40000/2 = PWM frequency = 100 Hz
        TCCR1A = (1<<COM1A1); //zeros in COM1B1,COM1B0,WGM11,WGM10
        TCCR1B = (1<<WGM13) | (1<<CS10);
}


//Set pin 5 to input and 4 from output
void initialize(){
	DDRC &= ~(1<<PC5);
	DDRC |= (1<<PC4);
}

//Read 1 or 0 from pinc5
int readInput(){
	return ((PINC & (1 << PC5)) >> PC5);
}

//Write value to pinC4
void writeOutput(int value){
	if(value == 1){
		PORTC |= (1 << PC4);
	} else {
		PORTC &= ~(1 << PC4);
	}
	return;
}
