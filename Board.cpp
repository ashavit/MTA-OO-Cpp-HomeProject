#include <string>
#include <iostream>
#include <list>
#include "Commons.h"
#include "Board.h"
#include "Cell.h"
#include "Utils.h"

using namespace std;

//*********** Life Cycle ***********//

int Board::aliveIns = 0;

Board::Board(UINT width, UINT height) : height(height), width(width) {
	aliveIns++;
	board = new Cell**[width];
	for (UINT col = 0; col < width; ++col) {
		board[col] = new Cell*[height];
		for (UINT row = 0; row < height; ++row) {
			board[col][row] = new Cell(row, col);
		}
	}

	UINT temp = width;
	rowLabelsSpace = 1;
	while (temp) {
		++rowLabelsSpace;
		temp /= 10;
	}
}

Board::~Board() {
	aliveIns--;
	for (UINT col = 0; col < width; ++col) {
		for (UINT row = 0; row < height; ++row) {
			delete board[col][row];
		}
		delete board[col];
	}
	delete board;
}

//*********** Public functions ***********//

Cell* Board::getRandomCellInRows(size_t from, size_t to) const {
	Cell* ptrRes = nullptr;
	size_t range = to - from + 1;

	do {
		int r = static_cast<int>((rand() % range) + from - 1);
		int c = rand() % width;
		Cell * ptrTemp = board[c][r];
		if (ptrTemp && ptrTemp->getCellType() == CellType::REGULAR && ptrTemp->getStandingShip() == nullptr) {
			ptrRes = ptrTemp;;
		}
	}
	while (ptrRes == nullptr);
	return ptrRes;
}

Cell* Board::getNextCell(const Cell* cell, Direction direction) const {
	int r = cell->row;
	int c = cell->column;

	switch (direction) {
	case Direction::UP:
		r--;
		break;
	case Direction::DOWN:
		r++;
		break;
	case Direction::LEFT:
		c--;
		break;
	case Direction::RIGHT:
		c++;
		break;
	default:
		break;
	}

	if (c >= 0 && c < width &&
		r >= 0 && r < height) {
		return board[c][r];
	}
	return nullptr;
}

//*********** Outputs ***********//

void Board::drawBoard() const {
	clearScreen();
	for (int column = 0; column < width; ++column) {
		gotoxy(column + rowLabelsSpace, 0);
		std::cout << static_cast<char>('A' + column);
	}
	for (int row = 1; row <= height; ++row) {
		gotoxy(0, row);
		std::cout << row;
	}
	std::cout.flush();

	for (int column = 0; column < width; ++column) {
		for (int row = 0; row < height; ++row) {
			Cell * cell = board[column][row];
			drawCell(cell);
		}
	}
}

void Board::drawCell(Cell* cell) const {
	gotoxy(cell->column + rowLabelsSpace, cell->row + 1);

	char ch = cell->charRepresentation();
	switch (ch) {
	case BOARD_MARK_SEA:
		setTextColor(YELLOW, BLUE);
		break;
	case BOARD_MARK_FOREST:
		setTextColor(BLUE, GREEN);
		break;
	case BOARD_MARK_FLAG_A:
		setTextColor(BLACK, RED);
		break;
	case BOARD_MARK_FLAG_B:
		setTextColor(BLACK, YELLOW);
		break;
	case CellType::REGULAR:
		setTextColor(WHITE, WHITE);
		break;
	default:
		setTextColor(BLACK, GREY);
	}

	cout << ch;
	cout.flush();
}

void Board::printMessage(const string message, bool onFullScreen, int indent, int rowsDown) const {
	setTextColor(WHITE);
	if (onFullScreen) {
		clearScreen();
		gotoxy(indent, rowsDown);
	}
	else {
		gotoxy(indent, height + rowsDown);
	}
	cout << message << endl;
}

int Board::getPlayerStatsLocation() const {
	return rowLabelsSpace + width + scoreBoardIndentation;
}

//*********** Private functions ***********//

void Board::randomPlaceSpecialCells(CellType type, int count) const {
	for (int i = 0; i < count; ++i) {
		getRandomCellInRows(1, height)->setCellType(type);
	}
}
