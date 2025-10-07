all: bin
	@mpirun -np 6 ./bin 12

bin: main.c main.h
	@mpicc main.c -o  bin

clean:
	@rm bin