//------------------------------------------------------------------------------
// File: MoveCommand.h
//
// Description:
//  Implements move execution and undo logic for standard chess moves.
//  Stores necessary state backups to support reversible moves.
//
//  Follows the Command pattern to encapsulate move actions.
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

class MoveCommand : public ActionCommand 
{

private:
    bool checkPossibleEnPassantCapture(int toX, int toY, bool isWhite, const Board& board) const;

public:
    MoveCommand(const Move& move);

    void execute(ChessGame& game) override;
    void undo(ChessGame& game) override;

}; // MoveCommand

//-----------------------------------------------------------------------------
