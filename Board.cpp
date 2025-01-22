// Board.cpp
#include "Board.hpp"
#include <cmath>
#include <iostream>

Board::Board()
    : mIsWhiteTurn(true), mSelectedPiece(nullptr), mGameOver(false),
    mMustContinueCapturing(false), mPieceToContinue(nullptr)
{
    initializePieces();
}

void Board::initializePieces()
{
    mPieces.clear();
    mMoveHistory.clear();

    // Siyah taþlar üst tarafta baþlatýlýr
    for (int i = 0; i < 12; ++i)
    {
        auto piece = std::make_shared<Piece>(false);
        int row = i / 4;
        int col = (i % 4) * 2 + (row % 2);
        piece->setPosition(static_cast<float>(col * 100 + 50), static_cast<float>(row * 100 + 50));
        mPieces.push_back(piece);
    }

    // Beyaz taþlar alt tarafta baþlatýlýr
    for (int i = 0; i < 12; ++i)
    {
        auto piece = std::make_shared<Piece>(true);
        int row = 5 + (i / 4);
        int col = (i % 4) * 2 + (row % 2);
        piece->setPosition(static_cast<float>(col * 100 + 50), static_cast<float>(row * 100 + 50));
        mPieces.push_back(piece);
    }
}

void Board::reset()
{
    mIsWhiteTurn = true;
    mSelectedPiece = nullptr;
    mGameOver = false;
    mWinner.clear();
    mMustContinueCapturing = false;
    mPieceToContinue = nullptr;
    mMoveHistory.clear();
    initializePieces();
}

bool Board::selectPieceAt(float x, float y)
{
    sf::Vector2f clickPosition(x, y);

    for (auto& piece : mPieces)
    {
        if (piece->contains(clickPosition) && piece->isWhite() == mIsWhiteTurn)
        {
            if (mMustContinueCapturing)
            {
                if (piece != mPieceToContinue)
                {
                    return false; // Ardýþýk yeme hamlesinde baþka taþ seçilemez
                }
            }

            if (mSelectedPiece)
            {
                mSelectedPiece->setSelected(false);
            }
            mSelectedPiece = piece;
            mOldPosition = mSelectedPiece->getPosition();
            mSelectedPiece->setSelected(true);
            return true;
        }
    }
    return false;
}

bool Board::moveSelectedPieceTo(float x, float y)
{
    if (!mSelectedPiece)
        return false;

    int col = static_cast<int>(x / 100);
    int row = static_cast<int>(y / 100);
    sf::Vector2f targetPosition(static_cast<float>(col * 100 + 50), static_cast<float>(row * 100 + 50));

    if (isValidMove(mSelectedPiece, targetPosition))
    {
        bool wasCapture = std::abs(targetPosition.x - mOldPosition.x) == 200.f;
        bool wasKingBeforeMove = mSelectedPiece->isKing();

        Move move;
        move.from = mOldPosition;
        move.to = targetPosition;
        move.wasKing = wasKingBeforeMove;
        move.becameKing = false;
        move.capturedPiece = nullptr;

        if (wasCapture)
        {
            float midX = (mOldPosition.x + targetPosition.x) / 2.f;
            float midY = (mOldPosition.y + targetPosition.y) / 2.f;
            sf::Vector2f capturedPosition(midX, midY);

            // Yenen taþý bul ve kaydet
            for (auto it = mPieces.begin(); it != mPieces.end(); ++it)
            {
                if (arePositionsEqual((*it)->getPosition(), capturedPosition))
                {
                    move.capturedPiece = *it;
                    move.capturedPiecePosition = capturedPosition;
                    mPieces.erase(it);
                    break;
                }
            }
        }

        // Taþý hareket ettir
        mSelectedPiece->setPosition(targetPosition);

        // Dama olma kontrolü
        if (!wasKingBeforeMove && ((mSelectedPiece->isWhite() && targetPosition.y == 50.f) || (!mSelectedPiece->isWhite() && targetPosition.y == 750.f)))
        {
            mSelectedPiece->makeKing();
            move.becameKing = true;
        }

        // Hamleyi hamle geçmiþine ekle
        mMoveHistory.push_back(move);

        // Ardýþýk yeme hamlesi kontrolü
        if (wasCapture)
        {
            auto additionalCaptures = getCaptureMovesForPiece(mSelectedPiece);
            if (!additionalCaptures.empty())
            {
                mMustContinueCapturing = true;
                mPieceToContinue = mSelectedPiece;
                mOldPosition = mSelectedPiece->getPosition();
            }
            else
            {
                mMustContinueCapturing = false;
                mPieceToContinue = nullptr;
                mIsWhiteTurn = !mIsWhiteTurn;
                mSelectedPiece->setSelected(false);
                mSelectedPiece = nullptr;
            }
        }
        else
        {
            mMustContinueCapturing = false;
            mPieceToContinue = nullptr;
            mIsWhiteTurn = !mIsWhiteTurn;
            mSelectedPiece->setSelected(false);
            mSelectedPiece = nullptr;
        }

        // Oyun bitiþ kontrolü
        checkGameOver();

        return true;
    }
    else
    {
        std::cout << "Invalid move." << std::endl;
        mSelectedPiece->setPosition(mOldPosition);
        mSelectedPiece->setSelected(false);
        mSelectedPiece = nullptr;
        return false;
    }
}

bool Board::undoMove()
{
    if (mMoveHistory.empty())
        return false;

    Move lastMove = mMoveHistory.back();
    mMoveHistory.pop_back();

    // Taþý eski konumuna geri al
    std::shared_ptr<Piece> movedPiece = nullptr;
    for (auto& piece : mPieces)
    {
        if (arePositionsEqual(piece->getPosition(), lastMove.to))
        {
            movedPiece = piece;
            piece->setPosition(lastMove.from);

            // Kral statüsünü geri yükle
            if (lastMove.wasKing && !piece->isKing())
            {
                piece->makeKing();
            }
            else if (!lastMove.wasKing && piece->isKing() && lastMove.becameKing)
            {
                piece->demoteFromKing();
            }
            break;
        }
    }

    // Eðer hamlede bir taþ yenildiyse, onu geri ekle
    if (lastMove.capturedPiece)
    {
        lastMove.capturedPiece->setPosition(lastMove.capturedPiecePosition);
        mPieces.push_back(lastMove.capturedPiece);
    }

    // Sýra deðiþimini geri al
    if (!mMustContinueCapturing)
    {
        mIsWhiteTurn = !mIsWhiteTurn;
    }

    // Ardýþýk yeme hamleleri durumunu güncelle
    if (mMoveHistory.empty())
    {
        mMustContinueCapturing = false;
        mPieceToContinue = nullptr;
    }
    else
    {
        Move prevMove = mMoveHistory.back();
        if (mMustContinueCapturing && movedPiece == mPieceToContinue)
        {
            // Önceki hamle ayný taþla yapýlan bir yeme hamlesiydi
            mOldPosition = movedPiece->getPosition();
        }
        else
        {
            mMustContinueCapturing = false;
            mPieceToContinue = nullptr;
            mSelectedPiece = nullptr;
        }
    }

    // Oyun bitiþ durumunu güncelle
    mGameOver = false;
    mWinner.clear();

    return true;
}

void Board::deselectPiece()
{
    if (mSelectedPiece && !mMustContinueCapturing)
    {
        mSelectedPiece->setSelected(false);
        mSelectedPiece->setPosition(mOldPosition);
        mSelectedPiece = nullptr;
    }
}

bool Board::isValidMove(std::shared_ptr<Piece> piece, sf::Vector2f position)
{
    // Hedef kare boþ mu?
    for (const auto& p : mPieces)
    {
        if (arePositionsEqual(p->getPosition(), position))
        {
            return false;
        }
    }

    float dx = position.x - mOldPosition.x;
    float dy = position.y - mOldPosition.y;

    bool isCapture = std::abs(dx) == 200.f && std::abs(dy) == 200.f;
    bool isSimpleMove = std::abs(dx) == 100.f && std::abs(dy) == 100.f;

    if (mMustContinueCapturing)
    {
        if (piece != mPieceToContinue)
        {
            return false; // Sadece ayný taþla devam edebilir
        }

        if (!isCapture)
        {
            return false; // Ardýþýk yeme hamlesinde basit hamle yapýlamaz
        }

        auto captureMoves = getCaptureMovesForPiece(piece);
        for (const auto& move : captureMoves)
        {
            if (arePositionsEqual(move.from, mOldPosition) && arePositionsEqual(move.to, position))
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        auto captureMoves = getCaptureMoves(mIsWhiteTurn);
        if (!captureMoves.empty())
        {
            if (!isCapture)
            {
                return false; // Yeme hamlesi varsa basit hamle yapýlamaz
            }

            for (const auto& move : captureMoves)
            {
                if (arePositionsEqual(move.from, mOldPosition) && arePositionsEqual(move.to, position))
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            if (isSimpleMove)
            {
                if (!piece->isKing())
                {
                    int direction = piece->isWhite() ? -1 : 1;
                    if (dy != 100.f * direction)
                    {
                        return false;
                    }
                }
                return true;
            }
        }
    }

    return false;
}


void Board::removePieceAt(sf::Vector2f position)
{
    for (auto it = mPieces.begin(); it != mPieces.end(); ++it)
    {
        if (arePositionsEqual((*it)->getPosition(), position))
        {
            mPieces.erase(it);
            break;
        }
    }

    // Oyun bitiþ kontrolü
    checkGameOver();
}

void Board::checkGameOver()
{
    bool whiteExists = false, blackExists = false;
    for (const auto& piece : mPieces)
    {
        if (piece->isWhite())
            whiteExists = true;
        else
            blackExists = true;
    }

    if (!whiteExists || !blackExists)
    {
        mGameOver = true;
        mWinner = whiteExists ? "White" : "Black";
        std::cout << "Game over! Winner: " << mWinner << std::endl;
    }
}

bool Board::isWhiteTurn() const
{
    return mIsWhiteTurn;
}

bool Board::isGameOver() const
{
    return mGameOver;
}

std::string Board::getWinner() const
{
    return mWinner;
}

const std::vector<std::shared_ptr<Piece>>& Board::getPieces() const
{
    return mPieces;
}

bool Board::arePositionsEqual(const sf::Vector2f& pos1, const sf::Vector2f& pos2, float epsilon)
{
    return (std::abs(pos1.x - pos2.x) < epsilon) && (std::abs(pos1.y - pos2.y) < epsilon);
}

// Yeni fonksiyonlar

std::vector<Move> Board::getPossibleMoves(bool isWhite)
{
    std::vector<Move> moves;
    for (const auto& piece : mPieces)
    {
        if (piece->isWhite() == isWhite)
        {
            auto pieceMoves = getPossibleMovesForPiece(piece);
            moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }
    return moves;
}

std::vector<Move> Board::getCaptureMoves(bool isWhite)
{
    std::vector<Move> moves;
    for (const auto& piece : mPieces)
    {
        if (piece->isWhite() == isWhite)
        {
            auto pieceMoves = getCaptureMovesForPiece(piece);
            moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }
    return moves;
}

std::vector<Move> Board::getPossibleMovesForPiece(std::shared_ptr<Piece> piece)
{
    std::vector<Move> moves;

    sf::Vector2f from = piece->getPosition();
    int fromRow = static_cast<int>(from.y / 100);
    int fromCol = static_cast<int>(from.x / 100);

    int directions[] = { -1, 1 };

    for (int dirRow : directions)
    {
        for (int dirCol : directions)
        {
            int toRow = fromRow + dirRow;
            int toCol = fromCol + dirCol;

            if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8)
            {
                sf::Vector2f to(static_cast<float>(toCol * 100 + 50), static_cast<float>(toRow * 100 + 50));

                bool occupied = false;
                for (const auto& p : mPieces)
                {
                    if (arePositionsEqual(p->getPosition(), to))
                    {
                        occupied = true;
                        break;
                    }
                }

                if (!occupied)
                {
                    moves.push_back({ from, to, piece->isKing(), false, nullptr, sf::Vector2f() });
                }
            }
        }
    }

    // Taþ için yeme hamlelerini de ekleyelim
    auto captureMoves = getCaptureMovesForPiece(piece);
    moves.insert(moves.end(), captureMoves.begin(), captureMoves.end());

    return moves;
}

std::vector<Move> Board::getCaptureMovesForPiece(std::shared_ptr<Piece> piece)
{
    std::vector<Move> moves;

    sf::Vector2f from = piece->getPosition();
    int fromRow = static_cast<int>(from.y / 100);
    int fromCol = static_cast<int>(from.x / 100);

    int directions[] = { -1, 1 };

    for (int dirRow : directions)
    {
        for (int dirCol : directions)
        {
            // Eðer taþ dama deðilse, sadece ileri doðru yiyebilir
            if (!piece->isKing())
            {
                int direction = piece->isWhite() ? -1 : 1;
                if (dirRow != direction)
                    continue;
            }

            int toRow = fromRow + 2 * dirRow;
            int toCol = fromCol + 2 * dirCol;

            if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8)
            {
                sf::Vector2f to(static_cast<float>(toCol * 100 + 50), static_cast<float>(toRow * 100 + 50));

                bool occupied = false;
                for (const auto& p : mPieces)
                {
                    if (arePositionsEqual(p->getPosition(), to))
                    {
                        occupied = true;
                        break;
                    }
                }

                if (!occupied)
                {
                    int midRow = fromRow + dirRow;
                    int midCol = fromCol + dirCol;
                    sf::Vector2f midPos(static_cast<float>(midCol * 100 + 50), static_cast<float>(midRow * 100 + 50));

                    for (const auto& p : mPieces)
                    {
                        if (arePositionsEqual(p->getPosition(), midPos) && p->isWhite() != piece->isWhite())
                        {
                            moves.push_back({ from, to, piece->isKing(), false, p, midPos });
                            break;
                        }
                    }
                }
            }
        }
    }

    return moves;
}



