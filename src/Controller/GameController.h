//-----------------------------------------------------------------------------
// File: GameController.h
//
// Description:
//  Central controller responsible for executing the main game loop, managing
//  state transitions, delegating input handling, and coordinating commands.
//
// Author: Raquel Mas
// Date: July 2025
// License: MIT License
// Repository: [add your repository URL here]
//-----------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

#include "../Model/ChessGame.h"
#include "../Model/Command/CommandManager.h"
#include "../State/GameState.h"
#include "../View/GameView.h"

//-----------------------------------------------------------------------------

class GameController
{

private:
    ChessGame chessgame_;
    GameView view_;
    CommandManager cmdManager_;
    std::unique_ptr<GameState> currentState_;

    void setState(std::unique_ptr<GameState>&& newState);

public:
    GameController(GameView& view);

    void run();

    const GameView& view() { return view_; }
    ChessGame& game() { return chessgame_; }

    void handleInput(const std::string& input);

    template<typename T, typename... Args>
    void setState(Args&&... args)
    {
        static_assert(std::is_base_of<GameState, T>::value, "T must derive from GameState");
        setState(std::make_unique<T>(std::forward<Args>(args)...));
    }

    template<typename T, typename... Args>
    void executeAction(Args&&... args)
    {
        static_assert(std::is_base_of<ActionCommand, T>::value, "T must derive from MoveCommand");
        cmdManager_.executeCommand(std::make_unique<T>(std::forward<Args>(args)...), chessgame_);
    }

    void undoAction();

}; // GameController

//-----------------------------------------------------------------------------