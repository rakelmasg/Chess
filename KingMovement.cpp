//------------------------------------------------------------------------------
// File: KingMovement.cpp
//
// Implementation of king-specific movement logic.
//------------------------------------------------------------------------------

#include "KingMovement.h"
#include "GameContext.h"
#include "ChessUtils.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"

//-----------------------------------------------------------------------------

MoveInfo KingMovement::analyzeMove(Move move, bool isWhite, const Board& board, const GameContext& gameCtx) const
{
    const Piece* target = board.getPiece(move.toX, move.toY);

    if (target != nullptr && target->isWhite() == isWhite)
    {
        return MoveInfo(false);
    }

    int dx = abs(move.toX - move.fromX);
    int dy = abs(move.toY - move.fromY);

    if (dx <= 1 && dy <= 1) 
    {
        return MoveInfo(true);
    }
   
    if (dy == 0 && dx == 2)
    {
        bool kingSide = move.toX > move.fromX;
        if (canCastle(board, isWhite, kingSide, gameCtx))
        {
            MoveInfo info = MoveInfo(true);
            info.isCastling_ = true;
            return info;
        }
    }

    return MoveInfo(false);

} // analyzeMove

//-----------------------------------------------------------------------------

std::vector<std::pair<Move, MoveInfo>> KingMovement::generateMoves(int fromX, int fromY, bool isWhite, const Board& board, const GameContext& gameCtx) const
{
    static const std::vector<std::pair<int, int>> offsets = 
    {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1}, {1, -1}, 
        {1, 0}, {1, 1}
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

    if (canCastle(board, isWhite, true, gameCtx))
    {
        MoveInfo info = MoveInfo(true);
        info.isCastling_ = true;
        int toX = fromX + 2;
        int toY = fromY;
        Move move{ fromX, fromY, toX, toY };
        pair.emplace_back(move, info);
    }

    if (canCastle(board, isWhite, false, gameCtx))
    {
        MoveInfo info = MoveInfo(true);
        info.isCastling_ = true;
        int toX = fromX - 2;
        int toY = fromY;
        Move move{ fromX, fromY, toX, toY };
        pair.emplace_back(move, info);
    }

    return pair;

} // generateMoves

//-----------------------------------------------------------------------------

bool KingMovement::canCastle(const Board& board, bool isWhiteKing, bool kingSide, const GameContext& gameCtx) const
{
    int y = isWhiteKing ? 0 : 7;
    int kingX = 4;

    int rookX = kingSide ? 7 : 0;
    int dir = kingSide ? 1 : -1;

    CastlingRights right = isWhiteKing 
        ? (kingSide ? CastlingRights::WHITE_KINGSIDE : CastlingRights::WHITE_QUEENSIDE)
        : (kingSide ? CastlingRights::BLACK_KINGSIDE : CastlingRights::BLACK_QUEENSIDE);

    if (ChessUtils::hasCastlingRight(gameCtx.castlingRights_, right) == false)
    {
        return false;
    }

    const Piece* king = board.getPiece(kingX, y);
    const Piece* rook = board.getPiece(rookX, y);

    if (!king || !rook || king->getSymbol() != 'K' || rook->getSymbol() != 'R')
    {
        return false;
    }

    if (king->isWhite() != isWhiteKing || rook->isWhite() != isWhiteKing) 
    {
        return false;
    }

    for (int x = kingX + dir; x != rookX; x += dir)
    {
        if (board.getPiece(x, y) != nullptr) 
        {
            return false;
        }
    }

    for (int i = 0; i <= 2; ++i) 
    {
        int x = kingX + i * dir;
        if (ChessUtils::isSquareUnderAttack(board, x, y, !isWhiteKing, gameCtx))
        {
            return false;
        }
    }

    return true;

} // canCastle

//-----------------------------------------------------------------------------