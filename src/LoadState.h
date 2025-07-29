//------------------------------------------------------------------------------
// File: LoadState.h
//
// Description:
//	Implements the state responsible for loading saved games from FEN notation.
//
//	Follows the State pattern to manage game flow.
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

class LoadState : public GameState
{
	void enter(GameController& controller) override;
	void handleInput(GameController& controller, const std::string& input) override;

}; // LoadState

//-----------------------------------------------------------------------------