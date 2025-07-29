//------------------------------------------------------------------------------
// File: CommandManager.cpp
//
// Implementation of command execution and undo management,
// handling the history stack of game actions.
//------------------------------------------------------------------------------

#include "CommandManager.h"

//-----------------------------------------------------------------------------

void CommandManager::executeCommand(std::unique_ptr<ActionCommand>&& cmd, ChessGame& game)
{
    cmd->execute(game);
    history_.push(std::move(cmd));

} // executeAction

//-----------------------------------------------------------------------------

void CommandManager::undoCommand(ChessGame& game)
{
    if (!history_.empty())
    {
        history_.top()->undo(game);
        history_.pop();
    }

} // undoAction

//-----------------------------------------------------------------------------