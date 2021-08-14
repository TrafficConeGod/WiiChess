#include "Cursor.h"

Cursor::Cursor(Stage* _stage) : RotatableSprite(_stage), Sprite(_stage), Inputtable(_stage), Actor(_stage) {}

bool Cursor::IsOfType(short id) {
    return id == ID || RotatableSprite::IsOfType(id) || Inputtable::IsOfType(id);
}

void Cursor::HandlePointer(const ir_t& pointer) {
    Inputtable::HandlePointer(pointer);
    pos = Vector2i(pointer.x, pointer.y);
    radians = pointer.angle;
}