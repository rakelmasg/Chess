//------------------------------------------------------------------------------
// File: PromotionCommand.h
//
// Description:
//  Implements execution and undo logic for pawn promotion moves, managing
//  replacement of the pawn with the promoted piece.
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

class PromotionCommand : public ActionCommand {
   
private:
    std::unique_ptr<Piece> originalPawn_;
    std::unique_ptr<Piece> promotedPiece_;

public:
    PromotionCommand(const Move& move, std::unique_ptr<Piece>&& promotedPiece_);

    void execute(ChessGame& game) override;
    void undo(ChessGame& game) override;

}; // PromotionCommand

//-----------------------------------------------------------------------------