#pragma once
#include "Sprite.h"

class MoveHint : public Sprite {
    public:
        static const short ID = 9;

        ActorConstructor(MoveHint)
        virtual bool IsOfType(short id);
};