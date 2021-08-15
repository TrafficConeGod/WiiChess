#pragma once
#include "Sprite.h"

class Piece;

class Board : public virtual Sprite {
    private:
        ActorReference<Piece> blackPawnRef;
    public:
        static const short ID = 5;

        ActorConstructor(Board)
        virtual bool IsOfType(short id);

        virtual void Load(DataStream& stream);

        virtual void Create();

        void AddPiece(Piece* piece);
};