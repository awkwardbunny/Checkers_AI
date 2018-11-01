#include<checkers.hpp>

int main(int argc, char **argv){
	Checkers::GameState gs(10);
	std::cin >> gs;
	std::cout << gs;
	gs.print();
}
