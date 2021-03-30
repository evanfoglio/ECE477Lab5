#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <unistd.h>
void gpioInit();

void millisleep();

int main(int argc, char*argv[])
{
	int pin = 0;//pin 11
	double hz = 0;
	double time_high = 0;
	double time_low = 0;
	double hz_data[1000] = {0};
	double average;
	int num_cycle = 0;
	int gpioOut = 2;//pin 13
	//Sets up wiring Pi
	gpioInit();
	
	while(1){	
			time_high = 0;
			time_low = 0;
			while(digitalRead(pin) == 1){
				usleep(100);
				time_high++;
			}
			while(digitalRead(pin) == 0){
				usleep(100);
				time_low++;
			}

			hz = 1 / ((time_high + time_low) * 0.0001);
			hz = hz * .58; 
			hz_data[num_cycle] = hz;
			num_cycle++;

			if(num_cycle == 1000){

				for(int i = 0; i < 1000; i++)
					average += hz_data[i];
				average /= 1000;				
				if(average > 100.5)
					digitalWrite(gpioOut, HIGH);
				else if(average < 99.5)
					digitalWrite(gpioOut, LOW);
				else if((average > 99.5) && (average < 100.5)){
					
						for(int i = 0; i < 5; i++){
							digitalWrite(gpioOut, LOW);
							usleep(100000);
							digitalWrite(gpioOut, HIGH);
                                                        usleep(100000);
							digitalWrite(gpioOut, LOW);
                                                        usleep(100000);                                                       
							digitalWrite(gpioOut, HIGH);
                                                        usleep(100000);
							digitalWrite(gpioOut, LOW);
						}
					}
				for(int i = 0; i < 10; i++)
                                        hz_data[i] = 0;
				num_cycle = 0;
				average = 0;

			}
			


	}
}
//Intialize GPIO pins being used
void gpioInit()
{
        int gpioIn = 0;  //pin 11
        int gpioOut = 2; //pin 13
        wiringPiSetup();
        //input
	pinMode(gpioIn[i], INPUT);
        pullUpDnControl(gpioIn[i], PUD_UP);
	
	//output
        pinMode(gpioOut, OUTPUT) ;
        digitalWrite(gpioOut, LOW);	




}
