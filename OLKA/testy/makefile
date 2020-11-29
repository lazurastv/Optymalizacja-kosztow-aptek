CXX = g++
CXXFLAGS = -std=c++17
RM = del
MOD = ../OLKA/Modul_glowny/
ALG = ../OLKA/Algorytm/

all: input_test IO_test graf_test alg_test

input_test: input_test.cpp
	$(CXX) input_test.cpp $(MOD)input.cpp -o bin/input_test
	
IO_test: IO_test.cpp
	$(CXX) $(CXXFLAGS) IO_test.cpp $(MOD)IO.cpp $(MOD)input.cpp -o bin/IO_test
	
graf_test: graf_test.cpp
	$(CXX) graf_test.cpp $(ALG)graf.cpp $(MOD)input.cpp -o bin/graf_test
	
alg_test: alg_test.cpp
	$(CXX) alg_test.cpp $(ALG)alg.cpp $(ALG)graf.cpp $(ALG)wynik.cpp -o bin/alg_test
	
clean:
	$(RM) bin