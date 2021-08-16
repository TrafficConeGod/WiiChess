#include "BoardState.h"
using namespace Chess;

BoardState::BoardState(Array<Space>& spacesToAdd) {
    for (size_t i = 0; i < 64; i++) {
        if (i < spacesToAdd.size) {
            spaces[i] = spacesToAdd[i];
            if (spaces[i].type > 0) {
                pieceLocs << GetLoc(i);
            }
        } else {
            spaces[i] = Space();
        }
    }
}

Space* BoardState::GetSpace(Vector2u loc) {
    return spaces[loc.x + (loc.y * 8)];
}

Vector2u BoardState::GetLoc(size_t index) {
    return Vector2u(index % 8, index / 8);
}

Array<Space> BoardState::GetPieceSpaces() {
    Array<Space> pieceSpaces;
    for (size_t i = 0; i < pieceLocs.size; i++) {
        pieceSpaces << GetSpace(pieceLocs[i]);
    }
    return pieceSpaces;
}