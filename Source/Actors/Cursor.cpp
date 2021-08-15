#include "Cursor.h"

bool Cursor::IsOfType(short id) {
    return id == ID || RotatableSprite::IsOfType(id) || Inputtable::IsOfType(id);
}

void Cursor::HandlePointer(const ir_t& pointer) {
    Inputtable::HandlePointer(pointer);
    visible = pointer.valid;
    if (pointer.valid) {
        pos = Vector2u(pointer.x, pointer.y);
        radians = DegToRad(pointer.angle);
    }
}