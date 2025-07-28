//------------------------------------------------------------------------------
// File: Piece.h
//
// Description:
//	Represents a chess piece with its color, symbol, and movement behavior.
//	Delegates move validation and generation to a MovementStrategy.
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
#include "MoveInfo.h"
#include <vector>
#include <memory>

//-----------------------------------------------------------------------------

class MovementStrategy;
class Board;
struct GameContext;
struct Move;

//-----------------------------------------------------------------------------

class Piece : public ChessComponent
{

protected:
	bool isWhite_;
	char symbol_;
	const MovementStrategy& movement_;

public:
	Piece(const bool isWhite, const char symbol, const MovementStrategy& movement);
	~Piece() override = default;

	std::unique_ptr<Piece> clone() const;

	bool isWhite() const { return isWhite_; }
	char getSymbol() const;
	char getSymbolFEN() const;
	MoveInfo analyzeMove(Move move, const Board& board, const GameContext& gameCtx) const;
	std::vector<std::pair<Move, MoveInfo>> generateMoves(int fromX, int fromY, bool isWhite, const Board& board, const GameContext& gameCtx) const;

	void display() const override;

}; // Piece

//-----------------------------------------------------------------------------