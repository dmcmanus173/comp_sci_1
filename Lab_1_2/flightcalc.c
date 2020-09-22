#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int hours, real_minutes, velocity=529;
    float distance, minutes, time, km_mile=0.621371;
    printf("Enter the distance travelled by the aeroplane in kilometers:  ");
    scanf("%f",&distance);
    distance=distance*km_mile;
    time=distance/velocity;
    hours=distance/velocity;
    minutes=(time-hours)*60;
    real_minutes=(int)minutes;
    if((minutes-real_minutes)*60>=30)
    {
        real_minutes++;
    }
    printf("\nThe aeroplane's flight time is %d hours and %d minutes.\n",hours,real_minutes);
    return(0);
}
