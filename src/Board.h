//------------------------------------------------------------------------------
// File: Board.h
//
// Description:
//	Represents the chessboard as an 8x8 grid of Cells.
//	Manages piece placement, movement, and queries about board state, including
//	tracking king positions.
//
//	Inherits from ChessComponent to support display functionality.
//
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

#include "ChessComponent.h"
#include "Cell.h"
#include "Move.h"
#include <vector>

//-----------------------------------------------------------------------------

class Piece;

//-----------------------------------------------------------------------------

class Board : public ChessComponent
{

public:
	Board() = default;
	~Board() override = default; 
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;

	std::unique_ptr<Board> clone() const;
	void clear();

	static constexpr int BOARD_SIZE = 8;
	virtual int sizeX() const { return BOARD_SIZE; }
	virtual int sizeY() const { return BOARD_SIZE; }

	const Piece* getPiece(int x, int y) const;
	void setPiece(int x, int y, std::unique_ptr<Piece> pice);
	std::unique_ptr<Piece> takePiece(int x, int y);
	std::unique_ptr<Piece> movePiece(Move move);
	bool isValidPosition(int x, int y) const;

	std::pair<int, int> getKingPosition(bool isWhiteKing) const;

	void display() const override;

private:
	Cell cells_[BOARD_SIZE][BOARD_SIZE];

	std::pair<int, int> whiteKing_;
	std::pair<int, int> blackKing_;

	void displayRow(int y, bool whitePerspective) const;

}; // Board

//-----------------------------------------------------------------------------