//------------------------------------------------------------------------------
// File: CheckmateState.cpp
//
// Implements the logic for handling the stalemate game state.
//------------------------------------------------------------------------------

#include "../Controller/GameController.h"
#include "MainMenuState.h"
#include "StalemateState.h"

//-----------------------------------------------------------------------------

void StalemateState::enter(GameController& controller)
{
	controller.view().printStalemate(controller.game().isWhiteTurn());
	controller.view().printGameover();

} // enter

//-----------------------------------------------------------------------------

void StalemateState::handleInput(GameController& controller, const std::string& input)
{
	controller.setState<MainMenuState>();

} // handleInput

//-----------------------------------------------------------------------------