#include "../pieces.h"
#include "../movement.h"

void PawnGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& moves) {
    Space* space = state->GetSpace(loc);
    uint moveDirY = space->color == Space::Color::Black ? 1 : -1;
    if (AddLocationIfEmpty(state, loc + Vector2i(0, moveDirY), moves)) {
        uint startY = space->color == Space::Color::Black ? 1 : 6;
        if (loc.y == startY) {
            AddLocationIfEmpty(state, loc + Vector2i(0, space->color == Space::Color::Black ? 2 : -2), moves);
        }
    }
    
    AddLocationIfEnemy(state, space->color, loc + Vector2i(1, moveDirY), moves);
    AddLocationIfEnemy(state, space->color, loc + Vector2i(-1, moveDirY), moves);
}