#pragma once
#include "Sprite.h"
#include "Chess/Engine.h"

class Piece;

class Board : public virtual Sprite {
    private:
        Array<ActorReference<Piece>> pieceRefs;
        Array<uchar> initialState;
        Chess::Engine engine;
    public:
        static const short ID = 5;

        ActorConstructor(Board)
        virtual bool IsOfType(short id);

        virtual void Load(DataStream& stream);

        virtual void Create();
        void UpdateDisplay();
};