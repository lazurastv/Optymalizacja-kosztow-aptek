CC = g++
RM = del
RMFLAG = /S
CD = cd
ALG = ../Algorytm/

main: main.cpp $(ALG)graf.o input.o IO.o
	$(CC) main.cpp $(ALG)graf.o input.o IO.o -o main
	
graf.o: $(ALG)graf.cpp $(ALG)graf.h
	$(CC) $(ALG)graf.cpp -c
	
input.o: input.cpp input.h
	$(CC) input.cpp -c

IO.o: IO.cpp IO.h
	$(CC) IO.cpp -c

clean:
	$(CD) ../
	$(RM) *.o *.exe $(RMFLAG)