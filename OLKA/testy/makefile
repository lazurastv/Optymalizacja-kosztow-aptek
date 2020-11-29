CXX = g++
CXXFLAGS = -std=c++17
RM = del
MOD = ../src/Modul_glowny/
ALG = ../src/Algorytm/
BIN = bin/
EXE = .exe

all: $(BIN)input_test$(EXE) $(BIN)IO_test$(EXE) $(BIN)graf_test$(EXE) $(BIN)alg_test$(EXE)

$(BIN)input_test$(EXE): input_test.cpp
	$(CXX) input_test.cpp $(MOD)input.cpp -o $(BIN)input_test
	
$(BIN)IO_test$(EXE): IO_test.cpp
	$(CXX) $(CXXFLAGS) IO_test.cpp $(MOD)IO.cpp $(MOD)input.cpp -o $(BIN)IO_test
	
$(BIN)graf_test$(EXE): graf_test.cpp
	$(CXX) graf_test.cpp $(ALG)graf.cpp $(MOD)input.cpp -o $(BIN)graf_test
	
$(BIN)alg_test$(EXE): alg_test.cpp
	$(CXX) alg_test.cpp $(ALG)alg.cpp $(ALG)graf.cpp $(MOD)input.cpp $(ALG)wynik.cpp -o $(BIN)alg_test
	
clean:
	$(RM) bin