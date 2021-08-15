#pragma once
#include "Actor.h"
#include "Vector2.h"
#include <wiiuse/wiiuse.h>

class Inputtable : public virtual Actor {
    public:
        static const short ID = -1;

        ActorConstructor(Inputtable)
        virtual bool IsOfType(short id);

        virtual void ButtonsDown(uint buttons);
        virtual void ButtonsHeld(uint buttons);
        virtual void ButtonsUp(uint buttons);
        virtual void HandlePointer(const ir_t& pointer);
};