/*==================================================================
 *
 *               University College Dublin
 *          EEEN20010 - Computer Engineering I
 *
 * Assignment:  Find Root of Cubic Equation
 *
 * File Name:   root.c
 *
 * Description: User inputs values for a,b,c,
 *              Program finds root of a*x^3+b*x^2+c*x+d
 *              Program prints root of equation
 *
 * Authors:     Daniel McManus
 *
 * Date:        20 October 2017
 *
 *==================================================================*/

/*==================================================================
 * Systems header files
 *==================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*==================================================================
 * Function definitions
 *==================================================================*/
/****************************************************************************
 *
 * Procedure Name : Start_Sequence
 *
 * Purpose        : Prints the Intro message of the program
 *
 *
 * Parameters     : none
 *
 *
 ****************************************************************************/
void Start_Sequence(){
    printf("************************************************\n");
    printf("Welcome to the cubic root estimator.\n");
    printf("This estimates the value of one root of\n");
    printf("f(x)=ax^3+bx^2+cx+d.\n");
    printf("************************************************\n\n");
}

/****************************************************************************
 *
 * Procedure Name : Root_Equation
 *
 * Purpose        : Reads in a,b,c,d from main
 *                  Sets an interval [x1,x2]
 *                  Finds middle of interval
 *                  Calculates equation with middle set to x
 *                  Narrows the interval by setting m to either x1 or x2
 *                  Repeats above until finds root
 *                  Returns root to main
 *
 * Parameters     : a,b,c,d in the form a*x^3+b*x^2+c*x+d
 *
 *
 ****************************************************************************/
float Root_Equation(int a, int b, int c, int d){
    int x1=-100, x2=100, m, yx1, yx2, ym;
    if(d==0)
        return(0);
    if((((a*x1*x1*x1+b*x1*x1+c*x1+d)>0) && ((a*x2*x2*x2+b*x2*x2+c*x2+d)>0)) || (((a*x1*x1*x1+b*x1*x1+c*x1+d)<0) && ((a*x2*x2*x2+b*x2*x2+c*x2+d)<0)))
    {
        x1=x1-100;              //Ensures we always find root by widening interval if required.
        x2=x2+100;
    }
    while(1){
        m=(x1+x2)/2;
        ym=a*m*m*m+b*m*m+c*m+d;
        yx1=a*x1*x1*x1+b*x1*x1+c*x1+d;
        yx2=a*x2*x2*x2+b*x2*x2+c*x2+d;
        if(((ym>0)&&(yx2>0))||((ym<0)&&(yx2<0)))
            x2=m;
        else if(((ym>0)&&(yx1>0))||((ym<0)&&(yx1<0)))
            x1=m;
        if(abs(abs(x1)-abs(x2))<=1)     //exit sequence if x1,x2 have a gap of 1
           return(m);
        if((ym==0))
            return(m);
    }
}

/****************************************************************************
 *
 * Procedure Name : main
 *
 * Purpose        : Scans in values for a,b,c,d from user
 *                  where a,b,c,d is in the form a*x^3+b*x^2+c*x+d
 *                  Calls the function Start_Sequence
 *                  Prints value returned from Root_Equation
 *                  Asks user do they want to repeat/exit the program
 *
 * Parameters     : none
 *
 *
 ****************************************************************************/
int main(){
    Start_Sequence();
    while(1){
        int a,b,c,d;
        printf("Enter the coefficients in the form \"a b c d\": ");
        scanf("%d %d %d %d", &a, &b, &c, &d);
        if((a==0) || ((a==0)&&(b==0)&&(c==0)))   //checks if quadratic or straight line
            printf("This is not a cubic equation.");
        else
            printf("\nThere is a root at: x = %.3f\n", Root_Equation(a,b,c,d));
        char repeat;
        printf("Do you wish to try another cubic [y/n]: ");
        while(1){
            scanf(" %c", &repeat);
            if(repeat=='y'){
                printf("\n");
                break;
                }
            if(repeat=='n')
                return 0;
            }
        }
}
