//------------------------------------------------------------------------------
// File: Board.cpp
//
// Implementation of the Board class, handling the 8x8 grid of Cells,
// piece placement, movement, and board state queries.
//------------------------------------------------------------------------------

#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include <iostream>

//-----------------------------------------------------------------------------

std::unique_ptr<Board> Board::clone() const
{
	auto cloneBoard = std::make_unique<Board>();

	for (int x = 0; x < BOARD_SIZE; ++x)
	{
		for (int y = 0; y < BOARD_SIZE; ++y)
		{
			const Piece* piece = getPiece(x, y);
			if (piece)
			{
				cloneBoard->setPiece(x, y, piece->clone());
			}
		}
	}

	return cloneBoard;

} // clone

//-----------------------------------------------------------------------------

void Board::clear()
{
	for (int y = 0; y < BOARD_SIZE; ++y) 
	{
		for (int x = 0; x < BOARD_SIZE; ++x)
		{
			cells_[x][y].clear();
		}
	}

	whiteKing_ = { -1, -1 };
	blackKing_ = { -1, -1 };

} // clear

//-----------------------------------------------------------------------------

const Piece* Board::getPiece(int x, int y) const
{
	if (isValidPosition(x, y)) 
	{
		return cells_[x][y].getPiece();
	}

	return nullptr;

} // getPiece

//-----------------------------------------------------------------------------

void Board::setPiece(int x, int y, std::unique_ptr<Piece> piece)
{
	if (isValidPosition(x, y))
	{
		if (piece->getSymbol() == 'K') 
		{
			if (piece->isWhite()) 
			{
				whiteKing_ = {x, y};
			}
			else
			{
				blackKing_ = {x, y};
			}
		}

		cells_[x][y].setPiece(std::move(piece));
	}

} // setPiece

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> Board::takePiece(int x, int y)
{
	if (isValidPosition(x, y))
	{
		return cells_[x][y].takePiece();
	}

	return nullptr;

} // takePiece

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> Board::movePiece(Move move)
{
	std::unique_ptr<Piece> capturedPiece = takePiece(move.toX, move.toY);
	setPiece(move.toX, move.toY, takePiece(move.fromX, move.fromY));

	return capturedPiece;

} // movePiece

//-----------------------------------------------------------------------------

bool Board::isValidPosition(int x, int y) const
{
	if (x < 0 || x >= sizeX() || y < 0 || y >= sizeY())
	{
		return false;
	}
	
	return true;

} // isValidPosition

//-----------------------------------------------------------------------------

std::pair<int, int> Board::getKingPosition(bool isWhiteKing) const
{
	if (isWhiteKing) 
	{
		return whiteKing_;
	}
	else 
	{
		return blackKing_;
	}

} // getKingPosition

//-----------------------------------------------------------------------------

void Board::display() const
{
    for (int y = sizeY() - 1; y >= 0; --y)
    {
        //White
        std::cout << (y + 1) << " ";
        displayRow(y, true);

        std::cout << "   ";

        //Black
        std::cout << (sizeY() - y) << " ";
        displayRow(sizeY() - 1 - y, false);

        std::cout << "\n";
    }

    std::cout << "  ";
	for (int x = 0; x < sizeX(); ++x)
	{
		std::cout << " " << static_cast<char>('A' + x);
	}

    std::cout << "     ";

	for (int x = sizeX() - 1; x >= 0; --x)
	{
		std::cout << " " << static_cast<char>('A' + x);
	}

    std::cout << "\n";

} // display

//-----------------------------------------------------------------------------

void Board::displayRow(int y, bool whitePerspective) const
{
    bool isWhiteCell = (y % 2 == 0);

    if (whitePerspective)
    {
        for (int x = 0; x < sizeX(); ++x)
        {
            std::cout << (isWhiteCell ? "\033[43m" : "\033[46m");
            cells_[x][y].display();
            std::cout << "\033[0m";
            isWhiteCell = !isWhiteCell;
        }
    }
    else
    {
        for (int x = sizeX() - 1; x >= 0; --x)
        {
            std::cout << (isWhiteCell ? "\033[43m" : "\033[46m");
            cells_[x][y].display();
            std::cout << "\033[0m";
            isWhiteCell = !isWhiteCell;
        }
    }

} // displayRow

//-----------------------------------------------------------------------------