#ifndef PIECEARR_H
#define PIECEARR_H
#include "Piece.h"
#include "PieceColor.h"

class PieceArr
{
public:
    PieceArr();

private:
    const int size{16};

protected:

    PieceColor color;
};

#endif // PIECEARR_H
