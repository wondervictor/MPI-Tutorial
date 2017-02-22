CC=mpicc
objects=main.o sum.o vector_matrix.o

main: $(objects)
	$(CC) -o main $(objects)

main.o: main.c sum.c vector_matrix.c
	$(CC) -o main.o -c -g -Wall main.c

sum.o: sum.c
	$(CC) -o sum.o -c -g -Wall sum.c
vector_matrix.o: vector_matrix.c
	$(CC) -o vector_matrix.o -c -g -Wall vector_matrix.c


clean:
	rm $(objects) main

run:
	mpiexec -n 8 main
