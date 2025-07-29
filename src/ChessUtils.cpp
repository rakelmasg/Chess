//------------------------------------------------------------------------------
// File: ChessUtils.cpp
//
// Implements common chess-related funtions.
//------------------------------------------------------------------------------

#include "ChessUtils.h"
#include "Board.h"
#include "Piece.h"
#include "MoveInfo.h"
#include "Move.h"

//-----------------------------------------------------------------------------

bool ChessUtils::parseSquareToBoardIndex(const Board& board, const std::string& square, int& x, int& y)
{
    if (square.size() != 2)
    {
        return false;
    }

    x = tolower(square[0]) - 'a';
    y = square[1] - '0' - 1;

    if (x < 0 || x > board.sizeX() - 1 || y < 0 || y > board.sizeY() - 1)
    {
        return false;
    }

    return true;

} // parseSquareToBoardIndex

//-----------------------------------------------------------------------------

bool ChessUtils::parseBoardIndexToSquare(const Board& board, int x, int y, std::string& square)
{
    if (x < 0 || x > board.sizeX() - 1 || y < 0 || y > board.sizeY() - 1)
    {
        square = "-";
        return false;
    }

    square.resize(2);
    square[0] = 'a' + x;
    square[1] = '0' + y + 1;

    return true;

} // parseBoardIndexToSquare

//-----------------------------------------------------------------------------

bool ChessUtils::parseSquareCoordsToMove(const Board& board, const std::string& squareFrom, const std::string& squareTo, Move& move)
{
    if (!parseSquareToBoardIndex(board, squareFrom, move.fromX, move.fromY))
    {
        return false;
    }

    if (!parseSquareToBoardIndex(board, squareTo, move.toX, move.toY))
    {
        return false;
    }

    return true;

} // parseSquareCoordsToMove

//-----------------------------------------------------------------------------

bool ChessUtils::hasCastlingRight(const CastlingMask& rights, CastlingRights right)
{
    return rights & right;

} // hasCastlingRight

//-----------------------------------------------------------------------------

std::string ChessUtils::castlingRightsToFEN(const CastlingMask& rights)
{
    std::string fen;

    if (rights & WHITE_KINGSIDE)
    {
        fen += 'K';
    }
    if (rights & WHITE_QUEENSIDE)
    {
        fen += 'Q';
    }
    if (rights & BLACK_KINGSIDE)
    {
        fen += 'k';
    }
    if (rights & BLACK_QUEENSIDE)
    {
        fen += 'q';
    }

    return fen.empty() ? "-" : fen;

} // castlingRightsToFEN

//-----------------------------------------------------------------------------

CastlingMask ChessUtils::castlingRightsFromFEN(const std::string& fen)
{
    CastlingMask rights = NONE;

    for (char c : fen)
    {
        switch (c)
        {
        case 'K':
            rights |= WHITE_KINGSIDE;
            break;
        case 'Q':
            rights |= WHITE_QUEENSIDE;
            break;
        case 'k':
            rights |= BLACK_KINGSIDE;
            break;
        case 'q':
            rights |= BLACK_QUEENSIDE;
            break;
        }
    }

    return rights;

} // castlingRightsFromFEN

//-----------------------------------------------------------------------------

bool ChessUtils::isSquareUnderAttack(const Board& board, int x, int y, bool byWhite, const GameContext& gameCtx)
{
    for (int i = 0; i < board.sizeX(); ++i)
    {
        for (int j = 0; j < board.sizeY(); ++j)
        {
            const Piece* piece = board.getPiece(i, j);
            if (piece && piece->isWhite() == byWhite)
            {
                std::vector<std::pair<Move, MoveInfo>> moves = piece->generateMoves(i, j, piece->isWhite(), board, gameCtx);
                for (const std::pair<Move, MoveInfo>& pair : moves)
                {
                    const Move& move = pair.first;
                    if (move.toX == x && move.toY == y)
                    {
                        return true;
                    }
                }
            }
        }
    }


    return false;

} // isSquareUnderAttack

//-----------------------------------------------------------------------------