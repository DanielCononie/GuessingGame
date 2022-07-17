/* Name : Daniel Cononie
 * Last modified: 07/16/2022
 * PURPOSE: This program will take input for the max number to guess to and the max number of guesses
 * , then will generate a random number for the user to guess based on the max number to guess.
 * The program will notify the user when they are getting closer or farther from their past guess by
 * saying "Getting warmer" or "Getting colder"
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void newGame(int *maxGuessesAllowed, int *answer, int *max, bool *gameOver, int *differential, int *numGuessesTaken);
void guessMethod(int *guess, int *maxGuessesAllowed, int *answer, int *max, bool *gameOver,
				 int *differential, int *numGuessesTaken, int *last_differential);
void higherGuess(int *guess, int *maxGuessesAllowed, int *answer, int *max, bool *gameOver,
		 	 	 int *differential, int *numGuessesTaken, int *last_differential);
void lowerGuess(int *guess, int *maxGuessesAllowed, int *answer, int *max, bool *gameOver,
		 int *differential, int *numGuessesTaken, int *last_differential);
void rightGuess(int *guess, int *answer, bool *gameOver);
int isGameOver(bool *gameOver, int counter);



int main() {

	// Variable declarations
	int answer;
	int guess = 0;
	bool gameOver = false;
	int differential;
	int max;
	int maxGuessesAllowed;
	int numGuessesTaken;
	int last_differential = 0;
	int counter = 0;

	// Beginning of start loop
	while(counter == 0)	{
		newGame(&maxGuessesAllowed, &answer, &max, &gameOver, &differential, &numGuessesTaken);

		// Beginning of guess loop
		while (gameOver == false) {


			guessMethod(&guess, &maxGuessesAllowed, &answer, &max, &gameOver, &differential, &numGuessesTaken,
						&last_differential);

			// If the user enters a number higher than the answer
			if(guess > answer) {

				higherGuess(&guess, &maxGuessesAllowed, &answer, &max, &gameOver, &differential, &numGuessesTaken,
						&last_differential);
			} // end if guess > answer

			// If the user enters a number lower than the answer
			if(guess < answer) {

				lowerGuess(&guess, &maxGuessesAllowed, &answer, &max, &gameOver, &differential, &numGuessesTaken,
						&last_differential);
			} // end if guess < answer

			// // If the user enters a number equal to the answer
			if(guess == answer) {

				rightGuess(&guess, &answer, &gameOver);

			} // end if guess == answer


		} // end guess loop


		counter = isGameOver(&gameOver, counter);

		// Determining if the game is over
		if(counter == 0) {
			gameOver = false;
		}
		else {
			printf("Goodbye!");
		}

	}
	return 0;
} // end main


/**************************************************************
 * Function name: newGame
 *
 * PURPOSE: This function will receive input for the max guesses allowed and the max
 * number to guess to. Then will generate the random number for answer, set gameOver
 * to false, and set the number of guesses taken to 0;
 *
 ****************************************************************/
void newGame(int *maxGuessesAllowed, int *answer, int *max, bool *gameOver,
			 int *differential, int *numGuessesTaken) {

	printf("How many guesses are allowed? :");
	scanf("%d", maxGuessesAllowed);

	printf("What is the max number you would like to guess to: ");
	scanf("%d", max);

	// random number generation
	*answer = rand() % *max + 1;


	*gameOver = false;

	*differential = *max;

	*numGuessesTaken = 0;

	return;

}

/**************************************************************
 * Function name: guessMethod
 *
 * PURPOSE: This function will take input for the users guess, increase the value of number
 * 			of guesses taken, and determine if the number of guesses taken is greater
 * 			than the number of guesses allowed.
 ****************************************************************/
void guessMethod(int *guess, int *maxGuessesAllowed, int *answer, int *max, bool *gameOver,
				 int *differential, int *numGuessesTaken, int *last_differential) {

		printf("Please enter your guess, (Remember to enter a number from 0 - %d) :", *max);
		scanf("%d", guess);
        printf("Guess: %d.\n", *guess);

        while(*guess > *max) {
			printf("Error, this is out of bounds, (Remember to enter a number from 0 - %d \n) :", *max);
			scanf("%d", guess);
		}

		(*numGuessesTaken)++;

		if(*numGuessesTaken > *maxGuessesAllowed) {

			*gameOver = true;
		}

	//} // end while for maxGuessesAllowed
	return;
}// end guessMethod


/**************************************************************
 * Function name: higherGuess
 *
 * PURPOSE: This function will determine if the user is getting closer or farther when their
 * 			guess is above the answer. This function will also calculate the distance between the
 * 			past guess and current guess and compare them to see which is closer.
 *
 ****************************************************************/
void higherGuess(int *guess, int *maxGuessesAllowed, int *answer, int *max, bool *gameOver,
		 int *differential, int *numGuessesTaken, int *last_differential) {


	if(*numGuessesTaken >= *maxGuessesAllowed) {

		printf("Game over! Max guesses exceeded. \nAnswer was: %d\n", *answer);
		*gameOver = true;

	}

	if(*guess > *answer && *gameOver == false) {

		printf("Too high \n");

		*differential = *guess - *answer;
		if(*numGuessesTaken > 1) {
			if(*differential > *last_differential && *numGuessesTaken > 1) {

				printf("Getting colder \n");

			}

			else {
				printf("Getting warmer \n");
			}
		}
		*last_differential = *guess - *answer;
		numGuessesTaken++;
	}
} // end higherGuess


/**************************************************************
 * Function name: lowerGuess
 *
 * PURPOSE: This function will determine if the user is getting closer or farther when their
 * 			guess is below the answer. This function will also calculate the distance between the
 * 			past guess and current guess and compare them to see which is closer.
 *
 ****************************************************************/
void lowerGuess(int *guess, int *maxGuessesAllowed, int *answer, int *max, bool *gameOver,
		 int *differential, int *numGuessesTaken, int *last_differential) {

	if(*numGuessesTaken >= *maxGuessesAllowed) {

		printf("Game over! Max guesses exceeded.\nAnswer was: %d\n", *answer);
		*gameOver = true;

	}

	if(*guess < *answer && *gameOver == false) {

		printf("Too low \n");

		*differential = *answer - *guess;

		if(*numGuessesTaken > 1) {
			if(*differential < *last_differential) {

				printf("Getting warmer \n");

			}

			else {
				printf("Getting colder \n");
			}
		}
		*last_differential = *answer - *guess;

		numGuessesTaken++;
	}
}


/**************************************************************
 * Function name: rightGuess
 *
 * PURPOSE: This function will congratulate the user for entering the right answer and sets
 *  		gameOver = true, ending the current game.
 *
 ****************************************************************/
void rightGuess(int *guess, int *answer, bool *gameOver) {

	if(*guess == *answer) {

		printf("You are correct! Congratulations!\n");
		*gameOver = true;

			}
}


/**************************************************************
 * Function name: isGameOver
 *
 * PURPOSE: This function will ask the user if they would like to play another game.
 * 			If answered yes, the game loop will restart asking the user how many guesses.
 * 			If answered no, the program will print goodbye and end.
 *
 ****************************************************************/
int isGameOver(bool *gameOver, int counter) {

	printf("Do you want to repeat? Press 0 for yes, and 1 for no: ");
	scanf("%d", &counter);
	return counter;
}

