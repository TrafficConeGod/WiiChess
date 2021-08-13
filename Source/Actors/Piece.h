#pragma once
#include "Board.h"

class Piece : public virtual Sprite {
    public:
        static const short ID = 5;

        enum Color {
            BLACK,
            WHITE
        };

        ActorReference<Board> boardRef;
        Color color;
        Vector2u loc;

        using Sprite::Sprite;
        virtual bool IsOfType(short id);

        virtual void Load(DataStream& stream);
        virtual void Create();
};