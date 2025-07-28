//------------------------------------------------------------------------------
// File: MoveCommand.cpp
//
// Implementation of move execution and undo for standard chess moves,
// maintaining state backups for safe reversal.
//------------------------------------------------------------------------------

#include "MoveCommand.h"
#include "ChessGame.h"
#include "GameContext.h"
#include "ChessUtils.h"

//-----------------------------------------------------------------------------

MoveCommand::MoveCommand(const Move& move) : ActionCommand(move)
{

} // MoveCommand

//-----------------------------------------------------------------------------

void MoveCommand::execute(ChessGame& game)
{
    const Piece* piece = game.board().getPiece(move_.fromX, move_.fromY);

    enPassantBackup_ = game.getEnPassant();
    castlingRightsBackup_ = game.getCastlingRights();
    halfmoveBackup_ = game.getHalfmoveClock();
    capturedPiece_ = game.movePiece(move_);

    // King
    if (piece->getSymbol() == 'K')
    {
        if (piece->isWhite())
        {
            game.removeCastlingRight(CastlingRights::WHITE_KINGSIDE);
            game.removeCastlingRight(CastlingRights::WHITE_QUEENSIDE);
        }
        else
        {
            game.removeCastlingRight(CastlingRights::BLACK_KINGSIDE);
            game.removeCastlingRight(CastlingRights::BLACK_QUEENSIDE);
        }
    }

    // Rook
    if (piece->getSymbol() == 'R')
    {
        if (piece->isWhite())
        {
            if (move_.fromX == 0 && move_.fromY == 0)
            {
                game.removeCastlingRight(CastlingRights::WHITE_QUEENSIDE);
            }
            else if (move_.fromX == 7 && move_.fromY == 0)
            {
                game.removeCastlingRight(CastlingRights::WHITE_KINGSIDE);
            }
        }
        else
        {
            if (move_.fromX == 0 && move_.fromY == 7)
            {
                game.removeCastlingRight(CastlingRights::BLACK_QUEENSIDE);
            }
            else if (move_.fromX == 7 && move_.fromY == 7)
            {
                game.removeCastlingRight(CastlingRights::BLACK_KINGSIDE);
            }
        }
    }

    // Pawn
    if (piece->getSymbol() == 'P')
    {
        if (abs(move_.toY - move_.fromY) == 2 && checkPossibleEnPassantCapture(move_.toX, move_.toY, piece->isWhite(), game.board()))
        {
            int direction = piece->isWhite() ? 1 : -1;
            game.setEnPassant({ move_.toX, move_.toY - direction });
        }
        else
        {
            game.setEnPassant({ -1, -1 });
        }

        game.resetHalfmoveClock();
    }
    else 
    {
        game.setEnPassant({ -1, -1 });

        if (capturedPiece_)
        {
            game.resetHalfmoveClock();
        }
        else
        {
            game.incrementHalfmoveClock();

        }
    }
   
    game.incrementFullmoveNumber();
    game.addHistoric();
    game.switchTurn();

} // execute

//-----------------------------------------------------------------------------

void MoveCommand::undo(ChessGame& game) 
{
    game.removeHistoric();

    Move reverseMove = Move(move_.toX, move_.toY, move_.fromX, move_.fromY);

    game.movePiece(reverseMove);
    game.replacePiece(move_.toX, move_.toY, std::move(capturedPiece_));

    game.setEnPassant(enPassantBackup_);
    game.setCastlingRight(castlingRightsBackup_);
    game.restoreHalfmoveClock(halfmoveBackup_);
    game.decrementFullmoveNumber();
    game.switchTurn();
        
} // undoAction

//-----------------------------------------------------------------------------

bool MoveCommand::checkPossibleEnPassantCapture(int toX, int toY, bool isWhite, const Board& board) const
{
    const Piece* leftPiece = board.getPiece(toX - 1, toY);
    const Piece* rightPiece = board.getPiece(toX + 1, toY);

    if (leftPiece && leftPiece->isWhite() != isWhite && leftPiece->getSymbol() == 'P')
    {
        return true;
    }

    if (rightPiece && rightPiece->isWhite() != isWhite && rightPiece->getSymbol() == 'P')
    {
        return true;
    }

    return false;

} // checkPossibleEnPassantCapture

//-----------------------------------------------------------------------------