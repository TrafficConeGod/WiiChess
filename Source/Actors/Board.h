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

        Chess::Space::Color turnColor = Chess::Space::Color::White;
        Chess::Engine engine;
        Array<size_t> removedPieceIndices;

        ActorConstructor(Board)
        virtual bool IsOfType(short id);

        virtual void Load(DataStream& stream);

        virtual void Create();

        void ShowMoves(const Vector2u& loc);
        void HideMoves();
        bool MovePiece(const Vector2u& from, const Vector2u& to);
        void UpdateDisplay();
};