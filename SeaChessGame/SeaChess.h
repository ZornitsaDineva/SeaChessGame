#pragma once
class SeaChess
{
private:
	int r, c, turns = 0;
	char board[3][3];
	char symbol, otherSymbol;
	bool isFinished();
	bool isValidPosition();
	bool winPosition = false;
	void enterSymbol();
	void checkForWinPosition();
	void doStep();
	void printWinner();
	void printBoard();
	void drawLine();
	void enterPosition();
	void clearScreen();
	void setPosition();
	void printPlayer();

public:
	SeaChess();
	~SeaChess();
	void start();
};

