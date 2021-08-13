#include "Cursor.h"

Cursor::Cursor(Stage* _stage) : Sprite(_stage), Inputtable(_stage), Actor(_stage) {}

bool Cursor::IsOfType(short id) {
    return id == ID || Sprite::IsOfType(id) || Inputtable::IsOfType(id);
}

void Cursor::HandlePointer(const Vector2i& pointerPos) {
    Inputtable::HandlePointer(pointerPos);
    pos = pointerPos;
}