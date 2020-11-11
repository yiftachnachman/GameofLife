#include <iostream>
#include <fstream>
using namespace std;

class GameOfLife
{
	private:
		int height;
		int width;
		double popDens;
		string fileName;
		char** gameBoard;
		char** nextGen;
		char gameMode;
		char configAnswer;
		string infileName;
		bool stable;
		string outFileName;
		char outputType; 
		ofstream outfile;
		
	public:
		GameOfLife();
		~GameOfLife();
		
		
		void askQuestions();
		void typeOfOutput();
		void setBoard();
		void RandomDrawBoard();
		void flatLineDrawBoard();
		void copyArr(char** before, char** after);
		void checkIfEmpty(char** arr);
		void checkIfStable(char** before, char** after);
		void classicMode();
		void doughnutMode();
		void mirrorMode();
		void setGameMode();
		void runGameLoop();
		void basicSetup();
		void ContinueOrOutput();
		void printBoard(char** arr);
		
};
