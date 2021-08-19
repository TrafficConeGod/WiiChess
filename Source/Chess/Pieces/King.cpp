#include "../pieces.h"
#include "../movement.h"

void KingGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& moves) {
    Space* space = state->GetSpace(loc);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(1, 0), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(-1, 0), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(0, 1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(0, -1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(1, 1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(-1, -1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(1, -1), moves);
    AddLocationIfEmptyOrEnemy(state, space->color, loc + Vector2i(-1, 1), moves);
}