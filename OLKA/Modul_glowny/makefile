CC = g++
RM = del
CD = cd
ALG = ../Algorytm/

main: main.cpp graf.o wynik.o input.o alg.o IO.o
	$(CC) main.cpp graf.o wynik.o input.o alg.o IO.o -o main
	
alg.o: $(ALG)alg.cpp $(ALG)alg.h
	$(CC) $(ALG)alg.cpp -c -o alg.o
	
graf.o: $(ALG)graf.cpp $(ALG)graf.h
	$(CC) $(ALG)graf.cpp -c -o graf.o
	
wynik.o: $(ALG)wynik.cpp $(ALG)wynik.h
	$(CC) $(ALG)wynik.cpp -c -o wynik.o
	
input.o: input.cpp input.h
	$(CC) input.cpp -c

IO.o: IO.cpp IO.h
	$(CC) IO.cpp -c

clean_o:
	$(RM) *.o
	
clean:
	$(RM) *.o *.exe