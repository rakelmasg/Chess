//------------------------------------------------------------------------------
// File: CheckmateState.cpp
//
// Implements the logic for handling the stalemate game state.
//------------------------------------------------------------------------------

#include "StalemateState.h"
#include "GameController.h"
#include "MainMenuState.h"

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