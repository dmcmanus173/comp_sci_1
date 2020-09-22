/*==================================================================
 *
 *               University College Dublin
 *          EEEN20010 - Computer Engineering I
 *
 * Assignment:  Bruteforce Solution for Knapsack problem
 *
 * File Name:   optpack.c
 *
 * Description: Generates total value, weight and cost for every
 * possible combination of items in an inputted list and it prints
 * the one solution with the highest value, that is also under an
 * inputted cost and weight limit.
 *
 * Authors:     Daniel McManus
 *
 * Date:        02 December 2017
 *
 *==================================================================*/

/*==================================================================
 * Systems header files
 *==================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*==================================================================
* Max amount of items that can be scanned from a list.
==================================================================*/
#define MAX_ITEMS 80

/*==================================================================
* struct 'item' grouping label ,value, weight and cost arrays.
==================================================================*/
struct item{
    int label;
    int value;
    int weight;
    int cost;
};
typedef struct item Item;

/****************************************************************************
 *
 * Procedure Name : print_table
 *
 * Purpose        : Prints how many items are in the table
 *                  Prints table of items, with labels, respective values,
 *                      weights and costs.
 *
 * Parameters     : num_items - number of items in a list.
 *                  item[] - contains items weights, costs, values.
 *                  *filename - pointer to str containing inputted filename
 *
 ****************************************************************************/
void print_table(int num_items, Item item[], char *filename){
    int i;
    printf("\"%s\" contains the following %d items:\n", filename, num_items);
    printf("|-----------------------------------------|\n");
    printf("|  Item # |  Value  |  Weight  |   Cost   |\n");
    printf("|-----------------------------------------|\n");
    for(i=0; i<num_items; i++){
        printf("|  %3d    |  %3d    |   %3d    |   %3d    |\n", item[i].label, item[i].value, item[i].weight, item[i].cost );
        printf("|-----------------------------------------|\n");
    }
}

/****************************************************************************
 *
 * Procedure Name : brute_pack
 *
 * Purpose        : Finds every possible combination of items in a given list
 *                  Finds the value, weight and cost for each combination
 *                  Prints the combination with the highest value while
 *                      meeting the weight/cost requirement
 *
 * Parameters     : num_items, weight_lim, cost_lim, itemp[], *best_bag
 *
 ****************************************************************************/
void brute_pack(int num_items, int weight_lim, int cost_lim, Item item[], Item *best_bag){
    Item *bag;
    int i, j, k, num, remainder, total_cost, total_val, total_weight, best_val, best_weight, best_cost;
    for(i=0;i<pow(2,num_items);i++){
        total_cost=0;
        total_val=0;
        total_weight=0;
        k=0;
        num=i;
        bag=malloc(num_items*sizeof(Item));
        while(num>0){
            remainder=num%2;
            if(remainder==1){
                bag[k]=item[k];
                total_val+=item[k].value;
                total_cost+=item[k].cost;
                total_weight+=item[k].weight;
            }
            num/=2;
            k++;
        }
        if((total_weight<=weight_lim)&&(total_cost<=cost_lim)&&(total_val>best_val)){
            best_bag=bag;
            best_val=total_val;
            best_weight=total_weight;
            best_cost=total_cost;
        }
    }
    printf("\nWith the weight limit of %d kg and the cost limit of %d Eur,\n", weight_lim, cost_lim);
    printf("The best combination is:\n [");
    for(j=0; j<num_items; j++){
        if(best_bag[j].label!=0)
            printf(" %d", best_bag[j].label);
    }
    printf(" ] with total value: %d, weight: %d, and cost:%d\n", best_val, best_weight, best_cost);
}

/****************************************************************************
 *
 * Procedure Name : go_again
 *
 * Purpose        : Asks does the user wish to try another file.
 *                  Scans until 'y' or 'n' is typed, the program quits.
 *
 * Parameters     : none
 *
 ****************************************************************************/
char again(){
char opt[0];
    printf("\nDo you want to try another file [y/n]:    ");
    while(1){
        while(1){
            scanf(" %s",&opt);
            if(opt[1]==0)
                break;
        }
        if((opt[0]=='Y')||(opt[0]=='N'))
            opt[0]=opt[0]+32;
        if((opt[0]=='y')||(opt[0]=='n')){
            return opt[0];
        }
    }
}

/****************************************************************************
 *
 * Procedure Name : main
 *
 * Purpose        : Scans filename containing list from user
 *                  Opens a file by name inputted
 *                  Scans file, sorting table into respective categories
 *                  Scans required weight/cost limit from the user
 *                  Calls the print_table function
 *                  Calls brute_pack function
 *                  Calls 'again' function
 *
 * Parameters     : none
 *
 *
 ****************************************************************************/
int main(){
    FILE *input;
    char filename[FILENAME_MAX + 1], *fname=filename, header[10];
    Item *item, *best_bag;
    int i, line, num_items, weight_lim, cost_lim;
    while(1){
        printf("Enter the file name containing a list of objects: ");
        scanf("%s", filename);
        if((input = fopen(filename, "r")) == NULL){
            fprintf(stderr, "Failed to open \"%s\".\n\n", filename);
            continue;
        }
        fscanf(input, "%s %s %s", header, header, header);
        item = calloc(MAX_ITEMS, sizeof(Item));
        for (i=0; i<MAX_ITEMS; i++){
            item[i].label=i+1;
            line = fscanf(input, "%d %d %d", &item[i].value, &item[i].weight, &item[i].cost);
            if(line==EOF){
                break;
            }
        }
        num_items=i;
        fclose(input);
        if(line==EOF){
            item=realloc(item, num_items*sizeof(Item));
            best_bag=malloc(num_items*sizeof(Item));
        }
        else{
            fprintf(stderr,"The number of objects in \"%s\" exceeds the item limit of 80.\n\n", filename);
            continue;
        }
        printf("Enter the required weight limit and cost limit: ");
        scanf("%d %d", &weight_lim, &cost_lim);
        printf("\n");
        print_table(num_items, item, fname);
        brute_pack(num_items, weight_lim, cost_lim, item, best_bag);
        if(again()=='n')
            return 0;
        else
            printf("\n");
    }
    return(0);
}
