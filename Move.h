//------------------------------------------------------------------------------
// File: Move.h
//
// Description:
//  Represents a basic chess movement from one cell to another, with origin and
//  destination coordinates.
//
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------


#pragma once

//-----------------------------------------------------------------------------

struct Move {

    int fromX;
    int fromY;
    int toX;
    int toY;

    Move() = default;
    Move(int fromX, int fromY, int toX, int toY) : fromX(fromX), fromY(fromY), toX(toX), toY(toY){}

}; // Move

//-----------------------------------------------------------------------------