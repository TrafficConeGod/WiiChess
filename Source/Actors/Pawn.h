#pragma once
#include "Piece.h"

class Pawn : public virtual Piece {
    public:
        static const short ID = 6;

        ActorConstructor(Pawn)
        virtual bool IsOfType(short id);
};