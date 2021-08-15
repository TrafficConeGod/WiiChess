#pragma once
#include "Board.h"
#include "Inputtable.h"

class Piece : public virtual Sprite, public virtual Inputtable {
    private:
        Vector2i origPos;
        bool hovered;
        bool held;
    public:
        static const short ID = 5;

        enum Color {
            BLACK,
            WHITE
        };

        ActorReference<Board> boardRef;
        Color color;
        Vector2u loc;

        Piece(Stage* stage);
        virtual bool IsOfType(short id);

        virtual void Load(DataStream& stream);

        virtual void Create();
        virtual void Update();

        virtual void HandlePointer(const ir_t& pointer);
        virtual void ButtonsDown(uint buttons);
        virtual void ButtonsUp(uint buttons);
};