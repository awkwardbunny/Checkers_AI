#include<fstream>
#include<othello.hpp>

int main(int argc, char **argv){

	using namespace Othello;

	Game game;

	bool timeout = false;

	std::string strLoad = "blah";
	while(strLoad != "y" && strLoad != "n"){
		std::cout << "Is player one computer? (y/n): ";
		std::cin >>	strLoad;
	}
	if(strLoad == "y"){
		timeout = true;
		game.setPlayer(0, new Robot());
	}else{
		game.setPlayer(0, new Human());
	}

	strLoad = "blah";
	while(strLoad != "y" && strLoad != "n"){
		std::cout << "Is player two computer? (y/n): ";
		std::cin >>	strLoad;
	}
	if(strLoad == "y"){
		timeout = true;
		game.setPlayer(1, new Robot());
	}else{
		game.setPlayer(1, new Human());
	}

	strLoad = "blah";
	while(strLoad != "y" && strLoad != "n"){
		std::cout << "Would you like to load a saved game? (y/n): ";
		std::cin >>	strLoad;
	}

	if(strLoad == "y"){
		std::cout << "Enter filename: ";
		std::cin >> strLoad;
		
		std::fstream fin;
		fin.open(strLoad);
		fin >> game;
		fin.close();
	}else{
		strLoad = "blah";
		while(strLoad != "y" && strLoad != "n"){
			std::cout << "Player one starts? (y/n): ";
			std::cin >>	strLoad;
		}
		if(strLoad == "n"){
			game.setTurn(1);
		}
	}

	if(timeout){
		std::cout << "Enter a time limit in seconds: ";
		std::cin >>	strLoad;
		game.setTime(std::stoi(strLoad));
	}

	game.go();

	return 0;
}
