//------------------------------------------------------------------------------
// File: Cell.h
//
// Description:
//	Represents a single square on the chessboard.
//	Manages ownership of a Piece and provides operations to set, clear, and
//	retrieve the piece.
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
#include <memory>

//-----------------------------------------------------------------------------

class Piece;

//-----------------------------------------------------------------------------

class Cell : public ChessComponent
{

private:
	std::unique_ptr<Piece> piece_;

public:
	Cell() = default;
	~Cell() override = default;

	void clear();

	void setPiece(std::unique_ptr<Piece> piece);
	bool isEmpty() const;
	const Piece* getPiece() const;
	std::unique_ptr<Piece> takePiece();

	void display() const override;

}; // Cell

//-----------------------------------------------------------------------------