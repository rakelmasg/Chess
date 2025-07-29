//------------------------------------------------------------------------------
// File: CommandManager.h
//
// Description:
//  Manages execution and undo of ActionCommand objects, maintaining a history
//  stack to support reversible game actions.
//
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

#include <stack>
#include <memory>
#include "ActionCommand.h"

//-----------------------------------------------------------------------------

class ChessGame;

//-----------------------------------------------------------------------------

class CommandManager
{

private:
    std::stack<std::unique_ptr<ActionCommand>> history_;

public:
    void executeCommand(std::unique_ptr<ActionCommand>&& cmd, ChessGame& game);
    void undoCommand(ChessGame& game);

}; // CommandManager

//-----------------------------------------------------------------------------