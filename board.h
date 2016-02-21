#ifndef BOARD_H
#define BOARD_H

sweeper createBoard(int numRows, int numCols, int numMines);
void generateMines(sweeper board, int argc, char** argv);
void generateNums(sweeper board);
void printBoard(sweeper board);
void displayBoard(sweeper board);

#endif
