#ifndef PLAY_GAME_H
#define PLAY_GAME_H

void playGame(sweeper board);
void receiveMove(sweeper board);
void getPlay(sweeper board);
int validPlay(sweeper board, int rowPlay);
void receiveAction(sweeper board);
void illuminateTiles(sweeper board, int i, int j);
int winCondition(sweeper board);

#endif
