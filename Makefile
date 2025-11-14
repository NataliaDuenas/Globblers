# gcc main_example.c board.o -o gobblers

main : main_example.o board.o Display.o
	gcc main_example.o board.o Display.o -o main
# El ejecutable `main` se crea enlazando los objetos main.o y aff.o

main_example.o : main_example.c Display.h
	gcc -o main_example.o -c main_example.c

Display.o: Display.c Display.h
	gcc -c Display.c

clean :
	rm *.o
