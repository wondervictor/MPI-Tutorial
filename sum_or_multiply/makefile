CC=mpicc
objects=main.o sum.o

main: $(objects)
	$(CC) -o main $(objects)

main.o: main.c sum.c
	$(CC) -o main.o -c -g -Wall main.c

sum.o: sum.c
	$(CC) -o sum.o -c -g -Wall sum.c

clean:
	rm $(objects) main

run:
	mpiexec -n 8 main
