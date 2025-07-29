//------------------------------------------------------------------------------
// File: CastlingCommand.h
//
// Description:
//  Implements execution and undo logic for castling moves,
//  managing both the king's and rook's movements.
//
//  Follows the Command pattern to encapsulate this special move action.
//
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

#include "ActionCommand.h"

//-----------------------------------------------------------------------------

class CastlingCommand : public ActionCommand {

private:
    Move rookMove_;
    CastlingRights getCastlingType(bool isWhiteKing, bool kingSide);

public:
    CastlingCommand(const Move& move);

    void execute(ChessGame& game) override;
    void undo(ChessGame& game) override;

}; // CastlingCommand

//-----------------------------------------------------------------------------