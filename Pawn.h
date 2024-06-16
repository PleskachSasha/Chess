#ifndef PAWN_H
#define PAWN_H
#include "FigureBase.h"
#include "PawnMoveDirection.h"

class Pawn : public FigureBase {
    bool step_count;
    PawnMoveDirection direction;
    bool end_board;
};

#endif
