#pragma once
#include "Actor.h"
#include "String.h"

class Resource : public virtual Actor {
    protected:
        String path;
    public:
        static const short ID = 3;

        ActorConstructor(Resource)
        virtual bool IsOfType(short id);

        virtual void Load(DataStream& stream);
};