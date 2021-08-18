#include "Actor.h"
#include "Stage.h"
#include "Wii/mem.h"
#include "Wii/io.h"

Actor::Actor(Stage* _stage) : stage{_stage}, index{_stage->GetCurrentIndex()} {}

Actor::Actor() {}

static void DestroyAction(Actor* actor) {
    actor->Destroy();
}

Actor::~Actor() {
}

void Actor::Initialize() {
    // we want the actor lifecycle to be active but for the actor to not actually be alive yet
    if (active && !initialized) {
        initialized = true;
        Create();
    }
}

static void DeleteAction(Actor* actor) {
    actor->Delete();
}

void Actor::Delete() {
    if (alive && active) {
        Destroy();
        UseChildren(DeleteAction);
        delete this;
    }
}

void Actor::Use(void (*func)(Actor*)) {
    if (initialized && alive && active) {
        func(this);
    }
}

void Actor::UseChildren(void (*func)(Actor*)) {
    for (size_t i = 0; i < children.size; i++) {
        if (children[i] != nullptr) {
            children[i]->Use(func);
        }
    }
}

Actor* Actor::CreateChild(short id) {
    Actor* actor = stage->AllocateActor(id);
    actor->Initialize();
    MakeChild(actor);
    return actor;
}

Actor* Actor::CreateChildFrom(DataStream& stream) {
    Actor* actor = stage->LoadActor(stream);
    actor->Initialize();
    MakeChild(actor);
    return actor;
}

void Actor::MakeChild(Actor* actor) {
    if (actor->parent == nullptr) {
        actor->parent = this;
        children << actor;
    }
}

void Actor::RemoveChild(Actor* actor) {
    actor->parent = nullptr;
    for (size_t i = 0; i < children.size; i++) {
        if (children[i] == actor) {
            children[i] = nullptr;
            break;
        }
    }
}

bool Actor::IsOfType(short id) {
    return id == ID;
}

void Actor::Load(DataStream& stream) {
    stream >> active;
}

void Actor::Create() {
    alive = true;
}

void Actor::Destroy() {
    alive = false;
    stage->RemoveActor(index);
    if (parent != nullptr) {
        parent->RemoveChild(this);
    }
    UseChildren(DestroyAction);
}

void Actor::Update() {}