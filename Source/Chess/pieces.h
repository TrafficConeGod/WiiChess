#pragma once
#include "Array.h"
#include "Vector2.h"
#include "BoardState.h"

using namespace Chess;

typedef void (*getMoveFunc)(BoardState*, const Vector2u&, Array<Vector2u>&);

void PawnGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret);
void RookGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret);
void KnightGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret);
void BishopGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret);
void KingGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret);
void QueenGetMoves(BoardState* state, const Vector2u& loc, Array<Vector2u>& ret);

const getMoveFunc getMovesFuncs[] = {
    PawnGetMoves,
    RookGetMoves,
    KnightGetMoves,
    BishopGetMoves,
    KingGetMoves,
    QueenGetMoves
};