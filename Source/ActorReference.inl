#include "ActorReference.h"

template<typename A>
ActorReference<A>::ActorReference() {}

template<typename A>
ActorReference<A>::ActorReference(Stage* _stage, size_t _index) : stage{_stage}, index{_index} {}

template<typename A>
void ActorReference<A>::operator=(const ActorReference<A>& ref) {
    stage = ref.stage;
    index = ref.index;
}

template<typename A>
ActorReference<A>::ActorReference(const ActorReference<A>& ref) {
    *this = ref;
}

template<typename A>
void ActorReference<A>::operator=(Actor* actor) {
    stage = actor->stage;
    index = actor->index;
}

template<typename A>
ActorReference<A>::ActorReference(Actor* actor) {
    *this = actor;
}

template<typename A>
void ActorReference<A>::Load(Stage* stage, DataStream& stream) {
    this->stage = stage;
    stream >> index;
}

template<typename A>
void ActorReference<A>::Load(Stage* stage, DataStream& stream, Array<ActorReference<A>>& arr) {
    Array<size_t> indices;
    indices.Load(stream);
    for (size_t i = 0; i < indices.size; i++) {
        arr << ActorReference<A>(stage, indices[i]);
    }
}

template<typename A>
bool ActorReference<A>::IsEmpty() {
    return ((A*)(*this)) == nullptr;
}

template<typename A>
ActorReference<A>::operator A*() {
    if (stage == nullptr) {
        return nullptr;
    }
    Actor* actor = stage->GetActorAtIndex(index);
    if (actor == nullptr) {
        return nullptr;
    }
    if (actor->IsOfType(A::ID)) {
        return dynamic_cast<A*>(actor);
    } else {
        return nullptr;
    }
}