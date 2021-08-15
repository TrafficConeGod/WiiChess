#pragma once
#include "Actor.h"
#include "Vector2.h"
#include "ActorReference.h"
#include "TextureResource.h"

class Sprite : public virtual Actor {
    public:
        static const short ID = 1;

        Vector2u pos;
        Vector2u size;
        uint layer;
        ActorReference<TextureResource> textureRef;

        ActorConstructor(Sprite)
        virtual bool IsOfType(short id);
        
        virtual void Load(DataStream& stream);

        virtual void Create();
        virtual void Destroy();

        virtual void Draw();

        void UpdateDrawOrder();
        static void Draw(Stage* stage);
};