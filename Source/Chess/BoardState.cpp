#include "BoardState.h"
using namespace Chess;

BoardState::BoardState(Array<Space>& spacesToAdd) {
    for (size_t i = 0; i < 64; i++) {
        if (i < spacesToAdd.size) {
            spaces[i] = spacesToAdd[i];
            if (spaces[i].type > 0) {
                pieceLocs << GetLocation(i);
            }
            if (spaces[i].type == Space::Type::King) {
                kingLoc = GetLocation(i);
            }
        } else {
            spaces[i] = Space();
        }
    }
}

Space* BoardState::GetSpace(Vector2u loc) {
    return &spaces[loc.x + (loc.y * 8)];
}

Vector2u BoardState::GetLocation(size_t index) {
    return Vector2u(index % 8, index / 8);
}