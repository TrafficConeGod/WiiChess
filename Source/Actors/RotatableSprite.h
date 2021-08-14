#pragma once
#include "Sprite.h"

class RotatableSprite : public virtual Sprite {
    public: 
        static const short ID = 7;

        float radians;

        using Sprite::Sprite;
        virtual bool IsOfType(short id);

        virtual void Load(DataStream& stream);

        virtual void Draw();
};