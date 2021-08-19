#include "../pieces.h"
#include "../movement.h"

void PawnGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& moves) {
    Space* space = state->GetSpace(loc);
    uint startY = space->color == Space::Color::Black ? 1 : 6;
    if (loc.y == startY) {
        AddLocationIfEmpty(state, loc + Vector2i(0, space->color == Space::Color::Black ? 2 : -2), moves);
    }
    uint moveDirY = space->color == Space::Color::Black ? 1 : -1;
    AddLocationIfEmpty(state, loc + Vector2i(0, moveDirY), moves);
    
    AddLocationIfEnemy(state, space->color, loc + Vector2i(1, moveDirY), moves);
    AddLocationIfEnemy(state, space->color, loc + Vector2i(-1, moveDirY), moves);
}

void KnightGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret) {}
void BishopGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret) {}
void KingGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret) {}
void QueenGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret) {}