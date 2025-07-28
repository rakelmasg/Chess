//------------------------------------------------------------------------------
// File: PromotionState.h
//
// Description:
//	Concrete game state responsible for handling pawn promotion.
//	Prompts the player to choose a promotion type, validates the input,
//	and applies the promotion via a command.
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
#include "Move.h"

//-----------------------------------------------------------------------------

class PromotionState : public GameState
{
private:
    Move move_;

public:
    PromotionState(const Move& move);

    void enter(GameController& controller) override;
    void handleInput(GameController& controller, const std::string& input) override;

}; // PromotionState

//-----------------------------------------------------------------------------