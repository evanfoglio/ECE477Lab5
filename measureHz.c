#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <unistd.h>
void gpioInit();

void millisleep();

int main(int argc, char*argv[])
{
	int pin = 1;
//	double time = 0;
//	double curr_time = 0;
	double hz = 0;
	double time_high = 0;
	double time_low = 0;
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
			printf("Hz: %lf\n", hz);
	}
}
//Intialize GPIO pins being used
void gpioInit()
{
        //int gpioOut[8] = {2, 3, 4, 5, 6, 7, 8, 9};
        int gpioIn[2] = {0, 1};
        int i;
        wiringPiSetup();
        for(i = 1; i >= 0; i--){
                pinMode(gpioIn[i], INPUT);
                pullUpDnControl(gpioIn[i], PUD_UP);
        }
}


void millisleep()
{
		usleep(1000);
}
