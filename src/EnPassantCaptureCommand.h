//------------------------------------------------------------------------------
// File: EnPassantCaptureCommand.h
//
// Description:
//  Implements execution and undo logic for en passant capture moves.
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

class EnPassantCaptureCommand : public ActionCommand {

public:
    EnPassantCaptureCommand(const Move& move);

    void execute(ChessGame& game) override;
    void undo(ChessGame& game) override;

}; // EnPassantCaptureCommand

//-----------------------------------------------------------------------------
