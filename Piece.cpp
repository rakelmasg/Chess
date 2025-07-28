//------------------------------------------------------------------------------
// File: Piece.cpp
//
// Implementation of the Piece class, representing chess pieces with color,
// symbol, and movement behavior delegated to MovementStrategy.
//------------------------------------------------------------------------------

#include "Piece.h"
#include "MovementStrategy.h"
#include "GameContext.h"
#include "Move.h"
#include <iostream>

//-----------------------------------------------------------------------------

Piece::Piece(const bool isWhite, const char symbol, const MovementStrategy& movement): isWhite_(isWhite), symbol_(symbol), movement_(movement)
{

} // Piece

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> Piece::clone() const
{
	return std::make_unique<Piece>(isWhite_, symbol_, movement_);

} // clone

//-----------------------------------------------------------------------------

char Piece::getSymbol() const
{ 
	return symbol_;

} // getSymbol

//-----------------------------------------------------------------------------

char Piece::getSymbolFEN() const
{
	if (isWhite_)
	{
		return symbol_;
	}
	else
	{
		return (char)std::tolower(symbol_);
	}

} // getSymbolFEN

//-----------------------------------------------------------------------------

MoveInfo Piece::analyzeMove(Move move, const Board& board, const GameContext& gameCtx) const
{ 
	return movement_.analyzeMove(move, isWhite_, board, gameCtx);

} // analyzeMove

//-----------------------------------------------------------------------------

std::vector<std::pair<Move, MoveInfo>> Piece::generateMoves(int fromX, int fromY, bool isWhite, const Board& board, const GameContext& gameCtx) const
{
	return movement_.generateMoves(fromX, fromY, isWhite, board, gameCtx);

} // generateMoves

//-----------------------------------------------------------------------------

void Piece::display() const
{
	if (isWhite_)
	{
		std::cout << "\033[37m " << getSymbolFEN();
	}
	else
	{
		std::cout << "\033[30m " << getSymbolFEN();
	}

	std::cout << "\033[0m";   

} // display

//-----------------------------------------------------------------------------