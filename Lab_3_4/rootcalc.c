#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Start_Sequence(){
    printf("************************************************\n");
    printf("Welcome to the quadratic root estimator.\n");
    printf("This estimates the value of one root of\n");
    printf("f(x)=ax^2+bx+c.\n");
    printf("************************************************\n\n");
}

float EquationRoot(int a, int b, int c){
    int x, z = c;
    for(x=1.0; x<=10.0; x++)
    {
        if(((a*x*x+b*x+c)<z) && ((a*x*x+b*x+c)>=0))
            z = x;
        if(((a*x*x-b*x+c)<-z) && ((a*x*x+b*x+c)<=0))
            z = -x;
        }
    return(z);
}

int main(){
    while(1){
        int a,b,c;
        Start_Sequence();
        printf("Enter the coefficients in the form \"a b c\": ");
        scanf("%d %d %d", &a, &b, &c);
        printf("\n");
        if((b*b)>=(4*a*c)){
            printf("There is a root at: x = %.3f\n", EquationRoot(a,b,c));
            }
        else{
            printf("Complex Roots - cannot estimate with this program\n");
            }
        char repeat;
        printf("Do you wish to try another quadratic [y/n]: ");
        while(1){
            scanf(" %c", &repeat);
            if(repeat=='y'){
                printf("/n");
                break;
                }
            if(repeat=='n')
                return 0;
            }
        }
}
