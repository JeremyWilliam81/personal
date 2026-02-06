#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Prototypes
int Adjacent(int tolerance, int point, int value);


/*_________________________________________________________________________________________________________________________
CHANGE LOG
-11/19/2024
	-Lines 126-140 I left stuff for big open but didn't have time to finish
	-Changed the indexing, fixing all the stupid -1's and whatnot
	-Had to change some bound things in the statements of bombs counters so the edge tiles worked
	-Added a difficulty value, so if we wanted to change the amount of bombs we can just change that, but I kept it at the 2 we were using
	-Added this cool box for describing all the changes we made for the other person
	-I'm saving what I know works as the Minesweeper.c and when I start making more changes I do them in Minesweeper_copy.c so I don't mess anything up horribly
		-Once the copy works 100% I just overwrite the original to make sure both are up to date



	-I'm thinking we make an array for count as well, use that to implement new idea for opening all 0 count tiles
	-I did it, and it works, but it needs to open up all the 0's it connects to and the only thing I can think of is a lottttt of if statements or loops
	-Also new idea was given by friend who plays minesweeper a lot, apparently the big open isn't just at the start, its just if you click a tile with no bombs around it, 
	it opens up all other tiles adjacent to it that also have 0 counts. And that just keeps chaining until it hits some tile with a number in the count, so that's what I'm working on




____________________________________________________________________________________________________________________________*/
int main(){
	printf("Welcome to Minesweeper\n");
	int userinputrow;
	int userinputcol;
	int endgame = 0;
	int count = 0;
	int difficulty = 5;
	
	int arrayRow = 12;
	int arrayCollumn = 14;
	char displayArray[arrayRow][arrayCollumn];
	int gameArray[arrayRow][arrayCollumn];
	int countArray[arrayRow][arrayCollumn];
	srand(time(0));
	
	for(int i = 0; i < arrayRow; i++){
		for(int j = 0; j < arrayCollumn; j++){
			gameArray[i][j] = rand() % 100;
		}
	}
	
	/*Initialize every place in the display array with #,
	(for some reason the box didn't work but if you can get it to it probably looks better)*/
	for(int i = 0; i < arrayRow; i++){
		for(int j = 0; j < arrayCollumn; j++){
			displayArray[i][j] = '☐';
		}
	}
	
	for(int j = 0; j < arrayCollumn; j++){
			if(j == arrayCollumn - 1){
				printf(" %d \n", j);
			}else if(j == 0){
				printf("  %d ", j);
			}else if(j > 8){
				printf(" %d", j);	
			}else{
				printf(" %d ", j);
			}
	}
	for(int i = 0; i < arrayRow; i++){
		for(int j = 0; j < arrayCollumn; j++){
			count = 0;
				if (i + 1 < arrayRow && gameArray[i + 1][j] <= difficulty) {
					count++;
				}
				if (i + 1 < arrayRow && j + 1 < arrayCollumn && gameArray[i + 1][j + 1] <= difficulty) {
					count++;
				}
				if (j + 1 < arrayCollumn && gameArray[i][j + 1] <= difficulty) {
					count++;
				}
				if (i - 1 >= 0 && gameArray[i - 1][j] <= difficulty) {
					count++;
				}
				if (i - 1 >= 0 && j - 1 >= 0 && gameArray[i - 1][j - 1] <= difficulty) {
					count++;
				}
				if (j - 1 >= 0 && gameArray[i][j - 1] <= difficulty) {
					count++;
				}
				if (i + 1 < arrayRow && j - 1 >= 0 && gameArray[i + 1][j - 1] <= difficulty) {
					count++;
				}
				if (i - 1 >= 0 && j + 1 < arrayCollumn && gameArray[i - 1][j + 1] <= difficulty) {
					count++;
				}
			countArray[i][j] = count;
		}
	}
	//NEW PRINTING DISPLAY CODE
	for(int i = 0; i < arrayRow; i++){
		printf("%d",i);
		if(i <= 9){
			printf(" ");
		}
		for(int j = 0; j < arrayCollumn; j++){
			printf("%c  ", displayArray[i][j]);
		}
		printf("\n");
	}

	/* PREVIOUS PRINTING DISPLAY CODE
	for(int i = 0; i < arrayRow; i++){
		for(int j = 0; j < arrayCollumn; j++){
			if(j == arrayCollumn-1){
				printf(" ☐ \n");
			}else if(j == 0){
				printf("%d ☐ ", i+1);
			}
			else{
				printf(" ☐ ");
			}
		}
	}/*

	//Next lines for visualizing bombs
	/*for(int i = 0; i <= arrayRow; i++){
		for(int j = 0; j <= arrayCollumn; j++){
			if(j == arrayCollumn){
				printf(" gameArray[i][j] \n");
			}else{
				printf(" gameArray[i][j] ");
			}
		}
	}*/

	printf("Make your guess\n");
	
	while(endgame == 0){
		
		scanf("%d", &userinputrow);
		scanf("%d", &userinputcol);

		/*for(int i = 0; i < arrayRow; i++){
			for(int j = 0; j < arrayCollumn; j++){
				if(j == arrayCollumn-1){
					printf(" ☐ \n");
				}else if(j == 0){
					printf("%d ☐ ", i);
				}
				else if(i == userinputrow && j == userinputcol){
					printf(" %d ", count);
				}
				else{
					printf(" ☐ ");
				}
			}
		}*/
		
		//This my idea for big open start, just don't know how to print it bc I'm not entirely sure how the display array works
		//If you can, my idea was to print the count of all the tiles that =11, since it will only be these ones, and I changed the normal count so that it won't count at values above 10, so like this should work probably
		/*int gamestart = 0;
		int open_size = 3;
		while (gamestart == 0) {
			for (int i = -open_size; i <= open_size; i++) {
				for (int j = -open_size; j <= open_size; j++) {
					if (abs(i) + abs(j) <= open_size) {
						if (userinputrow + i >= 0 && userinputrow + i < arrayRow && userinputcol + j >= 0 && userinputcol + j < arrayCollumn) {
							gameArray[userinputrow + i][userinputcol + j] = 11;
							gamestart = 1;
						}
					}
				}
			}
			if (gamestart == 1) {
				break;
			}
		}*/


		if(gameArray[userinputrow][userinputcol] > difficulty){
			endgame = 0;
			printf("Safe!\n");
			system("clear");
		
			//set the location of the choice to the number (as a character) of bombs adjacent (using ASCII table)
			/*if(countArray[userinputrow][userinputcol] == 0){
				for(int i = 0; i < 1000; i++){
					displayArray[userinputrow][userinputcol] = (char) (countArray[userinputrow][userinputcol]) + 48;
					displayArray[userinputrow + 1][userinputcol] = (char)(countArray[userinputrow + 1][userinputcol]) + 48;
					displayArray[userinputrow][userinputcol + 1] = (char)(countArray[userinputrow][userinputcol + 1]) + 48;
					displayArray[userinputrow - 1][userinputcol] = (char)(countArray[userinputrow - 1][userinputcol]) + 48;
					displayArray[userinputrow][userinputcol - 1] = (char)(countArray[userinputrow][userinputcol - 1]) + 48;
				}
					displayArray[userinputrow][userinputcol] = (char) (countArray[userinputrow][userinputcol]) + 48;
					displayArray[userinputrow + 1][userinputcol] = (char)(countArray[userinputrow + 1][userinputcol]) + 48;
					displayArray[userinputrow][userinputcol + 1] = (char)(countArray[userinputrow][userinputcol + 1]) + 48;
					displayArray[userinputrow - 1][userinputcol] = (char)(countArray[userinputrow - 1][userinputcol]) + 48;
					displayArray[userinputrow][userinputcol - 1] = (char)(countArray[userinputrow][userinputcol - 1]) + 48;
			}
			else{
				displayArray[userinputrow][userinputcol] = (char)(countArray[userinputrow][userinputcol]) + 48;
			}*/
			for(int i = 0; i < arrayRow; i++){
				if(countArray[userinputrow + i][userinputcol + i] == 0){
					displayArray[userinputrow][userinputcol] = (char) (countArray[userinputrow][userinputcol]) + 48;
					displayArray[userinputrow + i][userinputcol] = (char)(countArray[userinputrow + 1][userinputcol]) + 48;
					displayArray[userinputrow][userinputcol + i] = (char)(countArray[userinputrow][userinputcol + 1]) + 48;
					displayArray[userinputrow - i][userinputcol] = (char)(countArray[userinputrow - 1][userinputcol]) + 48;
					displayArray[userinputrow][userinputcol - i] = (char)(countArray[userinputrow][userinputcol - 1]) + 48;
				}else{
				displayArray[userinputrow][userinputcol] = (char)(countArray[userinputrow][userinputcol]) + 48;
				}
			}
			
			//printing the top numbers again
			for(int j = 0; j < arrayCollumn; j++){
				if(j == arrayCollumn - 1){
					printf(" %d \n", j);
				}else if(j == 0){
					printf("  %d ", j);
				}else if(j > 8){
					printf(" %d", j);
				}else{
					printf(" %d ", j);
				}
			}
			
			//printing side numbers and the display
			for(int i = 0; i < arrayRow; i++){
				printf("%d",i);
				if(i <= 9){
					printf(" ");
				}
				for(int j = 0; j < arrayCollumn; j++){
					printf("%c  ", displayArray[i][j]);
				}
				printf("\n");
			}
			
			/* PREVIOUS PRINTING DISPLAY CODE
			for(int j = 0; j < arrayCollumn; j++){
				if(j == arrayCollumn - 1){
					printf(" %d \n", j+1);
				}else if(j == 0){
					printf("  %d ", j+1);
				}else{
					printf(" %d ", j+1);
				}
			}
			
			for(int i = 0; i < arrayRow; i++){
				for(int j = 0; j < arrayCollumn; j++){
					if(j == arrayCollumn - 1){
						printf(" ☐ \n");
					}else if(i == userinputrow -1 && j == userinputcol -1){
						printf(" %d ", count);
					}else if(j == 0){
						printf("%d ☐ ", i+1);
					}else{
						printf(" ☐ ");
					}
				}
			}*/
		}else{
			endgame = 1;
			printf("BOMB\n");
		}
	}

	
	
	
	
	
	
	return 0;
}

//Functions
//Using close to from lab 5 to implement adjacent identifier, still working on it
int Adjacent(int tolerance, int point, int value){
	if(value >= (point - tolerance) && value <= (point + tolerance)){
		return 1;
	}else{
		return 0;
	}
}
