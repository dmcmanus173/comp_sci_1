
/*==================================================================
 *
 *               University College Dublin
 *          EEEN20010 - Computer Engineering I
 *
 * Assignment:  Suboptimal Knapsack problem solver
 *
 * File Name:   subpack.c
 *
 * Description: Finds a "good solution" for the Knapsack problem
 *              without bruteforcing a solution
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
* struct 'item' grouping label, value, weight and cost arrays.
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
 * Procedure Name : sub_pack
 *
 * Purpose        : Finds item with highest value in item array
 *                  Sees if it can add highest value to total val's
 *                  Prints 'good solution' along with its total value, weight
 *                  and cost
 *
 * Parameters     : num_items, weight_lim, cost_lim, item[]
 *
 ****************************************************************************/
void sub_pack(int num_items, int weight_lim, int cost_lim, Item item[]){
    int i, j, x, total_val=0, total_weight=0, total_cost=0, best_val;
    printf("\nWith the weight limit of %d kg and the cost limit of %d Eur,\n", weight_lim, cost_lim);
    printf("The best combination is:\n [");
    for(i=0; i<num_items; i++){
        best_val=0;
        for(j=0; j<num_items; j++){
            if(best_val<item[j].value){
                x=j;
                best_val=item[j].value;
            }
        }
        if(((total_cost+item[x].cost)<=cost_lim) && ((total_weight+item[x].weight)<=weight_lim)){
            total_weight+=item[x].weight;
            total_cost+=item[x].cost;
            total_val+=item[x].value;
            printf("%d ", item[x].label);
        }
        item[x].value=0;
    }
    printf("] with total value: %d, weight: %d, and cost:%d\n", total_val, total_weight, total_cost);
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
 *                  Calls sub_pack function
 *                  Calls 'again' function
 *
 * Parameters     : none
 *
 *
 ****************************************************************************/
int main(){
    FILE *input;
    char filename[FILENAME_MAX + 1], *fname=filename, header[10];
    Item *item;
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
        }
        else{
            fprintf(stderr,"The number of objects in \"%s\" exceeds the item limit of 80.\n\n", filename);
            continue;
        }
        printf("Enter the required weight limit and cost limit: ");
        scanf("%d %d", &weight_lim, &cost_lim);
        printf("\n");
        print_table(num_items, item, fname);
        sub_pack(num_items, weight_lim, cost_lim, item);
        if(again()=='n')
            return 0;
        else
            printf("\n");
    }
    return(0);
}
