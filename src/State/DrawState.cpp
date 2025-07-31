//------------------------------------------------------------------------------
// File: DrawState.cpp
//
// Implements the logic for handling the drawn game state.
//------------------------------------------------------------------------------

#include "../Controller/GameController.h"
#include "DrawState.h"
#include "MainMenuState.h"

//-----------------------------------------------------------------------------

void DrawState::enter(GameController& controller)
{
	controller.view().printDraw();
	controller.view().printGameover();

} // enter

//-----------------------------------------------------------------------------

void DrawState::handleInput(GameController& controller, const std::string& input)
{
	controller.setState<MainMenuState>();

} // handleInput

//-----------------------------------------------------------------------------