#include<cstring>
#include<vector>
#include<chrono>
#include<ctime>
#include<climits>
#include<othello.hpp>
#include<termcolor.hpp>

using namespace Othello;

Game::Game(uint8_t t){
	setTime(t);
}

void Game::setTime(uint8_t t){
	this->time = t;
	if(players[0])
		players[0]->setTime(t);
	if(players[1])
		players[1]->setTime(t);
}

uint8_t Game::getTime(){
	return time;
}

void Game::setPlayer(int n, Player *p){
	players[n] = p;
	//p->setTime(time);
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
			}else{
				skipped = true;
			}
		}else{
			skipped = false;
		}
	}
	int w = decideWinner(gs);
	std::cout << "The winner is... Player " << w+1 << "!!!\n";
}

int Game::decideWinner(GameState gs){
	int one = 0, two = 0;
	for(int y = 0; y < 8; y++){
		for(int x = 0; x < 8; x++){
			if(gs.board[x][y] == 1)
				one++;
			else if(gs.board[x][y] == 2)
				two++;
		}
	}
	
	return (one<two);
}

void Player::findMoves(GameState gs, std::vector<Move> &moves){
	Move m = {.xpos = 0, .ypos = 0, .gs = NULL, .bestMove = -1};
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

Player *Game::getPlayer(int n){
	return players[n];
}

void Player::setTime(int t){
	time = t;
}

bool Robot::makeMove(GameState &gs){
	//std::clock_t c_start = std::clock();
	auto t_start = std::chrono::high_resolution_clock::now();

	// Find moves
	std::vector<Move> moves;
	findMoves(gs, moves);

	Move m;
	bool ret = true;
	int depth = 0;

	if(moves.size() == 1){
		m = moves[0];
		std::cout << "Taking the only move...\n";
	}else if(moves.size() == 0){
		std::cout << "No moves found. Turn will be skipped...\n";
		ret = false;
	}else{
		// Actual stuff
		Move curr;
		curr.gs = &gs;
		curr.moves = moves;
		doThings(curr, t_start, time, m, depth);
	}

	if(ret){
		executeMove(gs, m);
		std::cout << "Made move (" << m.xpos << "," << m.ypos <<")\n";
		std::cout << "Searched to depth " << depth <<"\n";
	}

	auto t_end = std::chrono::high_resolution_clock::now();
	std::cout << "Time spent for decision: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << "ms\n";

	std::cout << "\n";
	gs.turn = !gs.turn;
	return ret;
}

void Robot::doThings(Move current, std::chrono::time_point<std::chrono::high_resolution_clock> start, int time, Move &m, int &depth){
	auto t_now = std::chrono::high_resolution_clock::now();
	double ms = std::chrono::duration<double, std::milli>(t_now-start).count();

	float ftime = time;
	depth = 0;
	int choice = 0;
	while((ms/1000.0) <= 0.98*ftime){
		
		//std::cout << "In doThings loop.\n";
		minimax(current, depth++, true, INT_MIN, INT_MAX, true, choice, start, time);
	
		t_now = std::chrono::high_resolution_clock::now();
		ms = std::chrono::duration<double, std::milli>(t_now - start).count();
	}
	m = current.moves[choice];
}

int Robot::minimax(Move &current, int depth, bool isMax, int alpha, int beta, bool first, int &choice, std::chrono::time_point<std::chrono::high_resolution_clock> start, int time){

	auto t_now = std::chrono::high_resolution_clock::now();
	double ms = std::chrono::duration<double, std::milli>(t_now-start).count();
	float ftime = time;
	if((ms/1000.0) > 0.9*ftime){
		return 0;
	}

	std::srand(std::time(NULL));
	//std::cout << depth;
	//std::cout << "A";

	if(depth == 0 && first){
		int ind = -1;
		int blah;
		int bestVal = INT_MIN;
		//std::cout << "B";
		for(unsigned int i = 0; i < current.moves.size(); i++){
			current.moves[i].gs = (GameState *)malloc(69);
			std::memcpy(current.moves[i].gs, current.gs, 69);
			//std::cout << "E";
			executeMove(*current.moves[i].gs, current.moves[i]);
			//std::cout << "F";
			findMoves(*current.moves[i].gs, current.moves[i].moves);
			//std::cout << "C\n";
			int val = minimax(current.moves[i], depth, false, alpha, beta, false, blah, start, time);
			//std::cout << "D\n";
			if(val > bestVal){
				bestVal = val;
				ind = i;
			}else if(val == bestVal){
				if(rand() % 2){
					ind = i;
				}
			}
			alpha = (alpha > bestVal) ? alpha : bestVal;
			if(beta <= alpha) break;
		}
		current.bestMove = ind;
		choice = ind;
		return bestVal;
	}

	if(depth == 0){
		// return value
		//std::cout << "\n";
		setScore(*current.gs);
		return current.gs->score;
	}

	int blah;
	int bestVal;
	int ind = -1;
	if(isMax){
		bestVal = INT_MIN;
		for(unsigned int i = 0; i < current.moves.size(); i++){
			if(current.bestMove == -1){
				//std::cout << "\nIn IF copy\n";
				current.moves[i].gs = (GameState *)malloc(69); // watch me forget to free this
				std::memcpy(current.moves[i].gs, current.gs, 69);
				executeMove(*current.moves[i].gs, current.moves[i]);
				findMoves(*current.moves[i].gs, current.moves[i].moves);
			}
			int val = minimax(current.moves[i], depth-1, false, alpha, beta, false, blah, start, time);
			if(val > bestVal){
				bestVal = val;
				ind = i;
			}else if(val == bestVal){
				if(rand() % 2){
					ind = i;
				}
			}
			alpha = (alpha > bestVal) ? alpha : bestVal;
			if(beta <= alpha) break;
		}
		current.bestMove = ind;
		if(first) choice = ind;
		//std::cout << ind << "\n";
		return bestVal;
	}else{
		bestVal = INT_MAX;
		for(unsigned int i = 0; i < current.moves.size(); i++){
			if(current.bestMove == -1){
				//std::cout << "\nIn ELSE copy\n";
				current.moves[i].gs = (GameState *)malloc(69); // watch me forget to free this
				std::memcpy(current.moves[i].gs, current.gs, 69);
				executeMove(*current.moves[i].gs, current.moves[i]);
				findMoves(*current.moves[i].gs, current.moves[i].moves);
			}else{
				//std::cout << "\nIn ELSE-ELSE\n";
				//std::cout << current.bestMove << "\n";
			}
			int val = minimax(current.moves[i], depth-1, true, alpha, beta, false, blah, start, time);
			if(val < bestVal){
				bestVal = val;
				ind = i;
			}else if(val == bestVal){
				if(rand() % 2){
					ind = i;
				}
			}
			beta = (beta < bestVal) ? beta : bestVal;
			if(beta <= alpha) break;
		}
		current.bestMove = ind;
		if(first) choice = ind;
		//std::cout << ind << "\n";
		return bestVal;
	}
}

void Robot::setScore(GameState &gs){
	std::vector<Move> moves;
	findMoves(gs, moves);
	int one = 0;
	int two = 0;
	int empty = 0;

	for(int y = 0; y < 8; y++){
		for(int x = 0; x < 8; x++){
			if(gs.board[x][y] == gs.turn+1){
				one++;
			}else if(gs.board[x][y] == (!gs.turn)+1){
				two--;
			}else{
				empty++;
			}
		}
	}

	if(moves.size() == 0){
		GameState next = gs;
		next.turn = !gs.turn;
		std::vector<Move> nextMoves;
		findMoves(next, nextMoves);

		// game ended?
		if(nextMoves.size() == 0){
			if(one-two > 0){
				gs.score = INT_MAX-100 + (one-two);
			}else{
				gs.score = INT_MIN+100 + (one-two);
			}
			return;
		}
	}

	// Get corners
	if(gs.board[0][0] == gs.turn+1) gs.score += 500;
	if(gs.board[0][7] == gs.turn+1) gs.score += 500;
	if(gs.board[7][7] == gs.turn+1) gs.score += 500;
	if(gs.board[7][0] == gs.turn+1) gs.score += 500;
	if(gs.board[0][0] == !gs.turn+1) gs.score -= 500;
	if(gs.board[0][7] == !gs.turn+1) gs.score -= 500;
	if(gs.board[7][7] == !gs.turn+1) gs.score -= 500;
	if(gs.board[7][0] == !gs.turn+1) gs.score -= 500;

	// Get edges
	// What are loops?
	if(gs.board[0][2] == gs.turn+1) gs.score += 50;
	if(gs.board[0][3] == gs.turn+1) gs.score += 50;
	if(gs.board[0][4] == gs.turn+1) gs.score += 50;
	if(gs.board[0][5] == gs.turn+1) gs.score += 50;
	if(gs.board[7][2] == gs.turn+1) gs.score += 50;
	if(gs.board[7][3] == gs.turn+1) gs.score += 50;
	if(gs.board[7][4] == gs.turn+1) gs.score += 50;
	if(gs.board[7][5] == gs.turn+1) gs.score += 50;
	if(gs.board[2][0] == gs.turn+1) gs.score += 50;
	if(gs.board[3][0] == gs.turn+1) gs.score += 50;
	if(gs.board[4][0] == gs.turn+1) gs.score += 50;
	if(gs.board[5][0] == gs.turn+1) gs.score += 50;
	if(gs.board[2][7] == gs.turn+1) gs.score += 50;
	if(gs.board[3][7] == gs.turn+1) gs.score += 50;
	if(gs.board[4][7] == gs.turn+1) gs.score += 50;
	if(gs.board[5][7] == gs.turn+1) gs.score += 50;
	if(gs.board[0][2] == !gs.turn+1) gs.score -= 50;
	if(gs.board[0][3] == !gs.turn+1) gs.score -= 50;
	if(gs.board[0][4] == !gs.turn+1) gs.score -= 50;
	if(gs.board[0][5] == !gs.turn+1) gs.score -= 50;
	if(gs.board[7][2] == !gs.turn+1) gs.score -= 50;
	if(gs.board[7][3] == !gs.turn+1) gs.score -= 50;
	if(gs.board[7][4] == !gs.turn+1) gs.score -= 50;
	if(gs.board[7][5] == !gs.turn+1) gs.score -= 50;
	if(gs.board[2][0] == !gs.turn+1) gs.score -= 50;
	if(gs.board[3][0] == !gs.turn+1) gs.score -= 50;
	if(gs.board[4][0] == !gs.turn+1) gs.score -= 50;
	if(gs.board[5][0] == !gs.turn+1) gs.score -= 50;
	if(gs.board[2][7] == !gs.turn+1) gs.score -= 50;
	if(gs.board[3][7] == !gs.turn+1) gs.score -= 50;
	if(gs.board[4][7] == !gs.turn+1) gs.score -= 50;
	if(gs.board[5][7] == !gs.turn+1) gs.score -= 50;

	// Get near-corner
	if(gs.board[0][1] == gs.turn+1) gs.score += 250;
	if(gs.board[1][0] == gs.turn+1) gs.score += 250;
	if(gs.board[7][1] == gs.turn+1) gs.score += 250;
	if(gs.board[6][0] == gs.turn+1) gs.score += 250;
	if(gs.board[0][6] == gs.turn+1) gs.score += 250;
	if(gs.board[1][7] == gs.turn+1) gs.score += 250;
	if(gs.board[7][6] == gs.turn+1) gs.score += 250;
	if(gs.board[6][7] == gs.turn+1) gs.score += 250;
	if(gs.board[0][1] == !gs.turn+1) gs.score -= 250;
	if(gs.board[1][0] == !gs.turn+1) gs.score -= 250;
	if(gs.board[7][1] == !gs.turn+1) gs.score -= 250;
	if(gs.board[6][0] == !gs.turn+1) gs.score -= 250;
	if(gs.board[0][6] == !gs.turn+1) gs.score -= 250;
	if(gs.board[1][7] == !gs.turn+1) gs.score -= 250;
	if(gs.board[7][6] == !gs.turn+1) gs.score -= 250;
	if(gs.board[6][7] == !gs.turn+1) gs.score -= 250;

	for(int y = 1; y < 7; y++){
		for(int x = 1; x < 7; x++){
			if(gs.board[x][y] == gs.turn+1)
				gs.score++;
			else if(gs.board[x][y] == !gs.turn+1)
				gs.score--;

		}
	}
}
