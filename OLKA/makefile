CC = g++
RM = del
ALG = Algorytm/
MOD = Modul_glowny/
O = object/

main: $(MOD)main.cpp $(O)input.o $(O)IO.o $(O)alg.o $(O)graf.o $(O)wynik.o
	$(CC) $(MOD)main.cpp $(O)input.o $(O)IO.o $(O)alg.o $(O)graf.o $(O)wynik.o -o main
	
$(O)input.o: $(MOD)input.cpp $(MOD)input.h
	$(CC) $(MOD)input.cpp -c -o $(O)input.o
	
$(O)IO.o: $(MOD)IO.cpp $(MOD)IO.h
	$(CC) $(MOD)IO.cpp -c -o $(O)IO.o

$(O)alg.o: $(ALG)alg.cpp $(ALG)alg.h
	$(CC) $(ALG)alg.cpp -std=c++11 -c -o $(O)alg.o
	
$(O)graf.o: $(ALG)graf.cpp $(ALG)graf.h
	$(CC) $(ALG)graf.cpp -c -o $(O)graf.o
	
$(O)wynik.o: $(ALG)wynik.cpp $(ALG)wynik.h
	$(CC) $(ALG)wynik.cpp -c -o $(O)wynik.o

clean:
	$(RM) object