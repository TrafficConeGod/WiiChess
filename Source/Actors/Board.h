#pragma once
#include "Sprite.h"
#include "Chess/Engine.h"

class Piece;

class Board : public virtual Sprite {
    private:
        Array<ActorReference<Piece>> pieceRefs;
        Array<uint> initialState;
        Chess::BoardState* boardState;
    public:
        static const short ID = 5;

        ActorConstructor(Board)
        virtual bool IsOfType(short id);

        virtual void Load(DataStream& stream);

        virtual void Create();
        virtual void Destroy();
};