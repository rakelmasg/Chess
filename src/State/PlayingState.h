//------------------------------------------------------------------------------
// File: PlayingState.h
//
// Description:
//  Implements the gameplay state responsible for processing player inputs,
//  validating moves, handling special move types (promotion, en passant, castling),
//  executing commands, and updating the game status accordingly.
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

class PlayingState : public GameState
{

private:
    void updateGameStatus(GameController& controller);

public:
    void enter(GameController& controller) override;
    void handleInput(GameController& controller, const std::string& input) override;


}; // PlayingState

//-----------------------------------------------------------------------------