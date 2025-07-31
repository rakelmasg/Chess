//------------------------------------------------------------------------------
// File: ChessGame.cpp
//
// Implements game state management, move processing, and rule enforcement 
// for chess, including special moves and game status evaluation.
//------------------------------------------------------------------------------

#include "ChessGame.h"
#include "Command/ActionCommand.h"
#include "Command/CastlingCommand.h"
#include "Command/EnPassantCaptureCommand.h"
#include "Command/MoveCommand.h"
#include "Command/PromotionCommand.h"
#include "Components/PieceFactory.h"
#include "GameContext.h"
#include <sstream>

//-----------------------------------------------------------------------------

ChessGame::ChessGame() : board_(std::make_unique<Board>()), isWhiteTurn_(true), halfmoveClock_(0), fullmoveNumber_(1)
{

} // ChessGame

//-----------------------------------------------------------------------------

std::unique_ptr<ChessGame> ChessGame::clone() const
{
    std::unique_ptr<Board> boardClone = board_->clone();

    std::unique_ptr<ChessGame> cloneGame = std::make_unique<ChessGame>();
    cloneGame->board_ = std::move(boardClone);
    cloneGame->isWhiteTurn_ = isWhiteTurn_;
    cloneGame->halfmoveClock_ = halfmoveClock_;
    cloneGame->fullmoveNumber_ = fullmoveNumber_;
    cloneGame->enPassant_ = enPassant_;
    cloneGame->castlingRights_ = castlingRights_;

    return cloneGame;

} // clone

//-----------------------------------------------------------------------------

std::string ChessGame::getDefaultFEN() const 
{
    return "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

} // getDefaultFEN

//-----------------------------------------------------------------------------

bool ChessGame::initBoardFromFEN(const std::string& fen)
{
    std::istringstream iss(fen);
    std::string boardPart, turnPart, castlingRights, enPassant, halfmoveClockStr, fullmoveNumberStr;

    if (!(iss >> boardPart >> turnPart >> castlingRights >> enPassant >> halfmoveClockStr >> fullmoveNumberStr))
    {
        return false;
    }

    try 
    {
        //Board
        board_->clear();

        int y = board_->sizeY() - 1;
        int x = 0;
        for (char c : boardPart)
        {
            if (c == '/') {
                --y;
                x = 0;
                if (y < 0)
                { 
                    return false; 
                }
            }
            else if (std::isdigit(c))
            {
                x += c - '0';
                if (x > board_->sizeX())
                {
                    return false;
                }
            }
            else
            {
                auto piece = PieceFactory::createPieceFEN(c);
                if (piece)
                {
                    board_->setPiece(x, y, std::move(piece));
                }
                ++x;
            }
        }

        isWhiteTurn_ = (turnPart == "w");
        halfmoveClock_ = std::stoi(halfmoveClockStr);
        fullmoveNumber_ = std::stoi(fullmoveNumberStr);

        int xPassant = -1, yPasssant = -1;
        ChessUtils::parseSquareToBoardIndex(board(), enPassant, xPassant, yPasssant);
        enPassant_ = { xPassant, yPasssant };
        castlingRights_ = ChessUtils::castlingRightsFromFEN(castlingRights);

        return true;
    }
    catch (const std::exception&) 
    {
        return false;
    }

} // initBoardFromFEN

//-----------------------------------------------------------------------------

bool ChessGame::initGame()
{
    return initBoardFromFEN(getDefaultFEN());

} // initGame

//-----------------------------------------------------------------------------

bool ChessGame::initGame(const std::string& fen)
{
    return initBoardFromFEN(fen);

} // initGame

//-----------------------------------------------------------------------------

std::string ChessGame::getFEN() const
{
    return getPartialFEN() + " " + std::to_string(halfmoveClock_) + " " + std::to_string(fullmoveNumber_);

} // getFEN

//-----------------------------------------------------------------------------

std::string ChessGame::getPartialFEN() const
{
    std::string boardPart, turnPart, castlingRights, enPassant;

    //Board
    int empty = 0;
    for (int y = board_->sizeY() - 1; y >= 0; --y)
    {
        for (int x = 0; x < board_->sizeX(); ++x)
        {
            const Piece* piece = board_->getPiece(x, y);
            if (piece)
            {
                if (empty != 0)
                {
                    boardPart += std::to_string(empty);
                }
                boardPart += piece->getSymbolFEN();
                empty = 0;
            }
            else
            {
                ++empty;
            }
        }

        if (empty != 0)
        {
            boardPart += std::to_string(empty);
            empty = 0;
        }

        if (y > 0)
        {
            boardPart += "/";
        }
    }

    turnPart = isWhiteTurn_ ? "w" : "b";
    castlingRights = ChessUtils::castlingRightsToFEN(castlingRights_);
    ChessUtils::parseBoardIndexToSquare(board(), enPassant_.first, enPassant_.second, enPassant);

    return boardPart + " " + turnPart + " " + castlingRights + " " + enPassant;

} // getPartialFEN

//-----------------------------------------------------------------------------

void ChessGame::switchTurn()
{
    isWhiteTurn_ = !isWhiteTurn_;

} // switchTurn

//-----------------------------------------------------------------------------

void ChessGame::incrementHalfmoveClock()
{
    ++halfmoveClock_;

} // incrementHalfmoveClock

//-----------------------------------------------------------------------------

void ChessGame::resetHalfmoveClock()
{
    halfmoveClock_ = 0;

} // resetHalfmoveClock

//-----------------------------------------------------------------------------

void ChessGame::restoreHalfmoveClock(int value)
{
    halfmoveClock_ = value;

} // restoreHalfmoveClock

//-----------------------------------------------------------------------------

void ChessGame::incrementFullmoveNumber()
{
    ++fullmoveNumber_;

} // incrementFullmoveNumber

//-----------------------------------------------------------------------------

void ChessGame::decrementFullmoveNumber()
{
    --fullmoveNumber_;

} // decrementFullmoveNumber

//-----------------------------------------------------------------------------

void ChessGame::setEnPassant(const std::pair<int, int> enPassant)
{
    enPassant_ = enPassant;

} // setEnPassant

//-----------------------------------------------------------------------------

void ChessGame::setCastlingRight(CastlingMask rights)
{
    castlingRights_ = rights;

} // setCastlingRight

//-----------------------------------------------------------------------------

void ChessGame::removeCastlingRight(CastlingRights right)
{
    castlingRights_ &= ~right;

} // removeCastlingRight

//-----------------------------------------------------------------------------

const std::set<char>& ChessGame::getValidPromotionSymbols() const
{
    static const std::set<char> defaultPromotions = { 'q', 'r', 'b', 'n' };
    return defaultPromotions;

} // getValidPromotionSymbols

//-----------------------------------------------------------------------------

bool ChessGame::isValidPromotionSymbol(char symbol) const
{
    return getValidPromotionSymbols().count(tolower(symbol)) > 0;

} // isValidPromotionSymbol

//-----------------------------------------------------------------------------

MoveInfo ChessGame::analyzeMove(Move move, const GameContext& gameCtx)
{
    const Piece* piece = board_->getPiece(move.fromX, move.fromY);

    if (!piece || piece->isWhite() != isWhiteTurn_)
    {
        return false;
    }

    return piece->analyzeMove(move, *board_, gameCtx);

} // analyzeMove

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> ChessGame::movePiece(Move move)
{
    return board_->movePiece(move);

} // movePiece

//-----------------------------------------------------------------------------

std::unique_ptr<Piece> ChessGame::replacePiece(int x, int y, std::unique_ptr<Piece> newPiece)
{
    std::unique_ptr<Piece> originalPiece = board_->takePiece(x, y);

    if (newPiece) {
        board_->setPiece(x, y, std::move(newPiece));
    }

    return originalPiece;

} // replacePiece

//-----------------------------------------------------------------------------

bool ChessGame::isMoveSafe(const Move& move, const MoveInfo& info) const
{
    std::unique_ptr<ChessGame> cloneGame = this->clone();

    return isMoveSafe(*cloneGame, move, info);

} // isMoveSafe

//-----------------------------------------------------------------------------

bool ChessGame::isMoveSafe(ChessGame& cloneGame, const Move& move, const MoveInfo& info) const
{
    auto isSafe = [&](ActionCommand& cmd) 
    {
        cmd.execute(cloneGame);
        bool isInCheck = cloneGame.isInCheck(cloneGame.board(), !cloneGame.isWhiteTurn());
        cmd.undo(cloneGame);

        return !isInCheck;
     };

    if (info.isPromotionMove_)
    {
        PromotionCommand promotionCmd(move, PieceFactory::createPiece('p', cloneGame.isWhiteTurn()));
        return isSafe(promotionCmd);
    }
    else if (info.isEnPassantCapture_)
    {
        EnPassantCaptureCommand passantCmd(move);
        return isSafe(passantCmd);
    }
    else if (info.isCastling_)
    {
        CastlingCommand castlingCmd(move);
        return isSafe(castlingCmd);
    }
    else // Regular Move
    {
        MoveCommand cmd(move);
        return isSafe(cmd);
    }
}

//-----------------------------------------------------------------------------

GameStatus ChessGame::getGameStatus() const
{
    if (isInCheck(*board_, isWhiteTurn_))
    {
        if (isCheckmate()) 
        {
            return GameStatus::Checkmate;
        }

        return GameStatus::Check;
    }
    
    if (isStalemate()) 
    {
        return GameStatus::Stalemate;
    }

    if (isDraw()) 
    {
        return GameStatus::Draw;
    }

    return GameStatus::Playing;

} // getGameStatus

//-----------------------------------------------------------------------------

bool ChessGame::isInCheck(const Board& board, bool isWhiteKing) const
{
    std::pair<int, int> kingPosition = board.getKingPosition(isWhiteKing);
    GameContext gameCtx = GameContext (enPassant_, castlingRights_);

    return ChessUtils::isSquareUnderAttack(board, kingPosition.first, kingPosition.second, !isWhiteKing, gameCtx);

} // isInCheck

//-----------------------------------------------------------------------------

bool ChessGame::isCheckmate() const //Must verify isInCheck is TRUE first
{
    std::unique_ptr<ChessGame> cloneGame = clone();

    GameContext cloneGameCtx = GameContext(cloneGame->getEnPassant(), cloneGame->getCastlingRights());

    for (int x = 0; x < cloneGame->board().sizeX(); ++x)
    {
        for (int y = 0; y < cloneGame->board().sizeY(); ++y)
        {
            const Piece* piece = cloneGame->board().getPiece(x, y);
            if (piece && piece->isWhite() == isWhiteTurn_)
            {
                auto moves = piece->generateMoves(x, y, piece->isWhite(), cloneGame->board(), cloneGameCtx);
         
                for (const std::pair<Move, MoveInfo>& pair : moves)
                {
                    if (isMoveSafe(*cloneGame, pair.first, pair.second))
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;

} // isCheckmate

//-----------------------------------------------------------------------------

bool ChessGame::isStalemate() const //Must verify isInCheck is FALSE first
{
    std::unique_ptr<ChessGame> cloneGame = clone();

    GameContext cloneGameCtx = GameContext(cloneGame->getEnPassant(), cloneGame->getCastlingRights());

    for (int x = 0; x < cloneGame->board().sizeX(); ++x)
    {
        for (int y = 0; y < cloneGame->board().sizeY(); ++y)
        {
            const Piece* piece = cloneGame->board().getPiece(x, y);
            if (piece && piece->isWhite() == isWhiteTurn_)
            {
                auto moves = piece->generateMoves(x, y, piece->isWhite(), cloneGame->board(), cloneGameCtx);

                for (const std::pair<Move, MoveInfo>& pair : moves)
                {
                    if (isMoveSafe(*cloneGame, pair.first, pair.second))
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;

} // isStalemate

//-----------------------------------------------------------------------------

bool ChessGame::isDraw() const
{
    if (halfmoveClock_ >= 100)
    {
        return true;
    }

    if (hasInsufficientMaterial())
    {
        return true;
    }

    // Triple repetition
    for (auto pair: historic)
    {
        if (pair.second >= 3) 
        {
            return true;
        }
    }

    return false;

} // isDraw

//-----------------------------------------------------------------------------

bool ChessGame::hasInsufficientMaterial() const
{
    int whiteKnights = 0;
    int blackKnights = 0;
    int whiteBishops = 0;
    int blackBishops = 0;
    int totalNonKingPieces = 0;

    for (int x = 0; x < board_->sizeX(); ++x)
    {
        for (int y = 0; y < board_->sizeY(); ++y)
        {
            const Piece* piece = board_->getPiece(x, y);
            if (!piece) 
            { 
                continue;
            }

            char s = std::tolower(piece->getSymbol());
            if (s == 'k')
            {
                continue;
            }

            ++totalNonKingPieces;

            if (piece->isWhite())
            {
                if (s == 'n') 
                {
                    whiteKnights++;
                }
                if (s == 'b')
                {
                    whiteBishops++;
                }
            }
            else
            {
                if (s == 'n')
                {
                    blackKnights++;
                }
                if (s == 'b') 
                {
                    blackBishops++;
                }
            }

            if (s == 'q' || s == 'r' || s == 'p')
            {
                return false;
            }
        }
    }

    if (totalNonKingPieces <= 1)
    {
        return true;
    }

    return false;

} // hasInsufficientMaterial

//-----------------------------------------------------------------------------

void ChessGame::addHistoric()
{
    historic[getPartialFEN()]++;

} // addHistoric

//-----------------------------------------------------------------------------

void ChessGame::removeHistoric()
{
    std::string key = getPartialFEN();
    if (--historic[key] == 0)
    {
        historic.erase(key);
    }

} // removeHistoric

//-----------------------------------------------------------------------------