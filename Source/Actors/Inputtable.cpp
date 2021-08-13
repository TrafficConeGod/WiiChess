#include "Inputtable.h"

bool Inputtable::IsOfType(short id) {
    return id == ID || Actor::IsOfType(id);
}

void Inputtable::ButtonsDown(uint) {}
void Inputtable::ButtonsHeld(uint) {}
void Inputtable::ButtonsUp(uint) {}
void Inputtable::HandlePointer(const Vector2i&) {}