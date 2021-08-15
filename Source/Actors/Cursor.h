#pragma once
#include "RotatableSprite.h"
#include "Inputtable.h"

class Cursor : public virtual RotatableSprite, public virtual Inputtable {
    public:
        static const short ID = 8;

        ActorConstructor(Cursor)
        virtual bool IsOfType(short id);

        virtual void HandlePointer(const ir_t& pointer);
};