//------------------------------------------------------------------------------
// File: GameContext.h
//
// Description:
//  Stores additional game state required to validate special moves, such as en
//  passant captures and castling rights.
//  Passed to movement logic to provide context beyond the board itself.
//
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

#include "ChessUtils.h"

//-----------------------------------------------------------------------------

struct GameContext
{
    std::pair<int, int> enPassant_;
    CastlingMask castlingRights_;

    GameContext(std::pair<int, int> enPassant, CastlingMask castlingRights)
        : enPassant_(enPassant), castlingRights_(castlingRights)
    {

    } // GameContext

}; // GameContext

//-----------------------------------------------------------------------------