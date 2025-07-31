//------------------------------------------------------------------------------
// File: KnightMovement.h
//
// Description:
//	Implements movement logic specific to the knight piece.
// 
//	Follows the Strategy pattern to encapsulate knight-specific rules for move
//  validation and generation.
// 
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

#include "MovementStrategy.h"

//-----------------------------------------------------------------------------

class KnightMovement : public MovementStrategy
{

public:
	MoveInfo analyzeMove(Move move, bool isWhite, const Board& board, const GameContext& gameCtx) const override;
	std::vector<std::pair<Move, MoveInfo>> generateMoves(int fromX, int fromY, bool isWhite, const Board& board, const GameContext& gameCtx) const override;

}; // KnightMovement

//-----------------------------------------------------------------------------

