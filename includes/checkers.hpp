#ifndef __CHECKERS__
#define __CHECKERS__

#include<string>
#include<iostream>
#include<cstdlib>

#define int2chr(i) (char)('0'+i)
#define color1 termcolor::green
#define color2 termcolor::cyan

namespace Checkers {

	typedef struct {
		unsigned int player : 1;
		unsigned int isKing : 1;
		unsigned int isDead : 1;
		unsigned int xPos : 2;
		unsigned int yPos : 3;
	} Piece;

	class GameState {
		public:
			GameState(){}
			GameState(uint8_t time);
			//GameState(std::string in);

			void setTime(uint8_t time);
			uint8_t getTime();

			friend std::ostream& operator<<(std::ostream &out, GameState gs);
			friend std::istream& operator>>(std::istream &in, GameState &gs);
			void print();

		private:
			uint8_t time = 0;
			uint8_t turn = 0;
			uint8_t iboard[4][8] = {
				{1,1,1,0,0,2,2,2},
				{1,1,1,0,0,2,2,2},
				{1,1,1,0,0,2,2,2},
				{1,1,1,0,0,2,2,2}
			};

			//Piece **pboard = (Piece**)iboard;

			//Piece pieces[24] = {
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0},
			//	{0,0,0,0,0}
			//};
	};

	std::ostream& operator<<(std::ostream &out, GameState gs);
	std::istream& operator>>(std::istream &in, GameState &gs);

//	class Game {
//		public:
//			Game();
//
//			void start();
//			void stop();
//			void reset();
//
//			void load(GameState gs);
//
//			GameState getGameState();
//			void setGameState(GameState gs);
//	};

}

#endif
