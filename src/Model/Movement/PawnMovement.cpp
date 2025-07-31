//------------------------------------------------------------------------------
// File: PawnMovement.cpp
//
// Implementation of pawn-specific movement logic.
//------------------------------------------------------------------------------

#include "../Components/Board.h"
#include "../Components/Piece.h"
#include "../GameContext.h"
#include "Move.h"
#include "PawnMovement.h"

//-----------------------------------------------------------------------------

MoveInfo PawnMovement::analyzeMove(Move move, bool isWhite, const Board& board, const GameContext& gameCtx) const
{
    MoveInfo info = MoveInfo(false);
    int direction = isWhite ? 1 : -1;
    int startRow = isWhite ? 1 : 6;

    int dx = move.toX - move.fromX;
    int dy = move.toY - move.fromY;

    const Piece* target = board.getPiece(move.toX, move.toY);

    // Simple move
    if (dx == 0 && target == nullptr)
    {
        if (dy == direction)
        {
            info.isPromotionMove_ = (move.toY == (board.sizeY() - 1));
            info.isValid_ = true;
            return info;
        }

        // Two steps
        if (dy == 2 * direction && move.fromY == startRow && board.getPiece(move.fromX, move.fromY + direction) == nullptr)
        {
            info.isValid_ = true;
            return info;
        }
    }

    // Capture
    if (abs(dx) == 1 && dy == direction)
    {
        if (target != nullptr && target->isWhite() != isWhite) 
        {
            info.isPromotionMove_ = (move.toY == (board.sizeY() - 1));
            info.isValid_ = true;
            return info;
        }

        // EnPassant
        if (target == nullptr && gameCtx.enPassant_.first == move.toX && gameCtx.enPassant_.second == move.toY)
        {
            info.isValid_ = true;
            info.isEnPassantCapture_ = true;
            return info;
        }
    }

    return info;

} // analyzeMove

//-----------------------------------------------------------------------------

std::vector<std::pair<Move, MoveInfo>> PawnMovement::generateMoves(int fromX, int fromY, bool isWhite, const Board& board, const GameContext& gameCtx) const
{
    std::vector<std::pair<Move, MoveInfo>> pair;

    int direction = isWhite ? 1 : -1;
    int startRow = isWhite ? 1 : 6;

    int toY = fromY + direction;

    if (board.isValidPosition(fromX, toY) && board.getPiece(fromX, toY) == nullptr)
    {
        MoveInfo info = MoveInfo(true);
        info.isPromotionMove_ = (toY == (board.sizeY() - 1));
        Move move{ fromX, fromY, fromX, toY};
        pair.emplace_back(move, info);
    }

    int twoStepsY = fromY + 2 * direction;
    if (fromY == startRow && board.getPiece(fromX, fromY + direction) == nullptr && board.getPiece(fromX, twoStepsY) == nullptr)
    {
        MoveInfo info = MoveInfo(true);
        Move move{ fromX, fromY, fromX, twoStepsY };
        pair.emplace_back(move, info);
    }

    for (int dx : {-1, 1})
    {
        int toX = fromX + dx;
        if (!board.isValidPosition(toX, toY)) 
        { 
            continue; 
        }

        const Piece* target = board.getPiece(toX, toY);
        if (target && target->isWhite() != isWhite)
        {
            MoveInfo info = MoveInfo(true);
            info.isPromotionMove_ = (toY == (board.sizeY() - 1));
            Move move{ fromX, fromY, toX, toY };
            pair.emplace_back(move, info);
        }

        // EnPassant
        if (target == nullptr && gameCtx.enPassant_.first == toX && gameCtx.enPassant_.second == toY)
        {
            MoveInfo info = MoveInfo(true);
            info.isEnPassantCapture_ = true;
            Move move{ fromX, fromY, toX, toY };
            pair.emplace_back(move, info);
        }
    }

    return pair;

} // generateMoves

//-----------------------------------------------------------------------------