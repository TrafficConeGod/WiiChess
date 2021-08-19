#pragma once
#include "Array.h"
#include "Vector2.h"
#include "BoardState.h"

using namespace Chess;

void AddLocationIfEmpty(BoardState* state, const Vector2u& loc, Array<Vector2u>& moves);
void AddLocationIfEnemy(BoardState* state, Space::Color color, const Vector2u& loc, Array<Vector2u>& moves);