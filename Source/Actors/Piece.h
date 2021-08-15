#pragma once
#include "Board.h"
#include "Inputtable.h"

class Piece : public virtual Sprite, public virtual Inputtable {
    private:
        Vector2u origPos;
        bool hovered;
        bool held;
    public:
        static const short ID = 6;

        enum Color {
            BLACK,
            WHITE
        };

        ActorReference<Board> boardRef;

        ActorConstructor(Piece)
        virtual bool IsOfType(short id);

        virtual void HandlePointer(const ir_t& pointer);
        virtual void ButtonsDown(uint buttons);
        virtual void ButtonsUp(uint buttons);
};