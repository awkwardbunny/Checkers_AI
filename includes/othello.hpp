#ifndef __OTHELLO__
#define __OTHELLO__

#include<string>
#include<vector>
#include<iostream>
#include<cstdlib>

#define int2chr(i) (char)('0'+i)
#define color1 termcolor::green
#define color2 termcolor::cyan

namespace Othello {

	typedef struct {
		uint8_t board [8][8] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,1,2,0,0,0},
					{0,0,0,2,1,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0}};
		uint8_t turn = 0;
	} GameState;

	typedef struct Move Move;
	struct Move {
		unsigned int xpos : 3;
		unsigned int ypos : 3;
		GameState *gs;
		std::vector<Move> moves;
	};

	class Player {
		public:
			Player(){};
			virtual void makeMove(GameState &gs) = 0;
			void findMoves(GameState gs, std::vector<Move> &moves);
			void executeMove(GameState &gs, Move m);
	};

	class Human: public Player {
		public:
			void makeMove(GameState &gs);
	};

	class Robot: public Player {
		public:
			void makeMove(GameState &gs);
	};

	class Game {
		public:
			Game(): Game(0){}
			Game(uint8_t time);
			
			void go();

			void setTime(uint8_t time);
			uint8_t getTime();

			friend std::ostream& operator<<(std::ostream &out, Game gs);
			friend std::istream& operator>>(std::istream &in, Game &gs);
			void print();
			void setPlayer(int n, Player *p);
			void setTurn(int t);

		private:
			bool active = false;
			uint8_t time = 0; // 0 is unlim
			Player *players[2];
			GameState gs;

	};

	std::ostream& operator<<(std::ostream &out, Game gs);
	std::istream& operator>>(std::istream &in, Game &gs);
}

#endif
