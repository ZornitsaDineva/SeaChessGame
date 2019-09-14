#include "pch.h"
#include <iostream>
#include "SeaChess.h"

using namespace std;

SeaChess::SeaChess()
{
	for (int r = 0; r <= 2; r++) {
		for (int c = 0; c <= 2; c++) {
			board[r][c] = ' ';
		}
	}
}

SeaChess::~SeaChess()
{
}

void SeaChess::start()
{
	enterSymbol();

	while (!isFinished()) {
		doStep();
	}

	clearScreen();
	printBoard();
	printWinner();
}

void SeaChess::enterSymbol()
{
	bool valid;
	do {
		cout << "Enter X or O: ";
		cin >> symbol;
		valid = symbol == 'X' || symbol == 'O';
		if (!valid) {
			cout << "Only X or O are allowed!" << endl;
		}
	} while (!valid);

	if (symbol == 'O') {
		otherSymbol = 'X';
	}
	else {
		otherSymbol = 'O';
	}
}

bool SeaChess::isFinished()
{
	bool finished = turns == 9 || winPosition;
	return finished;
}

void SeaChess::checkForWinPosition()
{
	bool diagonalWin1 = board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ';
	bool diagonalWin2 = board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ';

	bool someColWin = false;
	for (int c = 0; c <= 2; c++) {
		bool colWin = board[0][c] == board[1][c] && board[0][c] == board[2][c] && board[0][c] != ' ';
		someColWin = someColWin || colWin;
	}

	bool someRowWin = false;
	for (int r = 0; r <= 2; r++) {
		bool rowWin = board[r][0] == board[r][1] && board[r][0] == board[r][2] && board[r][0] != ' ';
		someRowWin = someRowWin || rowWin;
	}

	winPosition = diagonalWin1 || diagonalWin2 || someColWin || someRowWin;
}

void SeaChess::doStep()
{
	do {
		clearScreen();
		printBoard();
		printPlayer();
		enterPosition();
	} while (!isValidPosition());
	setPosition();
	checkForWinPosition();
}

void SeaChess::printWinner()
{
	bool draw = turns == 9 && !winPosition;

	if (draw) {
		cout << "Draw!";
	}
	else {
		cout << "Winner is ";
		if (turns % 2 == 0) {
			cout << "Player 2 ( " << otherSymbol << " ) ";
		}
		else {
			cout << "Player 1 ( " << symbol << " ) ";
		}
	}
}

void SeaChess::printBoard()
{
	cout << " ";
	for (int i = 0; i < 3; i++) {
		cout << "   " << i;
	}
	cout << endl;

	drawLine();

	for (int r = 0; r < 3; r++) {
		cout << r << " |";
		for (int c = 0; c < 3; c++) {
			cout << " " << board[r][c] << " |";
		}
		cout << endl;
		drawLine();
	}
}

void SeaChess::drawLine()
{
	cout << "  +";
	for (int i = 0; i < 3; i++) {
		cout << "---+";
	}
	cout << endl;
}

void SeaChess::enterPosition()
{
	cout << "Position: ";
	char x, y;
	cin >> x >> y;
	c = x - '0';
	r = y - '0';
}

bool SeaChess::isValidPosition()
{
	bool inRange = r >= 0 && r <= 2 && c >= 0 && c <= 2;
	if (!inRange)
		return false;

	bool freeCell = board[r][c] == ' ';
	if (!freeCell)
		return false;

	return true;
}

void SeaChess::clearScreen()
{
	cout << "\033[2J\033[1;1H";
}

void SeaChess::setPosition()
{
	char positionSymbol = symbol;
	if (turns % 2 == 1) {
		positionSymbol = otherSymbol;
	}
	board[r][c] = positionSymbol;
	turns++;
}

void SeaChess::printPlayer()
{
	if (turns % 2 == 0) {
		cout << "Player 1 ( " << symbol << " ) ";
	}
	else {
		cout << "Player 2 ( " << otherSymbol << " ) ";
	}
}
