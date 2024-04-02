#ifndef PIECE_H
#define PIECE_H
#include "PieceType.h"
#include <tuple>
#include <string>

class Piece{
protected:
    PieceType type;
    std::string image_path;
    std::pair<int, int> position;
    bool is_killed;
};

#endif // PIECE_H
