//------------------------------------------------------------------------------
// File: CheckmateState.cpp
//
// Implements the logic for handling the checkmate game state.
//------------------------------------------------------------------------------

#include "CheckmateState.h"
#include "GameController.h"
#include "MainMenuState.h"

//-----------------------------------------------------------------------------

void CheckmateState::enter(GameController& controller)
{
	controller.view().printCheckmate(controller.game().isWhiteTurn());
	controller.view().printGameover();

} // enter

//-----------------------------------------------------------------------------

void CheckmateState::handleInput(GameController& controller, const std::string& input)
{
	controller.setState<MainMenuState>();

} // handleInput

//-----------------------------------------------------------------------------