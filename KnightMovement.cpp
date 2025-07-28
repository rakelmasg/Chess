//------------------------------------------------------------------------------
// File: KnightMovement.cpp
//
// Implementation of knight-specific movement logic.
//------------------------------------------------------------------------------

#include "KnightMovement.h"
#include "GameContext.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"

//-----------------------------------------------------------------------------

MoveInfo KnightMovement::analyzeMove(Move move, bool isWhite, const Board& board, const GameContext& gameCtx) const
{
    const Piece* target = board.getPiece(move.toX, move.toY);

    if (target != nullptr && target->isWhite() == isWhite)
    {
        return MoveInfo(false);
    }

    int dx = abs(move.toX - move.fromX);
    int dy = abs(move.toY - move.fromY);

    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) 
    {
        return MoveInfo(true);
    }

    return MoveInfo(false);

} // analyzeMove

//-----------------------------------------------------------------------------

std::vector<std::pair<Move, MoveInfo>> KnightMovement::generateMoves(int fromX, int fromY, bool isWhite, const Board& board, const GameContext& gameCtx) const
{
    static const std::vector<std::pair<int, int>> offsets = 
    {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };

    std::vector<std::pair<Move, MoveInfo>> pair;

    for (const std::pair<int, int>& offset : offsets)
    {
        int toX = fromX + offset.first;
        int toY = fromY + offset.second;

        if (!board.isValidPosition(toX, toY))
        {
            continue;
        }

        const Piece* target = board.getPiece(toX, toY);
        if (target == nullptr || target->isWhite() != isWhite)
        {
            MoveInfo info = MoveInfo(true);
            Move move{ fromX, fromY, toX, toY };
            pair.emplace_back(move, info);
        }
    }

    return pair;

} // generateMoves

//-----------------------------------------------------------------------------