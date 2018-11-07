.PHONY: all clean run

TARGET = othello
INCLUDE = includes
INCL_H = $(wildcard includes/*)

CXX = g++
CXX_FLAGS = -g -std=c++11 -I $(INCLUDE) -Wall -Werror

all: run

$(TARGET): othello.o main.o
	$(CXX) $^ -o $@

%.o: src/%.cpp $(INCL_H)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

run: $(TARGET)
	@./$(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)

