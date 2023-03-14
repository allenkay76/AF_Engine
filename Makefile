CXX := g++
CXX_FLAGS := -std=c++11 -ggdb -Wall -Wextra -Werror -pedantic -Wconversion -Wformat-security -Wnull-dereference -Wdouble-promotion -Wshadow -fstack-protector-strong -D_FORTIFY_SOURCE=2

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