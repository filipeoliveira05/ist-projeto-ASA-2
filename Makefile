# Nome do compilador
CXX = g++

# Flags do compilador
CXXFLAGS = -std=c++11 -O3 -Wall

# Nome do arquivo fonte
SRC = ASA2425P2.cpp

# Nome do arquivo executável
TARGET = proj2

# Regra padrão para compilar o programa
all: $(TARGET)

# Como compilar o arquivo executável a partir do código-fonte
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) -lm

# Limpeza dos arquivos gerados pela compilação
clean:
	rm -f $(TARGET)

# Regra para rodar o programa após a compilação
run: all
	./$(TARGET)
