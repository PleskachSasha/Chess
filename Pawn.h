#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"
#include "PawnMoveDirection.h"

class Pawn : public Piece {
    bool step_count;
    PawnMoveDirection direction;
    bool end_board;
};

#endif // PAWN_H
