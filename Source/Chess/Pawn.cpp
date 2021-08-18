#include "pieces.h"

void PawnGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& moves) {
    Space* space = state->GetSpace(loc);
    moves << loc + Vector2u(0, space->color == Space::Color::Black ? 1 : -1);
}

void RookGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret) {}
void KnightGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret) {}
void BishopGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret) {}
void KingGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret) {}
void QueenGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret) {}