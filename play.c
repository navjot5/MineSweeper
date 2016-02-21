#include <stdio.h>
#include <stdlib.h>
#include "mine_sweeper.h"
#include "board.h"
#include "play.h"

//Function that takes in one parameter and starts the game
void playGame(sweeper board){
	//Creates a while loop until the game is over
	while(winCondition(board) == 0){
		printf("There are %d mines left\n", board.numMinesLeft[0]); 
		printBoard(board); 
		getPlay(board); 
	}
	//If you win the board gets displayed
	displayBoard(board); 
	printf("You Won!!\n");  
	exit(0);
}
//Function that makes sure that the user input is within the board
int validPlay(sweeper board, int rowPlay) {
	//Sets the check condition
	if((rowPlay > board.numRows - 1) ||(board.colPlay < 0) ||(board.colPlay > board.numCols - 1)  || (rowPlay < 0)) { 
		return 0;
	}
	//Sets the condition for if the user picks a tile thats already revealed
	else if(board.tile[board.rowPlay][board.colPlay].visibility == REVEALED){
		printf("This tile is already revealed.\n"); 
		return 0;
	} 
	return 1;
}
//This function gets a play from the user and takes the sweeper board as one parameter
void getPlay(sweeper board){
	//Declaration of variables
	int rowPlay;
	int colPlay; 

	//Inverts the points
	int row_at_zero = board.numRows - 1; 

	//Asks user for input
	printf("Enter row a row between 0-%d and a column between 0-%d: ", board.numRows - 1, board.numCols - 1);
	scanf("%d %d", &rowPlay, &colPlay); 
	if (board.numRows == 1) { 
		board.rowPlay = rowPlay; 
		board.colPlay = colPlay;
	}
	else {
		// Inverts the coordinates
		board.rowPlay = row_at_zero - rowPlay; 
		board.colPlay = colPlay;
	}
	// Prints a message asking user to input coordinates. 
	while (validPlay(board, rowPlay) == 0){
		printf("Enter row a row between 0-%d and a column between 0-%d: ", board.numRows - 1, board.numCols - 1);
		scanf("%d %d", &rowPlay, &colPlay);
		if (board.numRows == 1) { 
			board.rowPlay = rowPlay;
			board.colPlay = colPlay;
		}
		else {
			board.rowPlay = row_at_zero - rowPlay;
			board.colPlay = colPlay;
	}
	}
	//After the play is valid, run it through the receive action function
	receiveAction(board); 
}
//Function that takes in the board as a parameter and then brings up the menu based on where that play lands
void receiveAction(sweeper board){
	//Declaration of variables
	int action;

	// If the visibility is hidden, then it presents a set of options for the users. 
	if(board.tile[board.rowPlay][board.colPlay].visibility == CONCEALED) { 
		printf("Enter Action\n0. Reveal\n1. Question\n2. Mark\n3. Cancel\nAction: "); 
		scanf("%d", &action);
		if(action > 3 || action < 0){ 
			getPlay(board);
		}
		else{
			board.action = action;
			receiveMove(board);
		}
	}
	//If its marked, bring up a list of choices
	else if (board.tile[board.rowPlay][board.colPlay].visibility == MARKED) { // If the tile is already marked, these options will be presented. 
		printf("Enter Action\n0. Reveal\n1. Question\n2. Mark\n3. Cancel\nAction: ");
		scanf("%d", &action);
		board.action = action;
		receiveMove(board);
	}
	//If questioned,bring up a list of choices
	else if (board.tile[board.rowPlay][board.colPlay].visibility == QUESTIONED) { // If the user decides to question the tile, a set of options will be presented. 
		printf("Enter Action\n0. Reveal\n1. Question\n2. Mark\n3. Cancel\nAction: ");
		scanf("%d", &action);
		board.action = action;
		receiveMove(board);
	}
}

//Takes in the action from the user
void receiveMove(sweeper board){
	//Sets the condition for if the tile chosen is concealed
	if(board.tile[board.rowPlay][board.colPlay].visibility == CONCEALED){
		//Sets the condition for what number the user picked
		if(board.action == 0){
			illuminateTiles(board, board.rowPlay, board.colPlay);
		}
		else if(board.action == 1){
			board.tile[board.rowPlay][board.colPlay].visibility = QUESTIONED; 
		}
		else if(board.action == 2){
			board.numMinesLeft[0] -= 1; 
			board.tile[board.rowPlay][board.colPlay].visibility = MARKED; 
		}
		else if(board.action == 3){
			getPlay(board);
		}
	}
	//Creates condition for if the selected tile on the board is marked
	else if (board.tile[board.rowPlay][board.colPlay].visibility == MARKED) { 
		//Sets condition depending  on what number was entered
		if(board.action == 0){
			board.numMinesLeft[0] += 1; 
			board.tile[board.rowPlay][board.colPlay].visibility = CONCEALED;
		}
		else if(board.action == 1){ 
			getPlay(board);
		}
	}
	//Creates condition for if the tile chosen is questioned
	else if (board.tile[board.rowPlay][board.colPlay].visibility == QUESTIONED) { 
		//Depending on choice
		if(board.action == 0){
			board.tile[board.rowPlay][board.colPlay].visibility = CONCEALED; 
		}
		else if(board.action == 1){
			getPlay(board); 
		}
	}
	
}


//Function that illuminates all the tiles in the board
void illuminateTiles(sweeper board, int i, int j) {
	
	//If the user reveals  a mine, the "You Lost" message pops up and the program exits. 
	if(board.tile[i][j].mine == 1){ 
		displayBoard(board); 
		printf("You Lost :(\n");
		exit(0);
	}

	// It is revealed if there are no mines on the selected tile. 
	if(board.tile[i][j].num_surronding_mine != 0){ 
		board.tile[i][j].visibility = REVEALED;
		return;
	}
	
	board.tile[i][j].visibility = REVEALED; 
	
// Makes sure that the surrounding tile are in bounds
	if(i + 1 < board.numRows && board.tile[i + 1][j].visibility == CONCEALED){ 
		if(board.tile[i + 1][j].num_surronding_mine >= 0) {
			illuminateTiles(board, i + 1, j); 
		}
	}
	if(i + 1 < board.numRows && j + 1 < board.numCols && board.tile[i + 1][j + 1].visibility == CONCEALED){
		if(board.tile[i + 1][j + 1].num_surronding_mine >= 0){
			illuminateTiles(board, i + 1, j + 1); 
		}
	}
	// Checks diagonal
	if(i + 1 < board.numRows && j - 1 >= 0 && board.tile[i + 1][j - 1].visibility == CONCEALED){ 
		if(board.tile[i + 1][j - 1].num_surronding_mine >= 0){
			illuminateTiles(board, i + 1, j - 1);
		}
	}
	if(j + 1 < board.numCols && board.tile[i][j + 1].visibility == CONCEALED){ 
			if(board.tile[i][j + 1].num_surronding_mine >= 0){
				illuminateTiles(board, i, j + 1); 
			}
		}
	if(i - 1 >= 0 && board.tile[i - 1][j].visibility == CONCEALED){ 
		if(board.tile[i - 1][j].num_surronding_mine >= 0){
			illuminateTiles(board, i - 1, j); 
		}
	}
// CHecks the boundaries
	if(j - 1 >= 0 && board.tile[i][j -1].visibility == CONCEALED){ 
		if(board.tile[i][j - 1].num_surronding_mine >= 0){
			illuminateTiles(board, i, j - 1); 
		}
	}
	
// Checks boundaries
	if(i - 1 >= 0 && j + 1 < board.numCols && board.tile[i - 1][j + 1].visibility == CONCEALED){
		if(board.tile[i - 1][j + 1].num_surronding_mine >= 0){
			illuminateTiles(board, i - 1, j + 1); 
		}
	}
// CHecks diagonal
	if(i - 1 >= 0 && j - 1 >= 0 && board.tile[i - 1][j - 1].visibility == CONCEALED){ 
		if(board.tile[i - 1][j - 1].num_surronding_mine >= 0){
			illuminateTiles(board, i - 1, j - 1); 
		}
	}
}

//Function that checks if the user won the game. 
int winCondition(sweeper board) {
	//Declaration of variables
	int i;
	int j;
	int counter = 0;
	int counter2 = 0;
	int counter3 = 0;
	//Loops through the number of rows and columns to see if the mine was marked by the user
	for(i = 0; i < board.numRows; i++){
		for(j = 0; j < board.numCols; j++){ 
			if(board.tile[i][j].mine == 1 && board.tile[i][j].visibility == MARKED){
				counter++;
				if(counter== board.numMines){
					 counter3++; 
				}
			}
			//Checks to see if all the boards are revealed
			if(board.tile[i][j].visibility == REVEALED){
				counter2++; 
				if(counter2 == (board.numRows * board.numCols - board.numMines)){
				 
					counter3++;
				}
			}
		}
	}
	//If both of the variables are incremented, then the game is won, and 1 is returned. 
	if(counter3 == 2){ 
		return 1;
	}
	
	return 0;
}
