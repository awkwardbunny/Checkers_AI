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
		unsigned int do_move: 1;
		unsigned int xpos: 2;
		unsigned int ypos: 3;
		unsigned int dir: 2;
	} Move;

	typedef struct MoveNode MoveNode;
	
	struct MoveNode {
		Move move;
		MoveNode *a, *b, *c, *d;
	};

	typedef struct {
		unsigned int player : 1;
		unsigned int isKing : 1;
		unsigned int isDead : 1;
		unsigned int xPos : 2;
		unsigned int yPos : 3;
	} Piece;

	typedef struct {
		uint8_t board [4][8] = {
					{1,1,1,0,0,2,2,2},
					{1,1,1,0,0,2,2,2},
					{1,1,1,0,0,2,2,2},
					{1,1,1,0,0,2,2,2}};
		uint8_t turn = 0;
	} GameState;

	class Player {
		public:
			void setCPU();
			void findMoves(GameState gs, MoveNode (&mn)[12]);
			void makeMove(GameState &gs);
		
		private:
			bool isCPU = false;
	};

	class Game {
		public:
			Game(){}
			Game(uint8_t time);
			//Game(std::string in);
			//Game(uint8_t **iboard);
			
			void go();

			void setTime(uint8_t time);
			uint8_t getTime();

			friend std::ostream& operator<<(std::ostream &out, Game gs);
			friend std::istream& operator>>(std::istream &in, Game &gs);
			void print();

			void setPlayerCPU(int num);

		private:
			bool active = false;
			uint8_t time = 0; // 0 is unlim
			Player players[2];
			GameState gs;

			//char pmap[5] = { ' ', '.', '*', 'O', 'X' };
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

	std::ostream& operator<<(std::ostream &out, Game gs);
	std::istream& operator>>(std::istream &in, Game &gs);

}

#endif
