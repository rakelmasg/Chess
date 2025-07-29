//------------------------------------------------------------------------------
// File: MoveInfo.h
//
// Description:
//  Stores metadata about a move's validity and special move types.
//  Used to indicate if a move is legal and whether it involves promotion, en 
//  passant, or castling.
//
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

struct MoveInfo {

    bool isValid_ = false;
    bool isPromotionMove_ = false;
    bool isEnPassantCapture_ = false;
    bool isCastling_ = false;

    MoveInfo(bool isValid) : isValid_(isValid)
    {

    } // MoveInfo

}; // MoveInfo

//-----------------------------------------------------------------------------