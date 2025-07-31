//------------------------------------------------------------------------------
// File: Cell.cpp
//
// Implementation of the Cell class, managing individual squares on the chessboard,
// including piece ownership and display behavior.
//------------------------------------------------------------------------------

#include "Cell.h"
#include "Piece.h"
#include <iostream>

//-----------------------------------------------------------------------------

void Cell::clear()
{
	piece_.reset();

} // clear

//-----------------------------------------------------------------------------

void Cell::setPiece(std::unique_ptr<Piece> piece)
{
	piece_ = std::move(piece);

} // setPiece

//-----------------------------------------------------------------------------

bool Cell::isEmpty() const
{
	return piece_ == nullptr;

} // isEmpty

//-----------------------------------------------------------------------------

const Piece* Cell::getPiece() const
{
	return piece_.get();

} // getPiece

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> Cell::takePiece()
{
	return std::move(piece_);

} // takePiece

//-----------------------------------------------------------------------------

void Cell::display() const
{
	//if (visualHint_)
	//	std::cout << "\033[42m";  // green bg
	

	if (isEmpty())
	{
		std::cout << "  ";
	}
	else
	{
		piece_.get()->display();
	}

	//std::cout << "\033[0m"; // reset color

} // display

//-----------------------------------------------------------------------------