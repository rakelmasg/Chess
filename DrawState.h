//------------------------------------------------------------------------------
// File: DrawState.h
//
// Description:
//  Implements the state representing a drawn game.
//
//  Follows the State pattern to manage game flow.
//
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

#include "GameState.h"

//-----------------------------------------------------------------------------

class DrawState : public GameState
{

public:
    void enter(GameController& controller) override;
    void handleInput(GameController& controller, const std::string& input) override;

}; // CheckmateState

//-----------------------------------------------------------------------------