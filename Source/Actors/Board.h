#pragma once
#include "Sprite.h"
#include "Chess/Engine.h"

class Piece;
class MoveHint;

class Board : public virtual Sprite {
    private:
        Array<ActorReference<Piece>> pieceRefs;
        Array<uchar> initialState;
        ActorReference<MoveHint> moveHintRef;
    public:
        static const short ID = 5;

        Chess::Engine engine;

        ActorConstructor(Board)
        virtual bool IsOfType(short id);

        virtual void Load(DataStream& stream);

        virtual void Create();

        void ShowMoves(Vector2u loc);
        void HideMoves();
        void UpdateDisplay();
};