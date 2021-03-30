#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <unistd.h>
void gpioInit();

void millisleep();

int main(int argc, char*argv[])
{
	int pin = 0;
	double hz = 0;
	double time_high = 0;
	double time_low = 0;
	double hz_data[10] = {0};
	double average;
	int num_cycle = 0;
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

			if(num_cycle == 10){

				for(int i = 0; i < 10; i++)
					average += hz_data[i];
				average /= 10;				
				if(average > 100.5)
					printf("Too Fast! Hz: %lf\n", average);
				else if(average < 99.5)
					printf("Too Slow! Hz: %lf\n", average);
				else if((average > 99.5) && (average < 100.5))
					printf("Just Right! Hz: %lf\n", average);
				for(int i = 0; i < 10; i++)
                                        hz_data[i] = 0;
				num_cycle = 0;
				average = 0;

			}
			


			//printf("Hz: %lf\n", hz);
	}
}
//Intialize GPIO pins being used
void gpioInit()
{
        int gpioIn[2] = {0};
        int i;
        wiringPiSetup();
        for(i = 1; i >= 0; i--){
                pinMode(gpioIn[i], INPUT);
                pullUpDnControl(gpioIn[i], PUD_UP);
        }
}
