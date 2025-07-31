//------------------------------------------------------------------------------
// File: ChessGame.h
//
// Description:
//   Core class managing the chess game state, including board representation,
//   move validation, turn management, special rules (castling, en passant,
//   promotion), and game status detection (check, checkmate, stalemate, draw).
//
// Author: Raquel Mas
// Created: July 2025
// License: MIT License (see LICENSE file for details)
// Repository: 
//------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------

#include "../Utils/ChessUtils.h"
#include "Components/Board.h"
#include "Movement/MoveInfo.h"
#include <set>
#include <string>
#include <unordered_map>

//-----------------------------------------------------------------------------

enum class GameStatus
{
    Playing,
    Check,
    Checkmate,
    Stalemate,
    Draw,

}; //GameStatus

//-----------------------------------------------------------------------------

class ChessGame
{

private:
    std::unique_ptr<Board> board_;
    bool isWhiteTurn_;
    int halfmoveClock_;  
    int fullmoveNumber_;
    std::pair<int, int> enPassant_;
    CastlingMask castlingRights_ = CastlingRights::NONE;

    std::unordered_map<std::string, int> historic;

    virtual std::string getDefaultFEN() const;
    bool initBoardFromFEN(const std::string& fen);

public:
    ChessGame();

    std::unique_ptr<ChessGame> clone() const;

    bool initGame();
    bool initGame(const std::string& fen);

    std::string getFEN() const;
    std::string getPartialFEN() const;

    const Board& board() const { return *board_; }
    bool isWhiteTurn() const { return isWhiteTurn_; }
    int getHalfmoveClock() const { return halfmoveClock_; }
    int getfullmoveNumber() const { return fullmoveNumber_; }
    const std::pair<int, int> getEnPassant() const { return enPassant_; }
    const CastlingMask getCastlingRights() const { return castlingRights_; }

    void switchTurn();

    void incrementHalfmoveClock();
    void resetHalfmoveClock();
    void restoreHalfmoveClock(int value);

    void incrementFullmoveNumber();
    void decrementFullmoveNumber();

    void setEnPassant(const std::pair<int, int> enPassant);
    void setCastlingRight(CastlingMask rights);
    void removeCastlingRight(CastlingRights right);

    virtual const std::set<char>& getValidPromotionSymbols() const;
    virtual bool isValidPromotionSymbol(char symbol) const;

    MoveInfo analyzeMove(Move move, const GameContext& gameCtx);
    std::unique_ptr<Piece> movePiece(Move move);
    std::unique_ptr<Piece> replacePiece(int x, int y, std::unique_ptr<Piece> newPiece);

    bool isMoveSafe(const Move& move, const MoveInfo& info) const;
    bool isMoveSafe(ChessGame& cloneGame, const Move& move, const MoveInfo& info) const;

    GameStatus getGameStatus() const;
    bool isInCheck(const Board& board, bool isWhiteKing) const;
    bool isCheckmate() const;
    bool isStalemate() const;
    bool isDraw() const;

    bool hasInsufficientMaterial() const;

    void addHistoric();
    void removeHistoric();

}; // ChessGame

//-----------------------------------------------------------------------------