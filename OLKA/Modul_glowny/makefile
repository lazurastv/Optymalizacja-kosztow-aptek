CC = g++
RM = del

main: main.cpp input.o IO.o
	$(CC) main.cpp input.o IO.o -o main

input.o: input.cpp input.h
	$(CC) input.cpp -c

IO.o: IO.cpp IO.h
	$(CC) IO.cpp -c
	
clean:
	$(RM) *.o *.exe