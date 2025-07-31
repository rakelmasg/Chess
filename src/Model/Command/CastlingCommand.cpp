//------------------------------------------------------------------------------
// File: CastlingCommand.cpp
//
// Implementation of castling move execution and undo,
// handling both king and rook movement.
//------------------------------------------------------------------------------

#include "../ChessGame.h"
#include "../GameContext.h"
#include "CastlingCommand.h"

//-----------------------------------------------------------------------------

CastlingCommand::CastlingCommand(const Move& move) 
    : ActionCommand(move)
{

} // CastlingCommand

//-----------------------------------------------------------------------------

void CastlingCommand::execute(ChessGame& game)
{
    const Piece* piece = game.board().getPiece(move_.fromX, move_.fromY);

    enPassantBackup_ = game.getEnPassant();
    castlingRightsBackup_ = game.getCastlingRights();
    halfmoveBackup_ = game.getHalfmoveClock();
   
    game.movePiece(move_); // King move

    bool kingSide = move_.toX > move_.fromX;
    int y = piece->isWhite() ? 0 : 7;

    int rookX = kingSide ? 7 : 0;
    int dir = kingSide ? 1 : -1;

    rookMove_ = Move(rookX, y, move_.toX + dir, y);
    game.movePiece(rookMove_); // Rook move

    CastlingRights right = getCastlingType(piece->isWhite(), kingSide);
    game.removeCastlingRight(right);

    game.setEnPassant({ -1, -1 });
    game.incrementHalfmoveClock();
    game.incrementFullmoveNumber();
    game.addHistoric();
    game.switchTurn();

} // execute

//-----------------------------------------------------------------------------

void CastlingCommand::undo(ChessGame& game)
{
    game.removeHistoric();

    Move reverseKingMove = Move(move_.toX, move_.toY, move_.fromX, move_.fromY);
    game.movePiece(reverseKingMove);

    Move reverseRookMove = Move(rookMove_.toX, rookMove_.toY, rookMove_.fromX, rookMove_.fromY);
    game.movePiece(reverseRookMove);

    game.setEnPassant(enPassantBackup_);
    game.setCastlingRight(castlingRightsBackup_);
    game.restoreHalfmoveClock(halfmoveBackup_);
    game.decrementFullmoveNumber();
    game.switchTurn();

} // undoAction

//-----------------------------------------------------------------------------

CastlingRights CastlingCommand::getCastlingType(bool isWhiteKing, bool kingSide)
{
    if (isWhiteKing) 
    {
        return kingSide ? CastlingRights::WHITE_KINGSIDE : CastlingRights::WHITE_QUEENSIDE;
    }
    else 
    {
        return kingSide ? CastlingRights::BLACK_KINGSIDE : CastlingRights::BLACK_QUEENSIDE;
    }

} // getCastlingType

//-----------------------------------------------------------------------------