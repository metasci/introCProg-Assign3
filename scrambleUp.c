// Nicholas Beaudoin
// Assignment 3
// 3 - 29 - 16


#define _CRT_SECURE_NO_WARNINGS 1

#define SIZE 50
#include <stdio.h>
#include <string.h>
#include <ctype.h> // uppercase to lowercase transition



/*
 * Function Prototypes
 */
 
//A function that displays the instructions on how to play the game.
void HowToPlay();

//A function that returns the letter that the user has guessed.
void GetGuess(char *guess);

//A function that determines if the player would like to play again. 
void playAgain(char *playagn);

//A function that tells the user if they won or lost
void WinOrLose(int result);

//A function that sets all of the characters in a word to the same case (upper or lower).
void wordToLower(char wrd[]);

//A function that locates and places the selected letter where it belongs in the partial solution array.
void PutInPlace(char guess, char wrd[], char partial[]);

//A function that plays one entire game 
void PlayOneGame(char scram[], char solution[]);

//One additional function of your own choice.
int compareWords(char guess[], char solution[]);



int main()
{
	//declare variables
    FILE * wordPtr;
    char scram[SIZE]="";
    char solution[SIZE]="";
    char play = 'y';
	//display instructions
    HowToPlay();
	//open file
    wordPtr = fopen("scrambledwords.txt", "r");
    
	do{
		//get word from file
        fscanf(wordPtr, " %s   %s", solution, scram);
		
        // set both to lowercase
        wordToLower(solution);
        wordToLower(scram);
        
        
        //play one game
        PlayOneGame(scram, solution);
        
		//play again???
        playAgain(&play);
        
	}while(play == 'y');
    
    fclose(wordPtr);
    
	return 0;
}


/*
 * Function Definitions 
 */
 
//A function that displays the instructions on how to play the game.
void HowToPlay(){
    printf("\nWelcome to the Scrambled-Up game\n");
    printf("You will see the word in scrambled form.\n");
    printf("Pick a letter and I will show you where the letter belongs in the word.\n");
    printf(". . . Next you guess the word . . .\n");
    printf("If you can't guess it, don't worry.\n");
    printf("You will have three guesses to figure it out!\n\n");
}

//A function that plays one entire game 
void PlayOneGame( char scram[], char solution[])
{
    char partial[SIZE]="";
    char wrdGuess[SIZE]="";
    char lettGuess;
    int numGuess=1, correct=0, i;
    
    // create partial solution
    i=0;
    while(solution[i]){
        strcat(partial, "*");
        i++;
    }
    
    
	do{	
		//Display scrambled word
        printf("~~~~~~~~~~~~~~~ PICK A LETTER ~~~~~~~~~~~~~~~\n\n");
        printf("Here is the scrambled word:\n\n");
        printf("    %s\n\n", scram);
        
		//Display partial solution
        printf("Here are the letters you have so far:\n\n");
        printf("    %s\n\n", partial);
        
        // get users guessed letter
        GetGuess(&lettGuess);
        
		//locate where letter appears in solution
		//place letter in same location in partial solution
        PutInPlace(lettGuess, solution, partial);
        
        
		//display updated partial solution
        printf("\n-------------- GUESS THE WORD --------------\n\n");
        printf("Here is the scrambled word:\n\n");
        printf("    %s\n\n", scram);
        
        printf("Here are the letters you have so far:\n\n");
        printf("    %s\n\n", partial);
        
		//get user guess
        printf("GUESS THE WORD: ");
        scanf(" %s", wrdGuess);
        //set wrdGuess to lowercase
		wordToLower(wrdGuess);
        
        //if correct = game over, loop ends
        
        correct = compareWords(wrdGuess, solution);
        
        if(!correct){
            
            printf("  That was guess #%d\n\n", numGuess);
            if(numGuess == 3){
                printf("The word was %s", solution);
            }
            
            //update wrong guess count
            numGuess++;
        }
        
	}while(!correct && numGuess<=3);
    
    WinOrLose(correct);
}


//A function that determines if the player would like to play again. 
void playAgain(char *playAgn) {
    char temp;
    printf("\nWould you like to play again (Y or N)? ");
    scanf(" %c", &temp);
    *playAgn = tolower(temp);
}


//A function that sets all of the characters in a word to the same case (upper or lower).
void wordToLower(char wrd[]){
    int i = 0;
    
    while(wrd[i]){
        wrd[i] = tolower(wrd[i]);
        i++;
    }
}

//A function that locates and places the selected letter where it belongs in the partial solution array.
void PutInPlace(char guess, char wrd[], char partial[]){
    int i = 0;
    while(wrd[i]){
        if (wrd[i] == guess){
            partial[i] = guess;
        }
        i++;
    }
}



//A function that returns the letter that the user has guessed.
void GetGuess(char *guess){
    char temp;
    //Ask player for a letter
    printf("WHAT LETTER WOULD YOU LIKE TO PLACE? ");
    scanf(" %c", &temp);
    // set lettguess to lowercase
    *guess = tolower(temp);
}

//One additional function of your own choice.
int compareWords(char guess[], char solution[]){
    if(!strcmp(guess, solution)){
        printf("\n  The word was %s\n", guess);
        return 1;
    }else{
        //if not correct
        printf("\n  %s is not the word\n", guess);
        //if guesses left repeat loop
        return 0;
    }
}


//A function that tells the user if they won or lost
void WinOrLose(int result){
    if(result == 1){
        printf("\nYay -- you won :)\n");
    }else{
        printf("\nSorry you did not win this round\n");
    }
}

