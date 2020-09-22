#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int hours, velocity=529;
    float distance, minutes, time, km_mile=0.621371;
    printf("Enter the distance travelled by the aeroplane in kilometers:  ");
    scanf("%f",&distance);
    if(distance<0){
        printf("\nInvalid input. Please try again.\n");
        scanf("%f",&distance);
    }
    distance=distance*km_mile;
    time=distance/velocity;
    hours=distance/velocity;
    minutes=(time-hours)*60;
    printf("\nThe aeroplane's flight time is %d hours and %.0f minutes.\n",hours,minutes);
    return(0);
}
