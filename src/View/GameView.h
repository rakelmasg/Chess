//------------------------------------------------------------------------------
// File: GameView.h
//
// Description:
//   Handles all user-facing output for the chess application. This includes
//   menu prompts, board rendering, game information, and feedback on invalid
//   inputs. Designed to be a lightweight, presentation-only layer that reads
//   game state and outputs text to the console.
//
// Author: Raquel Mas  
// Created: July 2025  
// License: MIT License (see LICENSE file for details)  
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

#include <string>

//-----------------------------------------------------------------------------

class Board;

//-----------------------------------------------------------------------------

class GameView
{

public:
    //App dislays
    void displayMenu() const;
    void printInvalidOption() const;    
    void printInsertOption() const;
    void printStartingGame() const;
    void printLoadingGame() const;
    void printInsertFENString() const;
    void printInvalidFENFormat() const;
    void printExitApplication() const;

    //Game displays
    void displayBoard(const Board& board) const;
    void printFEN(std::string fenString) const;
    void printTurn(bool isWhite) const;
    void printHalfmoveClock(int num) const;
    void printFullMoveNumber(int num) const;
    void printEnPassant(std::string coord) const;
    void printCastlingRights(std::string castlingRights) const;
    void printInCheckAlert() const;
    void printCheckmate(bool isWhite) const;
    void printStalemate(bool isWhite) const;
    void printDraw() const;
    void printGameover() const;
    void printInsertCommand() const;
    void printInvalidMove() const;
    void printInvalidMoveCheck() const;
    void printInvalidMoveFormat() const;
    void printInsertPromotion() const;
    void printInvalidPromotionType() const;
    void printPromotionInfo(char type) const;

}; // GameView

//-----------------------------------------------------------------------------