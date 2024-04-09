#ifndef PIECE_H
#define PIECE_H
#include "PieceType.h"
#include "PieceColor.h"
#include <tuple>
#include <string>
#include <QString>

class Piece{
public:
    Piece(){}
    Piece(PieceType type, QString image_path, std::pair<int, int> position, bool is_killed, PieceColor color)
        :type(type),  image_path(image_path), position(position), is_killed(is_killed), color(color)
    {}
    QString image_path;

    PieceType type;
    std::pair<int, int> position;
protected:
    bool is_killed;
    PieceColor color;
};

#endif // PIECE_H
