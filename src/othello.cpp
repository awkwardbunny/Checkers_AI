#include<cstring>
#include<othello.hpp>
#include<termcolor.hpp>

using namespace Othello;

Game::Game(uint8_t t){
	setTime(t);
}

void Game::setTime(uint8_t t){
	this->time = t;
}

uint8_t Game::getTime(){
	return time;
}

void Game::print(){
	std::cout << "y\\x 0   1   2   3   4   5   6   7\n";
	//std::cout << termcolor::grey << "   ________________________________\n" << termcolor::reset;

	for(int y = 0; y < 8; y++){
		std::cout << " " << y << " " << termcolor::on_green << termcolor::grey; // << "|";
		for(int x = 0; x < 8; x++){
			switch(gs.board[x][y]){
				case 0: std::cout << termcolor::on_green; break;
				case 1: std::cout << termcolor::on_white; break;
				case 2: std::cout << termcolor::on_grey; break;
			}
			std::cout << "   ";
			if(x != 7)
				std::cout << termcolor::on_green << "|";
		}
		std::cout << termcolor::reset << "\n";

		std::cout << "   " << termcolor::on_green << termcolor::grey; // << "|";
		for(int x = 0; x < 8; x++){
			switch(gs.board[x][y]){
				case 0: std::cout << termcolor::on_green << "___"; break;
				case 1: std::cout << termcolor::on_white << termcolor::white << "_X_" << termcolor::grey ; break;
				case 2: std::cout << termcolor::on_grey << "_O_"; break;
			}
			if(x != 7)
				std::cout << termcolor::on_green << "|";
		}
		std::cout << termcolor::reset << "\n";
	}
	std::cout << "Current turn: Player " << gs.turn+1 << "\n";
	std::cout << (int)(this->time) << " seconds per turn\n";
}

std::istream& Othello::operator>>(std::istream &in, Game &g){
	std::string buf;
	for(int y = 0; y < 8; y++){
		for(int x = 0; x < 4; x++){
			in >> buf;
			g.gs.board[x][y] = buf[0]-'0';
			//std::cout << buf[0]-'0';
		}
	}
	in >> buf;
	//gs.turn = stoi(buf);
	//gs.turn--;
	g.gs.turn = (buf[0] == '2');
	in >> buf;
	g.time = stoi(buf);
	return in;
}

std::ostream& Othello::operator<<(std::ostream &out, Game g){
	for(int y = 0; y < 8; y++){
		for(int x = 0; x < 4; x++){
			if(y % 2){
				out << int2chr(g.gs.board[x][y]) << "   ";
			}else{
				out << "  " << int2chr(g.gs.board[x][y]) << " ";
			}
		}
		out << '\n';
	}
	out << int2chr(g.gs.turn+1) << '\n';

	char num[5];
	sprintf(num,"%d",g.time);
	out << num << '\n';

	return out;
}

void Game::go(){
	active = true;
	while(active){
		print();

		players[gs.turn].makeMove(gs);
		//gs.turn = !gs.turn;
	}
}

void Player::makeMove(GameState &gs){
	std::string strChoice;
	std::cin >> strChoice;
	std::cout << (int)(gs.turn) << std::endl;
	gs.turn = !gs.turn;
}

//void Player::findMoves(GameState gs, MoveNode (&mn)[12]){
//
//}
//
//void Player::makeMove(GameState &gs){
//	MoveNode moves[12];
//
//	// Find Moves
//	findMoves(gs, moves);
//
//	// Print Moves
//	printf("\nAvailable moves:\n");
//	for(int i = 0; i < 12; i++){
//		MoveNode cmn = moves[i];
//		cmn = cmn;
//		//while(
//	}
//
//	int choice;
//	std::string strChoice;
//	std::cout << "\nEnter the number that you'd like to choose: ";
//	std::cin >> strChoice;
//	choice = std::stoi(strChoice);
//
//	// Execute Moves
//	std::cout << "You chose: " << choice;
//	std::cout << "\n\n\n";
//
//	gs.turn = !gs.turn;
//}
