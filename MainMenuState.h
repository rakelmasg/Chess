//------------------------------------------------------------------------------
// File: MainMenuState.h
//
// Description:
//	Game state representing the main menu of the chess application.
//	Handles the initial user input for starting, loading a game, or exiting.
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

class MainMenuState : public GameState
{

public:
    void enter(GameController& controller) override;
    void handleInput(GameController& controller, const std::string& input) override;

}; // MainMenuState

//-----------------------------------------------------------------------------