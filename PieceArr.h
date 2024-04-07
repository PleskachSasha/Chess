#ifndef PIECEARR_H
#define PIECEARR_H
#include "Piece.h"
#include "PieceColor.h"
#include "PieceType.h"
#include <array>
#include <tuple>
#include <QObject>
#include "iostream"



class PieceArr : public QObject
{
    Q_OBJECT

public:
    PieceArr(PieceColor color) {
        createArray(color);
    }

private:
    void createArray(PieceColor color) {
        std::string strColor = static_cast<int>(color) ? "white" : "black";
        const std::string pawnImage = strColor + "_pawn.png";
        const std::string castleImage = strColor + "_castle.png";
        const std::string knightImage = strColor + "_knight.png";
        const std::string bishopImage = strColor + "_bishop.png";
        const std::string queenImage = strColor + "_queen.png";
        const std::string kingImage = strColor + "_king.png";

        const int pawnRow = color ? 1 : 6;
        const int backRow = color ? 0 : 7;

        for(size_t i{0}; i < 8; ++i){
            std::pair<int, int> position(i, pawnRow);
            pieces[i] = createPiece(PieceType::Pawn, pawnImage, position, false);
        }

        pieces[8]  = createPiece(PieceType::Castle, castleImage, std::make_pair(0, backRow), false);
        pieces[9]  = createPiece(PieceType::Castle, castleImage, std::make_pair(7, backRow), false);
        pieces[10] = createPiece(PieceType::Knight, knightImage, std::make_pair(1, backRow), false);
        pieces[11] = createPiece(PieceType::Knight, knightImage, std::make_pair(6, backRow), false);
        pieces[12] = createPiece(PieceType::Bishop, bishopImage, std::make_pair(2, backRow), false);
        pieces[13] = createPiece(PieceType::Bishop, bishopImage, std::make_pair(5, backRow), false);
        pieces[14] = createPiece(PieceType::King,   kingImage,   std::make_pair(4, backRow), false);
        pieces[15] = createPiece(PieceType::Queen,  queenImage,  std::make_pair(3, backRow), false);
    }
    Piece createPiece(PieceType type, std::string image_path, std::pair<int, int> position, bool is_killed){
        return Piece(type, image_path, position, is_killed, color);
    }


    static constexpr int size{16};

public:
    PieceColor color;
    std::array<Piece, size> pieces;
};

#endif // PIECEARR_H
