CC = g++
RM = del
MOD = ../OLKA/Modul_glowny/
ALG = ../OLKA/Algorytm/

main: input_test IO_test graf_test

input_test: $(MOD)input.cpp $(MOD)input.h input_test.cpp
	$(CC) input_test.cpp $(MOD)input.cpp -o input_test
	
IO_test: $(MOD)IO.cpp $(MOD)IO.h IO_test.cpp
	$(CC) IO_test.cpp -std=c++17 $(MOD)input.cpp $(MOD)IO.cpp -o IO_test
	
graf_test: $(MOD)input.cpp $(MOD)input.h $(ALG)graf.cpp $(ALG)graf.h
	$(CC) graf_test.cpp $(MOD)input.cpp $(ALG)graf.cpp -o graf_test