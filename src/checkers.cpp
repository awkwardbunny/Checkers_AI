#include<cstring>
#include<checkers.hpp>
#include<termcolor.hpp>

using namespace Checkers;

Game::Game(uint8_t t){
	setTime(t);
}

//Game::Game(uint8_t **iboard){
//	std::memcpy(this->iboard, iboard, 32);
//}

void Game::setTime(uint8_t t){
	this->time = t;
}

uint8_t Game::getTime(){
	return time;
}

void Game::print(){
	std::cout << "   0 1 2 3 4 5 6 7\n";
	std::cout << "  +----------------+\n";

	for(int y = 0; y < 8; y++){
		std::cout << " " << y << "|";
		std::cout << termcolor::bold << termcolor::dark;
		for(int x = 0; x < 4; x++){
			if(y % 2){
				//std::cout << termcolor::on_grey << ((iboard[x][y] % 2) ? termcolor::green : termcolor::yellow) << ((iboard[x][y] == 0) ? "  " : (iboard[x][y] > 2) ? "##" : "# ") << termcolor::on_white << "  ";
				//uint8_t cur_p = iboard[x][y];
				//std::cout << (cur_p % 2) ? color1 : color2 << pmap[cur_p] << pmap[cur_p];
				std::cout << termcolor::on_grey;
				switch(gs.board[x][y]){
					case 0: std::cout << "  "; break;
					case 1: std::cout << color1 << ". "; break;
					case 2: std::cout << color2 << "* "; break;
					case 3: std::cout << color1 << "OO"; break;
					case 4: std::cout << color2 << "XX"; break;
				}
				std::cout << termcolor::on_white << "  ";
			}else{
				//std::cout << termcolor::on_white << "  " << termcolor::on_grey << ((iboard[x][y] % 2) ? termcolor::green : termcolor::yellow) << ((iboard[x][y] == 0) ? "  " : (iboard[x][y] > 2) ? "##" : "# ");
				std::cout << termcolor::on_white << "  " << termcolor::on_grey;
				switch(gs.board[x][y]){
					case 0: std::cout << "  "; break;
					case 1: std::cout <<  color1 << ". "; break;
					case 2: std::cout <<  color2 << "* "; break;
					case 3: std::cout <<  color1 << "OO"; break;
					case 4: std::cout <<  color2 << "XX"; break;
				}
			}
		}
		std::cout << termcolor::reset << "|\n";
		//std::cout << buf;
	}
	std::cout << "  +----------------+\n";
	std::cout << "Current turn: Player " << gs.turn+1 << "\n";
	std::cout << (int)(this->time) << " seconds per turn\n";
}

std::istream& Checkers::operator>>(std::istream &in, Game &g){
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

std::ostream& Checkers::operator<<(std::ostream &out, Game g){
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

