//------------------------------------------------------------------------------
// File: GameState.h
//
// Description:
//  Abstract base class representing a game state.
//  Defines the interface for entering the state and handling input.
//
//  Follows the State pattern to enable flexible game flow management.
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

class GameController;

//-----------------------------------------------------------------------------

class GameState {

public:
    virtual void enter(GameController& controller) = 0;
    virtual void handleInput(GameController& controller, const std::string& input) = 0;
    virtual ~GameState() = default;

}; // GameState

//-----------------------------------------------------------------------------