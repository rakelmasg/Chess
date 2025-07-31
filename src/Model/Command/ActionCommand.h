//------------------------------------------------------------------------------
// File: ActionCommand.h
//
// Description:
//	Abstract base class for encapsulating chess move logic.
//	Implements the Command pattern to allow applying and reverting moves, with 
//	all necessary state stored internally.
//
//	Enables safe simulation during game analysis (e.g., for check/checkmate
//	detection or move generation).
//
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

#include "../Movement/Move.h"
#include <memory>
#include "../Components/Piece.h"
#include "../../Utils/ChessUtils.h"

//-----------------------------------------------------------------------------

class ChessGame;

//-----------------------------------------------------------------------------

class ActionCommand
{

protected:
	Move move_;
	std::unique_ptr<Piece> capturedPiece_;
	std::pair<int, int> enPassantBackup_;
	CastlingMask castlingRightsBackup_;
	int halfmoveBackup_ = 0;

public:
	ActionCommand(const Move& move);

	virtual void execute(ChessGame& game) = 0;
	virtual void undo(ChessGame& game) = 0;
	virtual ~ActionCommand() = default;

}; // ActionCommand

//-----------------------------------------------------------------------------