#include "movement.h"

void AddLocationIfEmpty(BoardState* state, const Vector2u& loc, Array<Vector2u>& moves) {
    Space* space = state->GetSpace(loc);
    if (space->type == Space::Type::None) {
        moves << loc;
    }
}

void AddLocationIfEnemy(BoardState* state, Space::Color color, const Vector2u& loc, Array<Vector2u>& moves) {
    Space* space = state->GetSpace(loc);
    if (space->type != Space::Type::None && space->color == (!(bool)color)) {
        moves << loc;
    }
}