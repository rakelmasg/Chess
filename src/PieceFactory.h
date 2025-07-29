//------------------------------------------------------------------------------
// File: PieceFactory.cpp
//
// Description:
//  Implementation of the PieceFactory responsible for creating chess pieces
//  from FEN notation or explicit type and color.
//
//  Follows the Factory Method pattern to encapsulate the creation logic for
//  different types of chess pieces.
//
//  Applies the Flyweight pattern by using static shared instances of each 
//  MovementStrategy.
//
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

#include "Piece.h"
#include <memory>

//-----------------------------------------------------------------------------

class PieceFactory
{

public:
    static std::unique_ptr<Piece> createPieceFEN(char c);
    static std::unique_ptr<Piece> createPiece(char type, bool isWhite);

private:
    static std::unique_ptr<Piece> createPawn(char c, bool isWhite);
    static std::unique_ptr<Piece> createRook(char c, bool isWhite);
    static std::unique_ptr<Piece> createBishop(char c, bool isWhite);
    static std::unique_ptr<Piece> createKnight(char c, bool isWhite);
    static std::unique_ptr<Piece> createKing(char c, bool isWhite);
    static std::unique_ptr<Piece> createQueen(char c, bool isWhite);

}; // PieceFactory

//-----------------------------------------------------------------------------