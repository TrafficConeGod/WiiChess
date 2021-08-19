#pragma once
#include "Board.h"
#include "Inputtable.h"

class Piece : public virtual Sprite, public virtual Inputtable {
    private:
        bool hovered = false;
        bool held = false;
        Vector2u origPos;

        void Hold();
        void Release();
    public:
        static const short ID = 6;

        ActorReference<Board> boardRef;
        Chess::Space::Color color;
        Vector2u loc;

        ActorConstructor(Piece)
        virtual bool IsOfType(short id);

        virtual void Create();

        virtual void HandlePointer(const ir_t& pointer);
        virtual void ButtonsDown(uint buttons);
        virtual void ButtonsUp(uint buttons);

        void UpdateLocation(const Vector2u& loc);
};