//------------------------------------------------------------------------------
// File: PromotionState.cpp
//
// Implements the logic for handling the promotion game state.
//------------------------------------------------------------------------------

#include "PromotionState.h"
#include "GameController.h"
#include "PieceFactory.h"
#include "PlayingState.h"
#include "PromotionCommand.h"

//-----------------------------------------------------------------------------

PromotionState::PromotionState(const Move& move) : move_(move)
{

} // PromotionState

//-----------------------------------------------------------------------------

void PromotionState::enter(GameController& controller)
{
    controller.view().printInsertPromotion();

} // enter

//-----------------------------------------------------------------------------

void PromotionState::handleInput(GameController& controller, const std::string& input)
{
    if (input.size() != 1) 
    {
        controller.view().printInvalidPromotionType();
        controller.view().printInsertPromotion();
        return;
    }

    char type = std::toupper(input[0]);

    if (!controller.game().isValidPromotionSymbol(type))
    {
        controller.view().printInvalidPromotionType();
        controller.view().printInsertPromotion();
        return;
    }

    controller.executeAction<PromotionCommand>(move_, PieceFactory::createPiece(type, controller.game().isWhiteTurn()));

    controller.view().printPromotionInfo(type);

    controller.setState<PlayingState>();

} // handleInput

//-----------------------------------------------------------------------------