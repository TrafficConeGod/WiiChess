#include "Actor.h"
#include "Stage.h"

template<typename A>
A* Actor::CreateChildFrom(A* actor) {
    A* clone = dynamic_cast<A*>(stage->AllocateActor(A::ID));
    *clone = *actor;
    clone->Initialize();
    MakeChild(dynamic_cast<Actor*>(clone));
    return clone;
}

template<typename A>
void Actor::UseOf(void (*func)(A*)) {
    if (initialized && alive && active && IsOfType(A::ID)) {
        func(dynamic_cast<A*>(this));
    }
}

template<typename T>
void Actor::UseWith(const T& val, void (*func)(Actor*, T)) {
    if (initialized && alive && active) {
        func(this, val);
    }
}

template<typename A, typename T>
void Actor::UseOfWith(const T& val, void (*func)(A*, T)) {
    if (initialized && alive && active && IsOfType(A::ID)) {
        func(dynamic_cast<A*>(this), val);
    }
}



template<typename A>
void Actor::UseChildrenOf(void (*func)(A*)) {
    for (size_t i = 0; i < children.size; i++) {
        if (children[i] != nullptr) {
            children[i]->UseOf(func);
        }
    }
}

template<typename T>
void Actor::UseChildrenWith(const T& val, void (*func)(Actor*, T)) {
    for (size_t i = 0; i < children.size; i++) {
        if (children[i] != nullptr) {
            children[i]->UseWith(val, func);
        }
    }
}

template<typename A, typename T>
void Actor::UseChildrenOfWith(const T& val, void (*func)(A*, T)) {
    for (size_t i = 0; i < children.size; i++) {
        if (children[i] != nullptr) {
            children[i]->UseOfWith(val, func);
        }
    }
}