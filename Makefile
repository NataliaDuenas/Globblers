# gcc main_example.c board.o -o gobblers

main : main_example.o board.o
	gcc main_example.o board.o -o main
# El ejecutable `main` se crea enlazando los objetos main.o y aff.o

main_example.o : main_example.c 
	gcc -o main_example.o -c main_example.c

clean :
	rm *.o
