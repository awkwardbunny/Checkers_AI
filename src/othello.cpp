#include<cstring>
#include<vector>
#include<chrono>
#include<ctime>
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

void Game::setPlayer(int n, Player *p){
	players[n] = p;
}

void Game::setTurn(int t){
	gs.turn = t;
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
				case 1: std::cout << termcolor::on_white << "___"; break;
				case 2: std::cout << termcolor::on_grey << termcolor::white << "___" << termcolor::grey; break;
			}
			if(x != 7)
				std::cout << termcolor::on_green << "|";
		}
		std::cout << termcolor::reset << "\n";
	}
	std::cout << "Current turn: Player " << gs.turn+1 << " (" << ((gs.turn == 0) ? "WHITE" : "BLACK") << ")\n";
	std::cout << (int)(this->time) << " seconds per turn\n";
}

std::istream& Othello::operator>>(std::istream &in, Game &g){
	std::string buf;
	for(int y = 0; y < 8; y++){
		for(int x = 0; x < 8; x++){
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
		for(int x = 0; x < 8; x++){
			out << int2chr(g.gs.board[x][y]) << " ";
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

		if(!(players[gs.turn]->makeMove(gs))){
			if(skipped){
				active = false;
				std::cout << "\nBoth players skipped. The game ends!\n";
			}
			skipped = true;
		}
	}
}

void Player::findMoves(GameState gs, std::vector<Move> &moves){
	Move m = {.xpos = 0, .ypos = 0, .gs = NULL};
	for(int y = 0; y < 8; y++){
		for(int x = 0; x < 8; x++){
			// is valid move?
			if(gs.board[x][y] != 0)
				continue;

			int xi = x;
			int yi = y;

			bool added = false;
			// Check up (0)
			if(y != 0 && gs.board[x][y-1] == (!gs.turn)+1){
				while(gs.board[xi][--yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
					added = true;
				}
			}
			// Check up-right (1)
			xi = x; yi = y;
			if(!added && y != 0 && x != 7 && gs.board[x+1][y-1] == (!gs.turn)+1){
				while(gs.board[++xi][--yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
					added = true;
				}
			}
			// Check right (2)
			xi = x; yi = y;
			if(!added && x != 7 && gs.board[x+1][y] == (!gs.turn)+1){
				while(gs.board[++xi][yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
					added = true;
				}
			}
			// Check down-right (3)
			xi = x; yi = y;
			if(!added && y != 7 && x != 7 && gs.board[x+1][y+1] == (!gs.turn)+1){
				while(gs.board[++xi][++yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
					added = true;
				}
			}
			// Check down (4)
			xi = x; yi = y;
			if(!added && y != 7 && gs.board[x][y+1] == (!gs.turn)+1){
				while(gs.board[xi][++yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
					added = true;
				}
			}
			// Check down-left (5)
			xi = x; yi = y;
			if(!added && y != 7 && x != 0 && gs.board[x-1][y+1] == (!gs.turn)+1){
				while(gs.board[--xi][++yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
					added = true;
				}
			}
			// Check left (6)
			xi = x; yi = y;
			if(!added && x != 0 && gs.board[x-1][y] == (!gs.turn)+1){
				while(gs.board[--xi][yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
					added = true;
				}
			}
			// Check up-left (7)
			xi = x; yi = y;
			if(!added && x != 0 && y != 0 && gs.board[x-1][y-1] == (!gs.turn)+1){
				while(gs.board[--xi][--yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
					added = true;
				}
			}
		}
	}
}

bool Human::makeMove(GameState &gs){
	// Find moves
	std::vector<Move> moves;
	findMoves(gs, moves);

	// Print moves
	std::cout << "\nAvailable moves: \n";
	int counter = 0;
	for(auto const& m : moves){
		std::cout << counter++ << ": (" << m.xpos << "," << m.ypos << ")\n";
	}
	
	if(!counter){
		std::cout << "None found. Your turn will be skipped...\n";
		return false;
	}

	// Pick move
	int choice = 999;
	std::string gabario;
	while(choice < 0 || choice > (signed int)moves.size()-1){
		std::cout << "Pick your choice (0-" << moves.size()-1 << "): ";
		std::cin >> choice;
		if(std::cin.fail()){
			choice = 999;
			std::cin.clear();
			std::cin >> gabario;
			std::cout << "Invalid input!\n";
		}
	}

	// Execute move
	Move m = moves[choice];
	executeMove(gs, m);

	std::cout << "\n";
	gs.turn = !gs.turn;
	return true;
}

void Player::executeMove(GameState &gs, Move m){
	int x = m.xpos;
	int y = m.ypos;

	int xi, yi;

	// Process UP
	xi = x, yi = y;
	while(yi != 0 && gs.board[xi][--yi] == (!gs.turn)+1); // Go all the way out
	if(gs.board[xi][yi] == gs.turn+1){ // And if the other end is found
		while(xi != x || yi != y) // Come back and flip on the way
			gs.board[xi][++yi] = gs.turn+1;
	}

	// Process UP-RIGHT
	xi = x, yi = y;
	while(yi != 0 && xi != 7 && gs.board[++xi][--yi] == (!gs.turn)+1); // Go all the way out
	if(gs.board[xi][yi] == gs.turn+1){ // And if the other end is found
		while(xi != x && yi != y) // Come back and flip on the way
			gs.board[--xi][++yi] = gs.turn+1;
	}

	// Process RIGHT
	xi = x, yi = y;
	while(xi != 7 && gs.board[++xi][yi] == (!gs.turn)+1); // Go all the way out
	if(gs.board[xi][yi] == gs.turn+1){ // And if the other end is found
		while(xi != x || yi != y){ // Come back and flip on the way
			gs.board[--xi][yi] = gs.turn+1;
		}
	}

	// Process DOWN-RIGHT
	xi = x, yi = y;
	while(yi != 7 && xi != 7 && gs.board[++xi][++yi] == (!gs.turn)+1); // Go all the way out
	if(gs.board[xi][yi] == gs.turn+1){ // And if the other end is found
		while(xi != x || yi != y) // Come back and flip on the way
			gs.board[--xi][--yi] = gs.turn+1;
	}

	// Process DOWN
	xi = x, yi = y;
	while(yi != 7 && gs.board[xi][++yi] == (!gs.turn)+1); // Go all the way out
	if(gs.board[xi][yi] == gs.turn+1){ // And if the other end is found
		while(xi != x || yi != y) // Come back and flip on the way
			gs.board[xi][--yi] = gs.turn+1;
	}

	// Process DOWN-LEFT
	xi = x, yi = y;
	while(xi != 0 && yi != 7 && gs.board[--xi][++yi] == (!gs.turn)+1); // Go all the way out
	if(gs.board[xi][yi] == gs.turn+1){ // And if the other end is found
		while(xi != x || yi != y) // Come back and flip on the way
			gs.board[++xi][--yi] = gs.turn+1;
	}

	// Process LEFT
	xi = x, yi = y;
	while(xi != 0 && gs.board[--xi][yi] == (!gs.turn)+1); // Go all the way out
	if(gs.board[xi][yi] == gs.turn+1){ // And if the other end is found
		while(xi != x || yi != y) // Come back and flip on the way
			gs.board[++xi][yi] = gs.turn+1;
	}

	// Process UP-LEFT
	xi = x, yi = y;
	while(yi != 0 && x != 0 && gs.board[--xi][--yi] == (!gs.turn)+1); // Go all the way out
	if(gs.board[xi][yi] == gs.turn+1){ // And if the other end is found
		while(xi != x || yi != y) // Come back and flip on the way
			gs.board[++xi][++yi] = gs.turn+1;
	}
}

bool Robot::makeMove(GameState &gs){
	//std::clock_t c_start = std::clock();
	auto t_start = std::chrono::high_resolution_clock::now();

	// Find moves
	std::vector<Move> moves;
	findMoves(gs, moves);

	if(moves.size() == 1){
		executeMove(gs, moves[0]);
		gs.turn = !gs.turn;
		return true;
	}else if(moves.size() == 0){
		gs.turn = !gs.turn;
		return false;
	}

	Move m = moves[0];
	executeMove(gs, m);
	std::cout << "Made move (" << m.xpos << "," << m.ypos <<")\n";

	auto t_end = std::chrono::high_resolution_clock::now();
	std::cout << "Time spent for decision: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << "ms\n";

	std::cout << "\n";
	gs.turn = !gs.turn;
	return true;
}
