// Board.hpp
#ifndef BOARD_HPP
#define BOARD_HPP

#include "Piece.hpp"
#include <vector>
#include <memory>

// Güncellenmiþ Move yapýsý
struct Move
{
    sf::Vector2f from;
    sf::Vector2f to;
    bool wasKing;
    bool becameKing; // Yeni eklenen deðiþken
    std::shared_ptr<Piece> capturedPiece;
    sf::Vector2f capturedPiecePosition;
};

class Board
{
public:
    Board();

    bool isWhiteTurn() const;
    bool isGameOver() const;
    std::string getWinner() const;

    bool selectPieceAt(float x, float y);
    bool moveSelectedPieceTo(float x, float y);
    void deselectPiece();

    void reset();

    const std::vector<std::shared_ptr<Piece>>& getPieces() const;

    // Yeni fonksiyonlar
    std::vector<Move> getPossibleMoves(bool isWhite);
    std::vector<Move> getCaptureMoves(bool isWhite);

    bool undoMove(); // Hamle geri alma fonksiyonu

private:
    void initializePieces();
    bool isValidMove(std::shared_ptr<Piece> piece, sf::Vector2f position);
    void removePieceAt(sf::Vector2f position);
    void checkGameOver();

    std::vector<Move> getPossibleMovesForPiece(std::shared_ptr<Piece> piece);
    std::vector<Move> getCaptureMovesForPiece(std::shared_ptr<Piece> piece);

    std::vector<std::shared_ptr<Piece>> mPieces;

    bool mIsWhiteTurn;
    std::shared_ptr<Piece> mSelectedPiece;
    sf::Vector2f mOldPosition;

    bool mGameOver;
    std::string mWinner;

    // Ardýþýk yeme hamleleri için
    bool mMustContinueCapturing;
    std::shared_ptr<Piece> mPieceToContinue;

    // Hamle geçmiþi
    std::vector<Move> mMoveHistory;

    bool arePositionsEqual(const sf::Vector2f& pos1, const sf::Vector2f& pos2, float epsilon = 1.f);
};

#endif // BOARD_HPP
