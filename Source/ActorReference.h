#pragma once
#include "Stage.h"
#include "Array.h"

template<typename A>
class ActorReference {
    private:
        Stage* stage = nullptr;
        size_t index = 0;
    public:
        ActorReference();
        
        ActorReference(Stage* stage, size_t index);

        void operator=(const ActorReference<A>& ref);
        ActorReference(const ActorReference<A>& ref);

        void operator=(Actor* actor);
        ActorReference(Actor* actor);
        void Load(Stage* stage, DataStream& stream);

        static void Load(Stage* stage, DataStream& stream, Array<ActorReference<A>>& arr);
        
        bool IsEmpty();
        operator A*();
};

#include "ActorReference.inl"