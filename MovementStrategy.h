//------------------------------------------------------------------------------
// File: MovementStrategy.h
//
// Description:
//	Abstract interface for piece-specific movement logic.
//	Defines how a piece validates moves and generates legal options based on 
//  board state and game context.
//
//  Implements the Strategy design pattern to allow flexible and interchangeable 
//	movement rules for different chess pieces.
// 
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

#include <vector>

//-----------------------------------------------------------------------------

class Board;
struct Move;
struct MoveInfo;
struct GameContext;

//-----------------------------------------------------------------------------

class MovementStrategy
{

public:
    virtual MoveInfo analyzeMove(Move move, bool isWhite, const Board& board, const GameContext& gameCtx) const = 0;
	virtual std::vector<std::pair<Move, MoveInfo>> generateMoves(int fromX, int fromY, bool isWhite, const Board& board, const GameContext& gameCtx) const = 0;
	virtual ~MovementStrategy() {}

}; // MovementStrategy

//-----------------------------------------------------------------------------