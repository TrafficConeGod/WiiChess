#pragma once
#include "Resource.h"

class TextureResource : public virtual Resource {
    private:
        GXTexObj texObj;
    public:
        static const short ID = 3;

        ActorConstructor(TextureResource)
        virtual bool IsOfType(short id);

        virtual void Load(DataStream& stream);

        void UseTexture();
};