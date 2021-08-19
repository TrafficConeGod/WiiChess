#pragma once
#include "Array.h"
#include "Vector2.h"
#include "BoardState.h"

using namespace Chess;

void AddLocationIfEmpty(BoardState* state, const Vector2u& loc, Array<Vector2u>& moves);
void AddLocationIfEnemy(BoardState* state, Space::Color color, const Vector2u& loc, Array<Vector2u>& moves);
void AddLocationIfEmptyOrEnemy(BoardState* state, Space::Color color, const Vector2u& loc, Array<Vector2u>& moves);
void AddDirectionalLocations(BoardState* state, Vector2u loc, const Vector2i& dir, Array<Vector2u>& moves);