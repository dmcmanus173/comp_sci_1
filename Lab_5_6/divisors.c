/*==================================================================
 *
 *               University College Dublin
 *          EEEN20010 - Computer Engineering I
 *
 * Assignment:  Count Positive Integers with a Given Number of
 *              Divisors
 *
 * File Name:   divisors.c
 *
 * Description: Reads in an integer 'k' and prints out the number
 *              of positive integers between 1 and 100000(inclusive)
 *              which have exactly k divisors.
 *
 * Authors:     Daniel McManus
 *
 * Date:        30 October 2017
 *
 *==================================================================*/

/*==================================================================
 * Systems header files
 *==================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/****************************************************************************
 *
 * Procedure Name : main
 *
 * Purpose        : Scans in users target number of divisors
 *                  Calls the function Divisors
 *                  Prints amount of numbers with target number of divisors
 *
 * Parameters     : none
 *
 *
 ****************************************************************************/
int main(){
float a;
int b;
while(1){
    printf("Enter the target number of divisors: ");
    scanf("%f",&a);
    b=a;
    if(((b-a)!=0) || (b<0))             //makes sure value inputted isnt float or negative
        printf("The value entered is not a valid divisor. Please enter a positive integer.\n\n");
    else
        break;
}
printf("\n");
if(b==1 || b==0)
    printf("There are %d numbers between 1 and 100000 inclusive which have exactly %d divisors.\n",b,b);
else
    printf("There are %d numbers between 1 and 100000 inclusive which have exactly %d divisors.\n",Divisors(b),b);
return(0);
}

/****************************************************************************
 *
 * Procedure Name : Divisors
 *
 * Purpose        : Interval from 2-100,000
 *                  Checks amount of divisors per number
 *                  Increments a count everytime a number has the
 *                  desired amount of divisors
 *                  Returns total amount to main
 *
 * Parameters     : target
 *
 *
 ****************************************************************************/
int Divisors(int target){
int i, divide, count,result, top=100000, total=0;
for(i=2; i<=top; i++){
    count=0;
    divide=1;
    result=0;
    while(divide<=i){
        if(result==divide)
            break;
        if(i%divide==0){
            result=i/divide;
            if(result==divide){
                count++;
                break;
            }
            else
                count=count+2;
        }
        divide++;
    }
    if(count==target)
        total++;
}
return(total);
}

