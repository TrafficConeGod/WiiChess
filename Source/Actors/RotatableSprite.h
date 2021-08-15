#pragma once
#include "Sprite.h"

class RotatableSprite : public virtual Sprite {
    public: 
        static const short ID = 7;

        float radians;

        ActorConstructor(RotatableSprite)
        virtual bool IsOfType(short id);

        virtual void Load(DataStream& stream);

        virtual void Draw();
};