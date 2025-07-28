//------------------------------------------------------------------------------
// File: LoadState.cpp
//
// Implements the logic for loading saved games from FEN notation.
//------------------------------------------------------------------------------

#include "LoadState.h"
#include "GameController.h"
#include <sstream>
#include "PlayingState.h"

//-----------------------------------------------------------------------------

void LoadState::enter(GameController& controller)
{
    controller.view().printLoadingGame();
    controller.view().printInsertFENString();

} // enter

//-----------------------------------------------------------------------------

void LoadState::handleInput(GameController& controller, const std::string& input)
{
    std::istringstream iss(input);
    std::string boardPart, turnPart, castlingRights, enPassant, halfmoveClockStr, fullmoveNumberStr;

    if (!(iss >> boardPart >> turnPart >> castlingRights >> enPassant >> halfmoveClockStr >> fullmoveNumberStr)) {
        controller.view().printInvalidFENFormat();
        controller.view().printInsertFENString();
        return;
    }

    if (controller.game().initGame(input)) 
    {
        controller.setState<PlayingState>();
    }
    else 
    {
        controller.view().printInvalidFENFormat();
        controller.view().printInsertFENString();
    }

} // handleInput

//-----------------------------------------------------------------------------