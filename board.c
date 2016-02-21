#include <stdio.h>
#include <stdlib.h>
#include "mine_sweeper.h"
#include "board.h"

//Function takes in three parameters and creates a board thats a sweeper type
sweeper createBoard(int numRows, int numCols, int numMines){
	//Declaration of variables
	int i;
	int j; 
	sweeper board;

//Sets the structure variable to the number inputed by the user
	board.numRows = numRows; 
	board.numCols = numCols;
	board.numMines = numMines; 

//Creates 2d matrix of type tile because of the two structs
	board.tile = (Tile**)malloc(numRows*sizeof(Tile*));
	for(i = 0; i < numRows; i++){ 	
		board.tile[i] = (Tile*)malloc(numCols*sizeof(Tile));
	}
	for(i = 0; i < numRows; i++){ 
		for(j = 0; j < numCols; j++){
			//Sets the initial condition as concealed
			board.tile[i][j].visibility = CONCEALED;
		}
	}
	//Stores the number of mines inside
	board.numMinesLeft = (int*)malloc(sizeof(int)*1);
	board.numMinesLeft[0] = numMines; 
	
	return board;
}
//Function takes in one argument which is the board
void printBoard(sweeper board){
	//Declaration of variables
	int i; 
	int j;
	//For loop to iterate through the rows and columns
	for (i = 0; i < board.numRows; i++){  
		printf("%d ", board.numRows - i - 1); 
		for (j = 0; j < board.numCols; j++){
		//Sets the condition for when to set the tile as revealed 
			if(board.tile[i][j].visibility== REVEALED){
				if(board.tile[i][j].mine == 1){ 
					printf("* ");
				}
				else{
					printf("%d ", board.tile[i][j].num_surronding_mine); 
				}
			}
			//Sets condition to when to make it concealed
			else if (board.tile[i][j].visibility== CONCEALED){
				printf("# ");
			}
			//Sets condition for when to make it marked
			else if(board.tile[i][j].visibility == MARKED){  
				printf("! ");
			}
			//Sets the condition to question 
			else if(board.tile[i][j].visibility == QUESTIONED){ 
				// If the user uses the question option, it prints a question mark 
				printf("? ");
			}
		}
		printf("\n");
	}
	
	// Prints numbers out underneath the board. 
	printf("  ");
	for (i = 0; i < board.numCols; i++){
		printf("%d ", i);
	}
	printf("\n");
}
//Takes in 3 arguments and generates minds based off user input/random num generator
void generateMines(sweeper board, int argc, char** argv){
	//Declaration of variables
	int randRow; 
	int randCol;
	int i;
	int j; 
	int counter = 0;
	int k;
	k = board.numRows - 1;
	
	srand(atoi(argv[4]));
	
	//Create loop that sets each tile's mine num to 0
	for(i = 0; i < board.numRows; i++) { 
		for(j = 0; j < board.numCols; j++){
			board.tile[i][j].mine = 0;
		}
	}

//Generates mines as long as it is less than the number of mines entered. 
	while (counter < board.numMines) { 
		// Generates a random row and column
		randRow = rand()%board.numRows; 
		randCol = rand()%board.numCols;	


		if(board.tile[k - randRow][randCol].mine == 0){ 
			printf("Placing mine at %d, %d\n", randRow, randCol);
			if (board.numRows == 1) {
				board.tile[randRow][randCol].mine = 1; 
				counter++; 
			}
			else {
				//Inverts the number of rows
				board.tile[k - randRow][randCol].mine = 1; 
				counter++; 
			}
			
		}
	}
}
//If the user wins the whole board is displayed and takes in one parameter
void displayBoard(sweeper board){
	//Declaration of variables
	int i;
	int j;

	// This iterates through the board and reveals all the tiles 
	for(i = 0; i < board.numRows; i ++){
		for(j = 0; j < board.numCols; j++){
			board.tile[i][j].visibility = REVEALED;
		}
	}


	printBoard(board);
}
//Takes in one parameter and generates numbers on the board based on the amount of mines near it
void generateNums(sweeper board){
	//Declaration of variables
	int i = 0;
	int j = 0;
	int numMines = 0;
	//Sets condition for if the row=1
	if (board.numRows == 1) { 
		if(board.tile[i][j].mine == 1) { 
			numMines++; 
		}
		else {
			// Variable is incremented if there is a mine next to it. 
			if (board.tile[i][j +1].mine == 1) {
				numMines++; 
			}
			
			board.tile[i][j].num_surronding_mine = numMines;
			//Variable set to number of mines around it.
			return;
		}
	}

	// Iterateing through numRows and columns to check the number of mines around that tile
	//Sets conditions so the check doesnt go off the board and segfault
	for(i = 0; i < board.numRows; i++){ 
		numMines = 0; 
		for(j = 0; j < board.numCols; j++){
			numMines = 0; 
			if(board.tile[i][j].mine == 1){ 
				if(j <= board.numCols - 1){ 
					continue;
				}
				else{
					break; 
				}
			}
			// Checks the diagonal and increments the variable if a mine exists
			else if(i == 0 && j == 0){
				if(board.tile[i][j + 1].mine == 1){ 
					numMines++;
				}
				if(board.tile[i + 1][j + 1].mine == 1){ 
	 				numMines++;
				}
				if(board.tile[i + 1][j].mine == 1){ 
					numMines++;
				}
				
				//Assigns numMines to tile [i][j]
				board.tile[i][j].num_surronding_mine = numMines; 
			}
		
		//Other diagonal is checked
	else if(i == 0 && j == board.numCols - 1){
				if(board.tile[i + 1][j].mine == 1){ 
					numMines++;
				}
				if(board.tile[i + 1][j - 1].mine == 1){ 
				}
				if(board.tile[i][j - 1].mine == 1){ 
					numMines++;
				}
				
				
				board.tile[i][j].num_surronding_mine = numMines; 
			}
//Third diagonal is checked
			else if(i == board.numRows - 1 && j == 0){
				if(board.tile[i - 1][j + 1].mine == 1){ 
					numMines++;
				}
				if(board.tile[i - 1][j].mine == 1){ 
					numMines++;
				}
				if(board.tile[i][j + 1].mine == 1){ 
					numMines++;
				}
				
				board.tile[i][j].num_surronding_mine = numMines; 
			}
			// Last diagonal checked. and numMines is added
			else if(i == board.numRows - 1 && j == board.numCols - 1){ 
				if(board.tile[i][j - 1].mine == 1){ 
					numMines++;
				}
				if(board.tile[i - 1][j].mine == 1){ 
					numMines++;
				}
				if(board.tile[i - 1][j - 1].mine == 1){ 
					numMines++;
				}
				// set numMines to right tile
				board.tile[i][j].num_surronding_mine = numMines; 
			}
			//Check for last column
			else if(j == board.numCols - 1 && (i != 0 || i != board.numRows - 1)){
				if(board.tile[i - 1][j].mine == 1){
					numMines++;
				}
				if(board.tile[i - 1][j - 1].mine == 1){
					numMines++;
				}
				if(board.tile[i][j - 1].mine == 1){
					numMines++;
				}
				if(board.tile[i + 1][j].mine == 1){
					numMines++;
				}
				if(board.tile[i + 1][j - 1].mine == 1){
					numMines++;
				}
				board.tile[i][j].num_surronding_mine = numMines; 
			}
			//tile above are checked. and numMines is added if theres a mine.
			else if(i == 0 && (j != 0 || j != board.numCols - 1)){
				if(board.tile[i + 1][j].mine == 1){ 
					numMines++;
				}
				
				if(board.tile[i + 1][j + 1].mine == 1){ 
					numMines++;
				}
				if(board.tile[i + 1][j - 1].mine == 1){ 
					numMines++;
				}
				if(board.tile[i][j - 1].mine == 1){ 
					numMines++;
				}
				if(board.tile[i][j + 1].mine == 1){ 
					numMines++;
				}
				board.tile[i][j].num_surronding_mine = numMines; 
			}
			else if(j == 0 && (i != 0 || i != board.numRows - 1)){
				if(board.tile[i - 1][j].mine == 1){ 
					numMines++;
				}
				
				if(board.tile[i - 1][j + 1].mine == 1){
					numMines++;
				}
				if(board.tile[i][j + 1].mine == 1){
					numMines++;
				}
				if(board.tile[i + 1][j + 1].mine == 1){
					numMines++;
				}
				if(board.tile[i + 1][j].mine == 1){
					numMines++;
				}
				board.tile[i][j].num_surronding_mine = numMines; 
			}
			// The else if statement checks all of the directions it can go. 
			else if(i == board.numRows - 1 && (j != 0 || j != board.numCols - 1)){
				if(board.tile[i][j - 1].mine == 1){ 
					numMines++;
				}
				if(board.tile[i][j + 1].mine == 1){
					numMines++;
				}
				if(board.tile[i - 1][j].mine == 1){
					numMines++;
				}
				if(board.tile[i - 1][j - 1].mine == 1){
					numMines ++;
				}
				if(board.tile[i - 1][j + 1].mine == 1){
					numMines++;
				}
				board.tile[i][j].num_surronding_mine = numMines; 
			}
			
			// Checks all the rest of the tile not in the first columns/numRows/corners
			else{ 
				
				if(board.tile[i - 1][j].mine == 1){
					numMines++; 
				}
				if(board.tile[i - 1][j - 1].mine == 1){
					numMines++;
				}
				if(board.tile[i - 1][j + 1].mine == 1){
					numMines++;
				}
				if(board.tile[i + 1][j].mine == 1){
					numMines++;
				}
				
				if(board.tile[i + 1][j - 1].mine == 1){
					numMines++;
				}
				
				if(board.tile[i + 1][j + 1].mine == 1){
					numMines++;
				}
				if(board.tile[i][j + 1].mine == 1){
					numMines++;
				}
				if(board.tile[i][j - 1].mine == 1){
					numMines++;
				}
				board.tile[i][j].num_surronding_mine = numMines; 
			}
		}
	}
}

