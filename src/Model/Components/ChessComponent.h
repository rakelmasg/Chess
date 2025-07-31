//------------------------------------------------------------------------------
// File: ChessComponent.h
//
// Description:
//	Abstract interface for all drawable chess-related components.
//
//	Follows the Composite design pattern, allowing individual components or 
//  compositions of components to be treated uniformly.
//
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

class ChessComponent
{

public:
	virtual void display() const = 0;
	virtual ~ChessComponent() {}

}; // ChessComponent

//-----------------------------------------------------------------------------