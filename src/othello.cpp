#include<cstring>
#include<list>
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
	std::cout << "Current turn: Player " << gs.turn+1 << "\n";
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

		players[gs.turn]->makeMove(gs);
	}
}

void Player::findMoves(GameState gs, std::list<Move> &moves){
	Move m;
	for(int y = 0; y < 8; y++){
		for(int x = 0; x < 8; x++){
			// is valid move?
			if(gs.board[x][y] != 0)
				continue;

			int xi = x;
			int yi = y;

			// Check up (0)
			if(y != 0 && gs.board[x][y-1] == (!gs.turn)+1){
				while(gs.board[xi][--yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
				}
			// Check up-right (1)
			}else if(y != 0 && x != 7 && gs.board[x+1][y-1] == (!gs.turn)+1){
				while(gs.board[++xi][--yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
				}
			// Check right (2)
			}else if(x != 7 && gs.board[x+1][y] == (!gs.turn)+1){
				while(gs.board[++xi][yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
				}
			// Check down-right (3)
			}else if(y != 7 && x != 7 && gs.board[x+1][y+1] == (!gs.turn)+1){
				while(gs.board[++xi][++yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
				}
			// Check down (4)
			}else if(y != 7 && gs.board[x][y+1] == (!gs.turn)+1){
				while(gs.board[xi][++yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
				}
			// Check down-left (5)
			}else if(y != 7 && x != 0 && gs.board[x-1][y+1] == (!gs.turn)+1){
				while(gs.board[--xi][++yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
				}
			// Check left (6)
			}else if(x != 0 && gs.board[x-1][y] == (!gs.turn)+1){
				while(gs.board[--xi][yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
				}
			// Check up-left (7)
			}else if(x != 0 && y != 0 && gs.board[x-1][y-1] == (!gs.turn)+1){
				while(gs.board[--xi][--yi] == (!gs.turn)+1);
				if(gs.board[xi][yi] == gs.turn+1){
					m.xpos = x;
					m.ypos = y;
					moves.push_back(m);
				}
			}
		}
	}
}

void Human::makeMove(GameState &gs){
	// Find moves
	std::list<Move> moves;
	findMoves(gs, moves);

	// Print moves
	int counter = 0;
	for(auto const& m : moves){
		std::cout << counter++ << ": (" << m.xpos << "," << m.ypos << ")\n";
	}
	
	// Pick move
	std::string strChoice;
	std::cin >> strChoice;
	std::cout << (int)(gs.turn) << std::endl;
	gs.turn = !gs.turn;
}

void Robot::makeMove(GameState &gs){
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
