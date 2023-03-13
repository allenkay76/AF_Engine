CXX := g++
CXX_FLAGS := -std=c++11 -ggdb

BIN := bin
SRC := src
INCLUDE := include

LIBRARIES :=
EXECUTABLE := AF_Engine


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*