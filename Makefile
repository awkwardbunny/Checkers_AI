.PHONY: all clean run

TARGET = checkers
INCLUDE = includes
INCL_H = $(wildcard includes/*)

CXX = g++
CXX_FLAGS = -g -std=c++11 -I $(INCLUDE) -Wall -Werror

all: run

$(TARGET): checkers.o main.o
	$(CXX) $^ -o $@

%.o: src/%.cpp $(INCL_H)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

run: $(TARGET)
	@./$(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)

