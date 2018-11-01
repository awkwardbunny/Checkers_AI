#include<checkers.hpp>
#include<termcolor.hpp>

using namespace Checkers;

GameState::GameState(uint8_t t){
	setTime(t);
}

void GameState::setTime(uint8_t t){
	this->time = t;
}

uint8_t GameState::getTime(){
	return time;
}

void GameState::print(){
	std::cout << "   0 1 2 3 4 5 6 7\n";
	std::cout << "  +----------------+\n";

	for(int y = 0; y < 8; y++){
		std::cout << " " << y << "|";
		for(int x = 0; x < 4; x++){
			if(y % 2){
				//std::cout << termcolor::on_grey << ((iboard[x][y] % 2) ? termcolor::green : termcolor::yellow) << ((iboard[x][y] == 0) ? "  " : (iboard[x][y] > 2) ? "##" : "# ") << termcolor::on_white << "  ";
				std::cout << termcolor::on_grey;
				switch(iboard[x][y]){
					case 0: std::cout << "  "; break;
					case 1: std::cout << termcolor::red << ". "; break;
					case 2: std::cout << termcolor::yellow << "* "; break;
					case 3: std::cout << termcolor::red << "OO"; break;
					case 4: std::cout << termcolor::yellow << "XX"; break;
				}
				std::cout << termcolor::on_white << "  ";
			}else{
				//std::cout << termcolor::on_white << "  " << termcolor::on_grey << ((iboard[x][y] % 2) ? termcolor::green : termcolor::yellow) << ((iboard[x][y] == 0) ? "  " : (iboard[x][y] > 2) ? "##" : "# ");
				std::cout << termcolor::on_white << "  " << termcolor::on_grey;
				switch(iboard[x][y]){
					case 0: std::cout << "  "; break;
					case 1: std::cout << termcolor::red << ". "; break;
					case 2: std::cout << termcolor::yellow << "* "; break;
					case 3: std::cout << termcolor::red << "OO"; break;
					case 4: std::cout << termcolor::yellow << "XX"; break;
				}
			}
		}
		std::cout << termcolor::reset << "|\n";
		//std::cout << buf;
	}
	std::cout << "  +----------------+\n";
}

std::istream& Checkers::operator>>(std::istream &in, GameState &gs){
	std::string buf;
	for(int y = 0; y < 8; y++){
		for(int x = 0; x < 4; x++){
			in >> buf;
			gs.iboard[x][y] = buf[0]-'0';
			//std::cout << buf[0]-'0';
		}
	}
	in >> buf;
	gs.turn = stoi(buf);
	in >> buf;
	gs.time = stoi(buf);
	return in;
}

std::ostream& Checkers::operator<<(std::ostream &out, GameState gs){
	for(int y = 0; y < 8; y++){
		for(int x = 0; x < 4; x++){
			if(y % 2){
				out << int2chr(gs.iboard[x][y]) << "   ";
			}else{
				out << "  " << int2chr(gs.iboard[x][y]) << " ";
			}
		}
		out << '\n';
	}
	out << int2chr(gs.turn) << '\n';

	char num[5];
	sprintf(num,"%d",gs.time);
	out << num << '\n';

	return out;
}

