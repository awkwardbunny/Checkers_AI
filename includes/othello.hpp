#ifndef __OTHELLO__
#define __OTHELLO__

#include<string>
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

	class Player {
		public:
			void makeMove(GameState &gs);
	};

	class Game {
		public:
			Game(){}
			Game(uint8_t time);
			
			void go();

			void setTime(uint8_t time);
			uint8_t getTime();

			friend std::ostream& operator<<(std::ostream &out, Game gs);
			friend std::istream& operator>>(std::istream &in, Game &gs);
			void print();

		private:
			bool active = false;
			uint8_t time = 0; // 0 is unlim
			Player players[2];
			GameState gs;

	};

	std::ostream& operator<<(std::ostream &out, Game gs);
	std::istream& operator>>(std::istream &in, Game &gs);
}

#endif
