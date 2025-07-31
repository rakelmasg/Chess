//------------------------------------------------------------------------------
// File: GameApplication.cpp
//
// Entry point for the chess game application.
//------------------------------------------------------------------------------

#include "GameApplication.h"
#include "View/GameView.h"
#include "Controller/GameController.h"

//-----------------------------------------------------------------------------

void GameApplication::run()
{
    GameView view;
    GameController controller(view);
    controller.run();

} // run

//-----------------------------------------------------------------------------