#ifndef PIECEARR_H
#define PIECEARR_H
#include "Piece.h"
#include "PieceColor.h"
#include "PieceType.h"
#include <array>
#include <tuple>

class PieceArr
{
public:
    PieceArr(){}
    PieceArr(int color) {

    }

private:
    void createArray(int color) {
        for(size_t i{0}; i < 8; ++i){
            std::string image_path{color + "_pawn.png"};
            std::pair<int, int> position;
            if (color) {
                position = std::make_pair(i, 1);
            } else {
                position = std::make_pair(i, 6);
            }
            pieces[i] = createPiece(PieceType::Pawn, image_path, position, false);
        }

        if (color) {
            std::string image_path{color + "_castle.png"};
            pieces[8] = createPiece(PieceType::Castle, image_path, std::make_pair(0, 0), false);
            pieces[9] = createPiece(PieceType::Castle, image_path, std::make_pair(7, 0), false);
        } else {
            std::string image_path{color + "_castle.png"};
            pieces[8] = createPiece(PieceType::Castle, image_path, std::make_pair(0, 7), false);
            pieces[9] = createPiece(PieceType::Castle, image_path, std::make_pair(7, 7), false);
        }
    }
    Piece createPiece(PieceType type, std::string image_path, std::pair<int, int> position, bool is_killed){

    }
    static constexpr int size{16};

protected:
    PieceColor color;
    std::array<Piece, size> pieces;
};

#endif // PIECEARR_H
