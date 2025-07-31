//------------------------------------------------------------------------------
// File: MainMenuState.cpp
//
// Implements the logic for the main menu.
//------------------------------------------------------------------------------

#include "../Controller/GameController.h"
#include "LoadState.h"
#include "MainMenuState.h"
#include "PlayingState.h"
#include <iostream>

//-----------------------------------------------------------------------------

void MainMenuState::enter(GameController& controller)
{
    controller.view().displayMenu();
    controller.view().printInsertOption();

} //enter

//-----------------------------------------------------------------------------

void MainMenuState::handleInput(GameController& controller, const std::string& input)
{
    if (input == "1") 
    {
        controller.view().printStartingGame();
        controller.game().initGame();
        controller.setState<PlayingState>();
        return;
    }

    if (input == "2") 
    {
        controller.setState<LoadState>();
        return;
    }

    if (input == "3")
    {
        controller.view().printExitApplication();
        std::exit(0);
        return;
    }

    controller.view().printInvalidOption();
    controller.view().printInsertOption();

} // handleInput

//-----------------------------------------------------------------------------