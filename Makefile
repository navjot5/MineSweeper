mine_sweeper.out: main.o board.o mine_sweeper.o play.o
	gcc main.o board.o mine_sweeper.o play.o -o mine_sweeper.out
main.o: main.c board.c board.h mine_sweeper.c mine_sweeper.h play.c play.h
	gcc -Wall -c main.c
board.o: board.c board.h
	gcc -Wall -c board.c
mine_sweeper.o: mine_sweeper.c mine_sweeper.h
	gcc -Wall -c mine_sweeper.c
play.o: play.c play.h
	gcc -Wall -c play.c
clean:
	rm *.o mine_sweeper.out


