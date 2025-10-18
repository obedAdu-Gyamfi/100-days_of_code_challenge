all: bin
	@mpirun -np 6 ./bin 100


bin: main.c main.h
	@mpicc main.c -o bin

clean:
	@rm bin