/*==================================================================
 *
 *               University College Dublin
 *          EEEN20010 - Computer Engineering I
 *
 * Assignment:  flight
 *
 * File Name:   flight.c
 *
 * Description: Takes distance in Km and calculates flight time.
 *
 * Authors:     Daniel McManus
 *
 * Date:        06 October 2017
 *
 *==================================================================*/

/*==================================================================
 * Systems header files
 *==================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*==================================================================
* Kilometer to Mile Conversion
==================================================================*/
#define km_mile 0.621371

/*==================================================================
 * Function definitions
 *==================================================================*/

/****************************************************************************
 *
 * Procedure Name : flight_calc
 *
 * Purpose        : Reads in distance from main
 *                  Converts distance to miles
 *                  Calculates flight time in hours and the nearest minute
 *                  Prints distance and flight time in table
 *
 * Parameters     : Distance in Kilometers
 *
 *
 ****************************************************************************/
void flight_calc(float distance)
{
    int hours, velocity=529;
    float distanceM, minutes, time;
    distanceM=distance*km_mile;     /*Converts distance*/
    time=distanceM/velocity;
    hours=distanceM/velocity;
    minutes=(time-hours)*60;        /*Fraction of remainder hour to Minutes*/
    printf("| %9.2f     | %6.1d     |%7.0f         |\n",distance,hours,minutes);
}

/****************************************************************************
 *
 * Procedure Name : main
 *
 * Purpose        : Scans in values for distance-flight time table from user
 *                  Prints start of table
 *                  Provides distance value when calling flight_calc
 *                  Prints the bottom of the table
 *
 * Parameters     : none
 *
 *
 ****************************************************************************/
int main(){
float lower, upper, step;
printf("Enter the lower limit on distance in km:      ");
scanf("%f",&lower);
printf("Enter the upper limit on distance in km:      ");
scanf("%f",&upper);
printf("Enter the step size in km:                    ");
scanf("%f",&step);
if((lower>upper)||(upper-lower<step)|| (step<0.001))
{
    printf("\nError detected!. Inputted values aren't valid.");
    return 0;
}
printf("\n\n===============================================\n| distance (km) |    hours   |    minutes     |\n|=============================================|\n");
while(lower<=upper)     /*Keeps table generating extra, unwanted distance values.*/
{
    flight_calc(lower);
    lower=lower+step;   /*Increments lower value by value of step*/
}
printf("===============================================");  /*End of table*/
}
