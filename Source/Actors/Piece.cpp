#include "Piece.h"

bool Piece::IsOfType(short id) {
    return id == ID || Sprite::IsOfType(id) || Inputtable::IsOfType(id);
}

void Piece::HandlePointer(const ir_t& pointer) {
    Inputtable::HandlePointer(pointer);
    if (pointer.valid) {
        if (held) {
            pos = Vector2u(pointer.x, pointer.y);
        } else {
            hovered = (pointer.x >= pos.x && pointer.y >= pos.y && pointer.x < (pos.x + size.x) && pointer.y < (pos.y + size.y));
        }
    } else if (held) {
        pos = origPos;
        held = false;
    }
}

void Piece::ButtonsDown(uint buttons) {
    Inputtable::ButtonsDown(buttons);
    if (hovered && !held && (buttons & WPAD_BUTTON_A)) {
        origPos = pos;
        origin = Vector2f(0.5, 1);
        held = true;
    }
}

void Piece::ButtonsUp(uint buttons) {
    Inputtable::ButtonsUp(buttons);
    if (held && (buttons & WPAD_BUTTON_A)) {
        pos = origPos;
        origin = Vector2f(0, 0);
        held = false;
    }
}