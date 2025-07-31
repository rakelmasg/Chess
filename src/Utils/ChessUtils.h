//------------------------------------------------------------------------------
// File: ChessUtils.h
//
// Description:
//  Utility class providing static helper functions for parsing board positions,
//  move conversion, and handling castling rights in FEN notation.
//
//  Encapsulates common chess-related operations used throughout the game logic.
//
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

#include <string>

//-----------------------------------------------------------------------------

class Board;
struct GameContext;
struct Move;

//-----------------------------------------------------------------------------

enum CastlingRights : uint8_t
{
    NONE = 0,
    WHITE_KINGSIDE = 1 << 0,
    WHITE_QUEENSIDE = 1 << 1,
    BLACK_KINGSIDE = 1 << 2,
    BLACK_QUEENSIDE = 1 << 3

}; // CastlingRights

//-----------------------------------------------------------------------------

using CastlingMask = uint8_t;

//-----------------------------------------------------------------------------

class ChessUtils
{

public:
    static bool parseSquareToBoardIndex(const Board& board, const std::string& square, int& x, int& y);
    static bool parseBoardIndexToSquare(const Board& board, int x, int y, std::string& square);
    static bool parseSquareCoordsToMove(const Board& board, const std::string& squareFrom, const std::string& squareTo, Move& move);

    static bool hasCastlingRight(const CastlingMask& rights, CastlingRights right);
    static std::string castlingRightsToFEN(const CastlingMask& rights);
    static CastlingMask castlingRightsFromFEN(const std::string& fen);

    static bool isSquareUnderAttack(const Board& board, int x, int y, bool byWhite, const GameContext& gameCtx);

}; // ChessUtils

//-----------------------------------------------------------------------------