//------------------------------------------------------------------------------
// File: PromotionCommand.cpp
//
// Implementation of pawn promotion execution and undo,
// handling the replacement of the pawn with the promoted piece.
//------------------------------------------------------------------------------

#include "PromotionCommand.h"
#include "ChessGame.h"
#include "GameContext.h"

//-----------------------------------------------------------------------------

PromotionCommand::PromotionCommand(const Move& move, std::unique_ptr<Piece>&& promotedPiece_):
    ActionCommand(move), promotedPiece_(std::move(promotedPiece_))
{
    
} // PromotionCommand

//-----------------------------------------------------------------------------

void PromotionCommand::execute(ChessGame& game)
{
    enPassantBackup_ = game.getEnPassant();
    halfmoveBackup_ = game.getHalfmoveClock();
    capturedPiece_ = game.movePiece(move_);
    originalPawn_ = game.replacePiece(move_.toX, move_.toY, std::move(promotedPiece_));

    game.setEnPassant({-1,-1});
    game.resetHalfmoveClock();
    game.incrementFullmoveNumber();
    game.addHistoric();
    game.switchTurn();

} // execute

//-----------------------------------------------------------------------------

void PromotionCommand::undo(ChessGame& game)
{
    game.removeHistoric();

    game.replacePiece(move_.fromX, move_.fromY, std::move(originalPawn_));
    game.replacePiece(move_.toX, move_.toY, std::move(capturedPiece_));

    game.setEnPassant({enPassantBackup_});
    game.restoreHalfmoveClock(halfmoveBackup_);
    game.decrementFullmoveNumber();
    game.switchTurn();

} // undoAction

//-----------------------------------------------------------------------------