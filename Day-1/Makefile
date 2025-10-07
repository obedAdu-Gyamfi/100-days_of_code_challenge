
all: bin
	@mpirun -np 6 ./bin

bin: main.o
	@mpicc -o bin main.o

main.o: main.c main.h
	@mpicc -c main.c

clean:
	@rm -f bin main.o
