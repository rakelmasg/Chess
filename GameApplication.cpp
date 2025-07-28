//------------------------------------------------------------------------------
// File: GameApplication.cpp
//
// Entry point for the chess game application.
//------------------------------------------------------------------------------

#include "GameApplication.h"
#include "GameView.h"
#include "GameController.h"

//-----------------------------------------------------------------------------

void GameApplication::run()
{
    GameView view;
    GameController controller(view);
    controller.run();

} // run

//-----------------------------------------------------------------------------