//------------------------------------------------------------------------------
// File: GameView.cpp
//
// Implements user interface display functions for the chess application.
//------------------------------------------------------------------------------

#include "GameView.h"
#include <iostream>

//-----------------------------------------------------------------------------

void GameView::printInvalidOption() const
{
    std::cout << "Invalid option\n";

} // printInvalidOption

//-----------------------------------------------------------------------------

void GameView::printInsertOption() const
{
    std::cout << "\nEnter option: ";

} // printInsertOption

//-----------------------------------------------------------------------------

void GameView::printStartingGame() const
{
    std::cout << "\nNEW GAME STARTED!\n";

} // printStartingGame

//-----------------------------------------------------------------------------

void GameView::printLoadingGame() const
{
    std::cout << "\nLOADING GAME\n";

} // printLoadingGame

//-----------------------------------------------------------------------------

void GameView::printInsertFENString() const
{
    std::cout << "\nEnter load string in FEN format: ";

} // printInsertFENString

//-----------------------------------------------------------------------------

void GameView::printInvalidFENFormat() const
{
    std::cout << "Invalid FEN format.\n";

} // printInvalidFENFormat

//-----------------------------------------------------------------------------

void GameView::printExitApplication() const
{
    std::cout << "\nGOOD BYE!\n";

} // printExitApplication

//-----------------------------------------------------------------------------

void GameView::displayMenu() const
{
    std::cout << "=== CHESS MENU ===\n";
    std::cout << "1. New Game\n";
    std::cout << "2. Load FEN\n";
    std::cout << "3. Quit\n";

} // displayMenu

//-----------------------------------------------------------------------------

void GameView::displayBoard(const Board& board) const
{
    std::cout << "\n     WHITE VIEW           BLACK VIEW\n";
    board.display();
    std::cout << "\n";

} // displayBoard

//-----------------------------------------------------------------------------

void GameView::printFEN(std::string fenString) const
{
    std::cout << "FEN notation: " << fenString << "\n";

} // printFEN

//-----------------------------------------------------------------------------

void GameView::printTurn(bool isWhite) const
{
    std::cout << "Player turn: " << (isWhite ? "White" : "Black") << "\n";

} // printTurn

//-----------------------------------------------------------------------------

void GameView::printHalfmoveClock(int num) const
{
    std::cout << "Halfmove Clock: " << num << "\n";

} // printHalfmoveClock

//-----------------------------------------------------------------------------

void GameView::printFullMoveNumber(int num) const
{
    std::cout << "Fullmove: " << num << "\n";

} // printFullMoveNumber

//-----------------------------------------------------------------------------

void GameView::printEnPassant(std::string coord) const
{
    std::cout << "En Passant: " << coord << "\n";

} // printEnPassant

//-----------------------------------------------------------------------------

void GameView::printCastlingRights(std::string castlingRights) const
{
    std::cout << "Castling Rights: " << castlingRights << "\n";

} // printCastlingRights

//-----------------------------------------------------------------------------

void GameView::printInCheckAlert() const
{
    std::cout << "Your king is in check!\n";

} // printInCheckAlert

//-----------------------------------------------------------------------------

void GameView::printCheckmate(bool isWhite) const
{
    std::cout << "Checkmate! Player " << (!isWhite ? "White" : "Black") << " wins.\n";

} // printCheckmate

//-----------------------------------------------------------------------------

void GameView::printStalemate(bool isWhite) const
{
    std::cout << "Stalemate! Player " << (!isWhite ? "White" : "Black") << " wins.\n";

} // printStalemate

//-----------------------------------------------------------------------------

void GameView::printDraw() const
{
    std::cout << "Draw!\n";

} // printDraw

//-----------------------------------------------------------------------------

void GameView::printGameover() const
{
    std::cout << "GAME OVER. Press enter to return to main menu.\n";

} // printGameover

//-----------------------------------------------------------------------------

void GameView::printInsertCommand() const
{
    std::cout << "\nEnter move (from to) or 'F' to get FEN notation: ";

} // printInsertCommand

//-----------------------------------------------------------------------------

void GameView::printInvalidMove() const
{
    std::cout << "Invalid move.\n";

} // printInvalidMove

//-----------------------------------------------------------------------------

void GameView::printInvalidMoveCheck() const
{
    std::cout << "Invalid move, that move puts your king in check!\n";

} // printInvalidMoveCheck

//-----------------------------------------------------------------------------

void GameView::printInvalidMoveFormat() const
{
    std::cout << "Invalid input format. Use move format like 'e2 e4' or 'F' to get FEN notation.\n";

} // printInvalidMoveFormat

//-----------------------------------------------------------------------------

void GameView::printInsertPromotion() const
{
    std::cout << "\nEnter pawn promotion symbol: ";

} // printInsertPromotion

//-----------------------------------------------------------------------------

void GameView::printInvalidPromotionType() const
{
    std::cout << "Invalid promotion type.\n";

} // printInvalidPromotionType

//-----------------------------------------------------------------------------

void GameView::printPromotionInfo(char type) const
{
    std::cout << "Pawn promoted to ";

    switch (type) {
        case 'Q':
            std::cout << "queen";
            break;
        case 'R':
            std::cout << "rook";
            break;
        case 'B': 
            std::cout << "bishop";
            break;
        case 'N':
            std::cout << "knight";
            break;
        default: 
            break;
    } 

    std::cout << ".\n";

} // printPromotionInfo

//-----------------------------------------------------------------------------