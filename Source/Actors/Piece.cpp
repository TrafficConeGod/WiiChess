#include "Piece.h"

bool Piece::IsOfType(short id) {
    return id == ID || Sprite::IsOfType(id) || Inputtable::IsOfType(id);
}

void Piece::Load(DataStream& stream) {
    boardRef.Load(stage, stream);
    stream >> color;
    stream >> loc;
}

void Piece::Create() {
    Sprite::Create();
    size = Vector2u(60, 60);
    Board* board = boardRef;
    if (board == nullptr) {
        return;
    }
    board->AddPiece(this);
}

void Piece::Update() {
    Sprite::Update();
    Inputtable::Update();
    if (held) {

    }
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
        held = true;
    }
}

void Piece::ButtonsUp(uint buttons) {
    Inputtable::ButtonsUp(buttons);
    if (held && (buttons & WPAD_BUTTON_A)) {
        pos = origPos;
        held = false;
    }
}