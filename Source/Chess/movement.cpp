#include "movement.h"

void AddLocationIfEmpty(BoardState* state, const Vector2u& loc, Array<Vector2u>& moves) {
    if (loc.x >= 8 || loc.y >= 8) {
        return;
    }
    Space* space = state->GetSpace(loc);
    if (space->type == Space::Type::None) {
        moves << loc;
    }
}

void AddLocationIfEnemy(BoardState* state, Space::Color color, const Vector2u& loc, Array<Vector2u>& moves) {
    if (loc.x >= 8 || loc.y >= 8) {
        return;
    }
    Space* space = state->GetSpace(loc);
    if (space->type != Space::Type::None && space->color == (!(bool)color)) {
        moves << loc;
    }
}

void AddDirectionalLocations(BoardState* state, Vector2u unsLoc, const Vector2i& dir, Array<Vector2u>& moves) {
    Vector2i loc = unsLoc;
    Space* space = state->GetSpace(loc);
    Vector2i curLoc = loc + dir;
    Space* curSpace = state->GetSpace(curLoc);
    while (curLoc.x < 8 && curLoc.y < 8 && curLoc.x >= 0 && curLoc.y >= 0 && curSpace->type == Space::Type::None) {
        moves << curLoc;
        curLoc += dir;
        curSpace = state->GetSpace(curLoc);
    }
    if (curSpace->type != Space::Type::None && curSpace->color == (!(bool)space->color)) {
        moves << curLoc;
    }
}