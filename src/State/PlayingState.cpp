//------------------------------------------------------------------------------
// File: PlayingState.cpp
//
// Implements the gameplay state logic including move validation,
// special move handling, command execution, and game status updates.
//------------------------------------------------------------------------------

#include "../Controller/GameController.h"
#include "../Model/ChessGame.h"
#include "../Model/Command/CastlingCommand.h"
#include "../Model/Command/EnPassantCaptureCommand.h"
#include "../Model/Command/MoveCommand.h"
#include "../Model/GameContext.h"
#include "CheckmateState.h"
#include "DrawState.h"
#include "PlayingState.h"
#include "PromotionState.h"
#include "StalemateState.h"
#include <sstream>

//-----------------------------------------------------------------------------

void PlayingState::updateGameStatus(GameController& controller)
{
    ChessGame& game = controller.game();
    controller.view().displayBoard(game.board());

    // Check status
    switch (game.getGameStatus())
    {
    case GameStatus::Checkmate:
        controller.setState<CheckmateState>();
        return;
    case GameStatus::Stalemate:
        controller.setState<StalemateState>();
        return;
    case GameStatus::Draw:
        controller.setState<DrawState>();
        return;
    case GameStatus::Check:
        controller.view().printInCheckAlert();
        break;
    default:
        break;
    }

    controller.view().printFullMoveNumber(game.getfullmoveNumber());
    controller.view().printHalfmoveClock(game.getHalfmoveClock());
    std::string passant;
    ChessUtils::parseBoardIndexToSquare(game.board(), game.getEnPassant().first, game.getEnPassant().second, passant);
    controller.view().printEnPassant(passant);
    controller.view().printCastlingRights(ChessUtils::castlingRightsToFEN(game.getCastlingRights()));
    controller.view().printTurn(controller.game().isWhiteTurn());
    controller.view().printInsertCommand();

} // updateGameStatus

//-----------------------------------------------------------------------------

void PlayingState::enter(GameController& controller)
{
    updateGameStatus(controller);

} // enter

//-----------------------------------------------------------------------------

void PlayingState::handleInput(GameController& controller, const std::string& input)
{
    ChessGame& game = controller.game();
    const GameView& view = controller.view();

    if (input == "F" || input == "f")
    {
        view.printFEN(game.getFEN());
        view.printInsertCommand();
        return;
    }

    std::istringstream iss(input);
    std::string from, to;
    if (!(iss >> from >> to)) 
    {
        view.printInvalidMoveFormat();
        view.printInsertCommand();
        return;
    }

    // Parse coordinates to index
    Move move;
    if (!ChessUtils::parseSquareCoordsToMove(game.board(), from, to, move))
    {
        view.printInvalidMoveFormat();
        view.printInsertCommand();
        return;
    }

    GameContext gameCtx = GameContext(game.getEnPassant(), game.getCastlingRights());
    MoveInfo moveInfo = game.analyzeMove(move, gameCtx);
    if (moveInfo.isValid_ == false)
    {
        view.printInvalidMove();
        view.printInsertCommand();
        return;
    }

    // Verify move does not cause check
    if (!game.isMoveSafe(move, moveInfo))
    {
        view.printInvalidMoveCheck();
        view.printInsertCommand();
        return;
    }

    // Promotion state
    if (moveInfo.isPromotionMove_)
    {
        controller.setState<PromotionState>(move);
        return;
    }

    //Passant Move
    if (moveInfo.isEnPassantCapture_)
    {
        controller.executeAction<EnPassantCaptureCommand>(move);
    }
    else if (moveInfo.isCastling_) // Castling Move
    {
        controller.executeAction<CastlingCommand>(move);
    }
    else // Regular Move
    {
        controller.executeAction<MoveCommand>(move);
    }    
   
    updateGameStatus(controller);

} // handleInput

//-----------------------------------------------------------------------------