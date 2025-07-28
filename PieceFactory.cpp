//------------------------------------------------------------------------------
// File: PieceFactory.cpp
//
// Implementation of the PieceFactory responsible for creating chess pieces.
//------------------------------------------------------------------------------

#include "PieceFactory.h"
#include "PawnMovement.h"
#include "KnightMovement.h"
#include "RookMovement.h"
#include "BishopMovement.h"
#include "KingMovement.h"
#include "QueenMovement.h"
#include <cctype>

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> PieceFactory::createPieceFEN(char c)
{
    bool isWhite = std::isupper(c);
    return createPiece(std::toupper(c), isWhite);

} // createPieceFEN

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> PieceFactory::createPiece(char type, bool isWhite)
{
    switch (type)
    {
        case 'P': 
            return createPawn(type, isWhite);
        case 'R': 
            return createRook(type, isWhite);
        case 'N': 
            return createKnight(type, isWhite);
        case 'B': 
            return createBishop(type, isWhite);
        case 'Q': 
            return createQueen(type, isWhite);
        case 'K': 
            return createKing(type, isWhite);
        default: 
            return nullptr;
    }

} // createPiece

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> PieceFactory::createPawn(char c, bool isWhite)
{
    static PawnMovement pawnStrategy;
    return std::make_unique<Piece>(isWhite, c, pawnStrategy);

} // createPawn

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> PieceFactory::createRook(char c, bool isWhite)
{
    static RookMovement rookStrategy;
    return std::make_unique<Piece>(isWhite, c, rookStrategy);

} // createRook

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> PieceFactory::createBishop(char c, bool isWhite)
{
    static BishopMovement bishopStrategy;
    return std::make_unique<Piece>(isWhite, c, bishopStrategy);

} // createBishop

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> PieceFactory::createKnight(char c, bool isWhite)
{
    static KnightMovement knightStrategy;
    return std::make_unique<Piece>(isWhite, c, knightStrategy);

} // createKnight

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> PieceFactory::createKing(char c, bool isWhite)
{
    static KingMovement kingStrategy;
    return std::make_unique<Piece>(isWhite, c, kingStrategy);

} // createKing

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> PieceFactory::createQueen(char c, bool isWhite)
{
    static QueenMovement queenStrategy;
    return std::make_unique<Piece>(isWhite, c, queenStrategy);

} // createQueen

//-----------------------------------------------------------------------------