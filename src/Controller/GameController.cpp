//------------------------------------------------------------------------------
// File: GameController.cpp
//
// Implements the game loop, input handling, and state transitions.
//------------------------------------------------------------------------------

#include "../State/GameState.h"
#include "../State/MainMenuState.h"
#include "GameController.h"
#include <iostream>

//-----------------------------------------------------------------------------

GameController::GameController(GameView& view) : view_(view), chessgame_(), cmdManager_(), currentState_(std::make_unique<MainMenuState>())
{
    currentState_->enter(*this);

} // GameController

//-----------------------------------------------------------------------------

void GameController::run()
{
    std::string input;
    while (std::getline(std::cin, input))
    {
        handleInput(input);
    }

} // run

//-----------------------------------------------------------------------------

void GameController::setState(std::unique_ptr<GameState>&& newState)
{
    currentState_ = std::move(newState);
    currentState_->enter(*this);

} // setState

//-----------------------------------------------------------------------------

void GameController::handleInput(const std::string& input) 
{
    if (currentState_) 
    {
        currentState_->handleInput(*this, input);
    }

} // handleInput

//-----------------------------------------------------------------------------

void GameController::undoAction()
{
    cmdManager_.undoCommand(chessgame_);

} // undoAction

//-----------------------------------------------------------------------------