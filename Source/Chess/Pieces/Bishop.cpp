#include "../pieces.h"
#include "../movement.h"

void BishopGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& moves) {
    AddDirectionalLocations(state, loc, Vector2i(1, 1), moves);
    AddDirectionalLocations(state, loc, Vector2i(-1, -1), moves);
    AddDirectionalLocations(state, loc, Vector2i(1, -1), moves);
    AddDirectionalLocations(state, loc, Vector2i(-1, 1), moves);
}