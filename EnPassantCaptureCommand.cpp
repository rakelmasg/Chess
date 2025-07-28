//------------------------------------------------------------------------------
// File: EnPassantCaptureCommand.cpp
//
// Implementation of en passant capture execution and undo.
//------------------------------------------------------------------------------

#include "EnPassantCaptureCommand.h"
#include "ChessGame.h"
#include "GameContext.h"

//-----------------------------------------------------------------------------

EnPassantCaptureCommand::EnPassantCaptureCommand(const Move& move) :
    ActionCommand (move)
{

} // MoveCommand

//-----------------------------------------------------------------------------

void EnPassantCaptureCommand::execute(ChessGame& game)
{
    enPassantBackup_ = game.getEnPassant();
    halfmoveBackup_ = game.getHalfmoveClock();

    game.movePiece(move_);
    int capturedY = move_.toY + (game.isWhiteTurn() ? -1 : 1);
    capturedPiece_ = game.replacePiece(move_.toX, capturedY, nullptr);

    game.resetHalfmoveClock();
    game.setEnPassant({-1, -1});
    game.incrementFullmoveNumber();
    game.addHistoric();
    game.switchTurn();

} // execute

//-----------------------------------------------------------------------------

void EnPassantCaptureCommand::undo(ChessGame& game)
{
    game.removeHistoric();

    Move reverseMove = Move(move_.toX, move_.toY, move_.fromX, move_.fromY);
    game.movePiece(reverseMove);

    game.setEnPassant(enPassantBackup_);
    game.restoreHalfmoveClock(halfmoveBackup_);
    game.decrementFullmoveNumber();
    game.switchTurn();

    int capturedY = move_.toY + (game.isWhiteTurn() ? -1 : 1);
    game.replacePiece(move_.toX, capturedY, std::move(capturedPiece_));

} // undoAction

//-----------------------------------------------------------------------------