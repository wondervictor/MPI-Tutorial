CC=mpicc
objects=main.o

main: $(objects)
	$(CC) -o main $(objects)

main.o: main.c
	$(CC) -o main.o -c -g -Wall main.c

clean:
	rm $(objects) main

run:
	mpiexec -n 64 main
