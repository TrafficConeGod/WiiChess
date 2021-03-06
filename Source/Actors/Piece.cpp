#include "Piece.h"

bool Piece::IsOfType(short id) {
    return id == ID || Sprite::IsOfType(id) || Inputtable::IsOfType(id);
}

void Piece::Create() {
    Sprite::Create();
    Inputtable::Create();
    origPos = pos;
}

void Piece::Hold() {
    Board* board = boardRef;
    if (board != nullptr) {
        // if (board->turnColor == color) {
            held = true;
            board->ShowMoves(loc);
        // }
    }
}

void Piece::Release() {
    held = false;
    Board* board = boardRef;
    if (board != nullptr) {
        board->HideMoves();
        Vector2u toLoc = (pos - origPos) / size;
        if (board->MovePiece(loc, toLoc)) {
            UpdateLocation(toLoc);
        } else {
            UpdateLocation(loc);
        }
        board->UpdateDisplay(); // no guarantees this piece will exist after calling this
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
        Release();
    }
}

void Piece::ButtonsDown(uint buttons) {
    Inputtable::ButtonsDown(buttons);
    if (hovered && !held && (buttons & WPAD_BUTTON_A)) {
        Hold();
    }
}

void Piece::ButtonsUp(uint buttons) {
    Inputtable::ButtonsUp(buttons);
    if (held && (buttons & WPAD_BUTTON_A)) {
        Release();
    }
}

void Piece::UpdateLocation(const Vector2u& loc) {
    this->loc = loc;
    pos = origPos + (loc * size);
}