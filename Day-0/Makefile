
all: bin
	@mpirun -np 6 ./bin

bin: main.c main.h
	@mpicc main.c -o bin

clean:
	@rm bin
