#pragma once
#include "Sprite.h"
#include "Inputtable.h"

class Cursor : public virtual Sprite, public virtual Inputtable {
    public:
        static const short ID = 7;

        Cursor(Stage* stage);
        virtual bool IsOfType(short id);

        virtual void HandlePointer(const Vector2i& pointerPos);
};