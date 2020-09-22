/*==================================================================
 *
 *               University College Dublin
 *          EEEN20010 - Computer Engineering I
 *
 * Assignment:  The game of Hangman
 *
 * File Name:   hangman.c
 *
 * Description: In the game of hangman, the player picks a word by
 * inputting the name of a text file containing a word and then has
 * to try to guess what the word is by selecting one letter at a
 * time. If they select a correct letter, all occurrences of the
 * letter are shown. If no letter shows up, they use up one of their
 * turns. The player is allowed to use no more than 10 incorrect
 * turns to guess what the word is. They can guess the word at any
 * time, but if they guess incorrectly, they lose a turn.
 *
 * Authors:     Daniel McManus
 *
 * Date:        15 November 2017
 *
 *==================================================================*/

/*==================================================================
 * Systems header files
 *==================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/****************************************************************************
 *
 * Procedure Name : Initialisation
 *
 * Purpose        : Scans a filename from the user
 *                  Opens a file with inputted name
 *                  Scans the file content and stores as a string
 *                  Ensures word from file is in lowercase
 *                  Creates a string of the same length but with '*'
 *                  Closes file that was opened.
 *                  0's all values in 'guessed' array.
 *
 * Parameters     : *pword, a pointer to char array that will store input word
 *                  *hid, a pointer to a char array that will store the
 *                   hidden word(with '*')
 *                  *guessed, a pointer to an array that will store previously
 *                   guessed letters
 *
 ****************************************************************************/
void Initialisation(char *pword, char *hid, char *guessed){
char filename[FILENAME_MAX + 1];
FILE *ipfile;
while(1){
    printf("Give the filename with the unknown word: ");
    scanf(" %[^\n]s",filename);
    if((ipfile=fopen(filename, "r")) == NULL){
        printf("The file specified doesn't exist.\n");
        continue;
    }
    else if(fscanf(ipfile, "%s", pword) != 1){
        printf("The file specified is empty.\n");
        continue;
    }
    break;
}
fclose(ipfile);             /*closes file opened by program*/
int i;
for(i=0; pword[i]!=0; i++){      /*ensures file word in full lowercase*/
    if(pword[i]<97)
        pword[i]=pword[i]+32;
    hid[i]='*';
}
hid[i]=0;               /*gives unwritten array values a null value*/
for(i=0; i<=26; i++){
    guessed[i]=0;
}
printf("\nReady to Start!\nThe word is:  %s\n",hid);
}

/****************************************************************************
 *
 * Procedure Name : WordOrLetter
 *
 * Purpose        : Scans for the user to input a single character and will
 *   pass it on to main when a 'w' or 'l' is entered.
 *
 * Parameters     : none
 *
 ****************************************************************************/
char WordOrLetter(){
char opt[1];
printf("\nWould you like to guess the word [w] or guess a letter [l]: ");
while(1){
    while(1){
        scanf(" %s",&opt);
        if(opt[1]==0)
            break;
    }
    if((opt[0]=='w')||(opt[0]=='l'))
        return opt[0];
}
}

/****************************************************************************
 *
 * Procedure Name : Pick_Word
 *
 * Purpose        : scans the word to be guessed
 *                  converts to lowercase if necessary
 *                  ensures no symbols inputted in 'word'
 *                  checks if word is correct
 *                  if correct, returns 1, else returns 0
 *
 * Parameters     : char word[]
 *
 ****************************************************************************/
int Pick_Word(char word[]){
char guessword[50];
int i;
RETRY:;
printf("What is your guessed word?: ");
scanf(" %s",&guessword);
for(i=0; guessword[i]!=0; i++){
    if((guessword[i]>=65)&&(guessword[i]<=90))
        guessword[i]=guessword[i]+32;           /*makes letter from capital to lowercase*/
    if((guessword[i]<97)||(guessword[i]>122)){     /*string contains non standard symbols*/
        printf("This is not a word. Please try again.\n");
        goto RETRY;
    }
}

if (strcmp(word, guessword) == 0)   /*compares arrays*/
    return 1;
else
    return 0;
}

/****************************************************************************
 *
 * Procedure Name : scanletter
 *
 * Purpose        : scans until a single character that is a letter is inputted
 *                  converts capital letter to lowercase if necessary
 *
 * Parameters     : none
 *
 ****************************************************************************/
char scanletter(){
char opt[0];
while(1){
    while(1){
        scanf(" %s",&opt);
        if(opt[1]==0)
            break;
    }
    if(opt[0]<=90)
        opt[0]=opt[0]+32;
    if((opt[0]<=122)&&(opt[0]>=97))
        return opt[0];
}
}
/****************************************************************************
 *
 * Procedure Name : Pick_Letter
 *
 * Purpose        : Checks if guessletter is in the word array
 *
 * Parameters     : char word[], char guessletter
 *
 ****************************************************************************/
int Pick_Letter(char word[], char guessletter){
int i;
for(i=0; word[i]!=0;i++){
    if(guessletter==word[i])
        return 1;
}
return 0;
}

/****************************************************************************
 *
 * Procedure Name : prev_guess
 *
 * Purpose        : searches array for previous guess matching guessed letter
 *                  if it find the same letter it'll return a value to main
 *                  adds guessletter to array if not found
 *
 * Parameters     : char *pguess, char guessletter
 *
 ****************************************************************************/
int prev_guess(char *guessed, char guessletter){
int i, exit=0;

for(i=0; guessed[i]!=0; i++){
    if(guessed[i]==guessletter){
        printf("\n***********************************************\n");
        printf("You've already made this guess!");
        exit=1;
        break;
    }
}
if(exit==0)
    guessed[i]=guessletter;
return exit;
}

/****************************************************************************
 *
 * Procedure Name : Reveal_Letter
 *
 * Purpose        : checks for instances when guessed letter is in the word
 *  array and then inserts the letter into the hidden array at that given state
 *
 * Parameters     : char word, char *hid, char guessletter
 *
 ****************************************************************************/
void Reveal_Letter(char word[], char *hid, char guessletter){
int i;
for(i=0; word[i]!=0; i++){
    if(guessletter==word[i])
        hid[i]=guessletter;
}
printf("\n***********************************************\n");
printf("Good Choice!\n");
printf("The word is: %s",hid);
}

/****************************************************************************
 *
 * Procedure Name : Wrong_Guess
 *
 * Purpose        : Decreases chances by one, and prints what the word was if
 *                  chances are zero, or what it is revealed at the time if it
 *                  isnt zero.
 *
 * Parameters     : int chances, char word[], char hidden[]
 *
 ****************************************************************************/
int Wrong_Guess(int chances, char word[], char hidden[]){
printf("\n***********************************************\n");
printf("Bad Choice!\n");
chances--;
if(chances==0){
    printf("You are out of turns! The word was: %s\n",word);
    return 0;
}
printf("The word is: %s",hidden);
return chances;
}

/****************************************************************************
 *
 * Procedure Name : go_again
 *
 * Purpose        : Asks does the user wish to play again. scans until 'y' or
 *      'n' is typed, the program quits.
 *
 * Parameters     : none
 *
 ****************************************************************************/
char go_again(){
char opt[0];
printf("\n\n***********************************************\n");
printf("Do you want to play again [y/n]:");
while(1){
    while(1){
        scanf(" %s",&opt);
        if(opt[1]==0)
            break;
    }
    if((opt[0]=='Y')||(opt[0]=='N'))
        opt[0]=opt[0]+32;
    if((opt[0]=='y')||(opt[0]=='n'))
        return opt[0];
}
}

/****************************************************************************
 *
 * Procedure Name : main
 *
 * Purpose        : Creates arrays and pointers to store arrays and edit
 *      them in functions
 *                  Calls initialisation function to setup game
 *                  Uses WordOrLetter output to call relevant functions to
 *      correspond to users inputs
 *
 * Parameters     : none
 *
 ****************************************************************************/
int main(){
while(1){
    char hidden[50], word[50], guessed[26];
    char *hid=hidden, *pword=word, *pguess=guessed;
    char guessletter;
    int chances=10;
    Initialisation(pword, hid, pguess);
    while(chances>0){
        printf("\nNumber of turns remaining: %d",chances);
        if(WordOrLetter()=='w'){
            if((Pick_Word(word))==1){
                printf("\nCongratulations!\n");
                break;
            }
            else
                chances=Wrong_Guess(chances, word, hidden);
        }
        else{
            printf("What letter have you chosen?: ");
            guessletter=scanletter();
            if((prev_guess(pguess, guessletter))==1){
                printf("\nThe word is:  %s",hidden);
                continue;
            }
            if((Pick_Letter(word, guessletter))==1){
                Reveal_Letter(word, hid, guessletter);
                if(strcmp(word, hidden) == 0)
                    break;
            }
            else
                chances=Wrong_Guess(chances, word, hidden);
        }
    }
    if(go_again()=='n')
        return 0;
}
}
