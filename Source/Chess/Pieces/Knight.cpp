#include "../pieces.h"
#include "../movement.h"

void KnightGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& moves) {
    Space* space = state->GetSpace(loc);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(2, 1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(-2, 1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(2, -1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(-2, -1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(1, 2), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(-1, 2), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(1, -2), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(-1, -2), moves);
}