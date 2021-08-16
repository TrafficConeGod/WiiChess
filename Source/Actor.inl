#include "Actor.h"
#include "Stage.h"

template<typename A>
A* Actor::CreateChildFrom(A* actor) {
    A* clone = dynamic_cast<A*>(stage->AllocateActor(A::ID));
    *clone = *actor;
    clone->Initialize();
    children << dynamic_cast<Actor*>(clone);
    return clone;
}

template<typename A>
void Actor::UseOf(void (*func)(A*)) {
    if (initialized && alive && IsOfType(A::ID)) {
        func(dynamic_cast<A*>(this));
    }
}

template<typename T>
void Actor::UseWith(const T& val, void (*func)(Actor*, T)) {
    if (initialized && alive) {
        func(this, val);
    }
}

template<typename A, typename T>
void Actor::UseOfWith(const T& val, void (*func)(A*, T)) {
    if (initialized && alive && IsOfType(A::ID)) {
        func(dynamic_cast<A*>(this), val);
    }
}