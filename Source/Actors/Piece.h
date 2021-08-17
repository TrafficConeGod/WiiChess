#pragma once
#include "Board.h"
#include "Inputtable.h"

class Piece : public virtual Sprite, public virtual Inputtable {
    private:
        bool hovered;
        bool held;
        Vector2u origPos;

        void Hold();
        void Release();
    public:
        static const short ID = 6;

        enum Color {
            BLACK,
            WHITE
        };

        ActorReference<Board> boardRef;
        Vector2u loc;

        ActorConstructor(Piece)
        virtual bool IsOfType(short id);

        virtual void Create();

        virtual void HandlePointer(const ir_t& pointer);
        virtual void ButtonsDown(uint buttons);
        virtual void ButtonsUp(uint buttons);

        void UpdateLocation(Vector2u loc);
};