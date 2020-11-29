CXX = g++
CXXFLAGS = -std=c++17
RM = del
ALG = src/Algorytm/
MOD = src/Modul_glowny/
O = object/
EXE = .exe

main$(EXE): $(MOD)main.cpp $(O)input.o $(O)IO.o $(O)alg.o $(O)graf.o $(O)wynik.o
	$(CXX) $(MOD)main.cpp $(O)input.o $(O)IO.o $(O)alg.o $(O)graf.o $(O)wynik.o -o main
	
$(O)input.o: $(MOD)input.cpp $(MOD)input.h
	$(CXX) $(MOD)input.cpp -c -o $(O)input.o
	
$(O)IO.o: $(MOD)IO.cpp $(MOD)IO.h
	$(CXX) $(CXXFLAGS) $(MOD)IO.cpp -c -o $(O)IO.o

$(O)alg.o: $(ALG)alg.cpp $(ALG)alg.h
	$(CXX) $(ALG)alg.cpp -c -o $(O)alg.o
	
$(O)graf.o: $(ALG)graf.cpp $(ALG)graf.h
	$(CXX) $(ALG)graf.cpp -c -o $(O)graf.o
	
$(O)wynik.o: $(ALG)wynik.cpp $(ALG)wynik.h
	$(CXX) $(ALG)wynik.cpp -c -o $(O)wynik.o

clean:
	$(RM) object