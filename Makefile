main: main.o Display.o board.o cell.o
	g++ main.o Display.o board.o cell.o -o main


main.o: main.cpp Display.h board.h enums.h
	g++ -c main.cpp


Display.o: Display.cpp Display.h board.h enums.h
	g++ -c Display.cpp


board.o: board.cpp board.h cell.h piece.h enums.h
	g++ -c board.cpp


cell.o: cell.cpp cell.h piece.h enums.h
	g++ -c cell.cpp


clean:
	rm -f *.o main
