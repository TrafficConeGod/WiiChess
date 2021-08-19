#include "../pieces.h"
#include "../movement.h"

void RookGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& moves) {
    AddDirectionalLocations(state, loc, Vector2i(1, 0), moves);
    AddDirectionalLocations(state, loc, Vector2i(-1, 0), moves);
    AddDirectionalLocations(state, loc, Vector2i(0, 1), moves);
    AddDirectionalLocations(state, loc, Vector2i(0, -1), moves);
}