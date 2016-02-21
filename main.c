#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mine_sweeper.h"
#include "board.h"
#include "play.h"
 
//Function that takes in the number of arguments
void read_args(int argc){
// Makes sure the arguments is not less than 4
	if (argc < 4){ 
		//If it is less than four, the usage message prints, then the program exits
		printf("Not enough arguments. Usage: ./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
		exit(0);
	}
	
	else if (argc > 5){ 
		// If there are too many arguments, usage message prints and exits. 
		printf("Too many arguments. Usage: ./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
		exit(0);
	}
}

int main(int argc, char** argv){
//Declaration of variables
	int numRows, numCols, numMines; 
	sweeper board;
//reads in arguments.
	read_args(argc);
	
//Reads in the arguments and converts them into integers
	numRows = atoi(argv[1]);
	numCols = atoi(argv[2]);
	numMines = atoi(argv[3]);
	
//Creates a board under the sweeper structure
	board = createBoard(numRows, numCols, numMines);
//Generates mines on the board
	generateMines(board, argc, argv);

//Counts the number of mines around each tile and updates the board with that number
	generateNums(board);

//Plays the game
	playGame(board);
	

	return 0;
}
