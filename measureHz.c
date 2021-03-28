#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <unistd.h>
void gpioInit();

//Returns 1 if 1 pin if pin A is pressed, 2 if pin B is pressed, 3 for both
//0 for neither
int read_pins(int pin_a, int pin_b);

void millisleep();

int main(int argc, char*argv[])
{
	int pin = 0;
	double time = 0;
	double curr_time = 0;
	double hz = 0;
	//Sets up wiring Pi
	gpioInit();
	
	while(1){
		
		if(digitalRead(pin) == 1){
			curr_time = time;
			while(digitalRead(pin) == 1){
				usleep(1);
				time++;
			}
			while(digitalRead(pin) == 0){
				usleep(1);
				time++;
			}
			hz = 1 / ((time - curr_time) * .000001); 
			printf("Hz: %lf\n %lf\n %lf\n", hz, time, curr_time);
			usleep(1);
			time++;
		}
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
