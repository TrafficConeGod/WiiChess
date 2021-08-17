#pragma once
#include "Wii/type.h"
#include "DataStream.h"
#include "Array.h"

#define ActorConstructor(name) name() {} \
name(Stage* _stage) : Actor(_stage) {}

class Stage;

class Actor {
    private:
        void RemoveChild(Actor* actor);
    protected:
        bool initialized = false;
        bool alive = false;

        Actor* parent = nullptr;
        Array<Actor*> children;

        Actor* CreateChild(short id);
        Actor* CreateChildFrom(DataStream& stream);
        void MakeChild(Actor* actor);
        template<typename A>
        A* CreateChildFrom(A* actor);

        virtual void Create();
    public:
        static const uint ID = 1;
        
        bool active = false;
        size_t index = 0;
        Stage* stage = nullptr;

        Actor(Stage* stage);
        Actor();
        ~Actor();

        virtual bool IsOfType(short id);

        void Use(void (*func)(Actor*));

        template<typename A>
        void UseOf(void (*func)(A*));

        template<typename T>
        void UseWith(const T& val, void (*func)(Actor*, T));

        template<typename A, typename T>
        void UseOfWith(const T& val, void (*func)(A*, T));

        void UseChildren(void (*func)(Actor*));

        template<typename A>
        void UseChildrenOf(void (*func)(A*));

        template<typename T>
        void UseChildrenWith(const T& val, void (*func)(Actor*, T));

        template<typename A, typename T>
        void UseChildrenOfWith(const T& val, void (*func)(A*, T));

        void Initialize();
        void Delete();

        virtual void Load(DataStream& stream);
        virtual void Destroy();
        virtual void Update();
};

#include "Actor.inl"