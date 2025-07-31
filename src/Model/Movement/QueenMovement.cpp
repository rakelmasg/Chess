//------------------------------------------------------------------------------
// File: QueenMovement.cpp
//
// Implementation of queen-specific movement logic.
//------------------------------------------------------------------------------

#include "../Components/Board.h"
#include "../Components/Piece.h"
#include "../GameContext.h"
#include "Move.h"
#include "QueenMovement.h"

//-----------------------------------------------------------------------------

MoveInfo QueenMovement::analyzeMove(Move move, bool isWhite, const Board& board, const GameContext& gameCtx) const
{
    const Piece* target = board.getPiece(move.toX, move.toY);

    if (target != nullptr && target->isWhite() == isWhite)
    {
        return MoveInfo(false);
    }

    int dx = move.toX - move.fromX;
    int dy = move.toY - move.fromY;

    if (abs(dx) == abs(dy) || dx == 0 || dy == 0)
    {
        int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
        int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

        int x = move.fromX + stepX;
        int y = move.fromY + stepY;

        while (x != move.toX || y != move.toY)
        {
            if (board.getPiece(x, y) != nullptr)
            {
                return MoveInfo(false);
            }

            x += stepX;
            y += stepY;
        }

        return MoveInfo(true);
    }

    return MoveInfo(false);

} // analyzeMove

//-----------------------------------------------------------------------------

std::vector<std::pair<Move, MoveInfo>> QueenMovement::generateMoves(int fromX, int fromY, bool isWhite, const Board& board, const GameContext& gameCtx) const
{
    static const std::vector<std::pair<int, int>> offsets =
    {
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1},
        {1, 0}, {-1, 0}, {0, -1}, {0, 1}
    };

    std::vector<std::pair<Move, MoveInfo>> pair;

    for (const std::pair<int, int>& offset : offsets)
    {
        int toX = fromX + offset.first;
        int toY = fromY + offset.second;

        while (board.isValidPosition(toX, toY))
        {
            const Piece* target = board.getPiece(toX, toY);

            if (target == nullptr)
            {
                MoveInfo info = MoveInfo(true);
                Move move{ fromX, fromY, toX, toY };
                pair.emplace_back(move, info);
            }
            else
            {
                if (target->isWhite() != isWhite)
                {
                    MoveInfo info = MoveInfo(true);
                    Move move{ fromX, fromY, toX, toY };
                    pair.emplace_back(move, info);
                }
                break;
            }

            toX += offset.first;
            toY += offset.second;
        }
    }

    return pair;

} // generateMoves

//-----------------------------------------------------------------------------