#ifndef MINE_SWEEPER_H
#define MINE_SWEEPER_H
enum Visibility {REVEALED, CONCEALED, MARKED, QUESTIONED};
 
typedef struct TILE_STRUCT{
	int mine;
	int num_surronding_mine;
	enum Visibility visibility;
} Tile;

typedef struct BOARD_STRUCT{
	int numRows;
	int numCols;
	int numMines;
	int rowPlay;
	int colPlay;
	int action;
	Tile** tile;
	int* numMinesLeft;
} sweeper;
#endif