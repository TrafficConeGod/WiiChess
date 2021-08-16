#pragma once
#include "Array.h"
#include "Vector2.h"
#include "Space.h"

namespace Chess {
    struct Move {
        Vector2u from;
        Vector2u to;
    };
    class BoardState {
        public:
            Array<Vector2u> pieceLocs;
            Vector2u kingLoc = Vector2u(-1, -1);
            Space spaces[64];

            BoardState(const BoardState& state);
            BoardState(Array<Space>& spaces);

            Space* GetSpace(Vector2u loc);
            Vector2u GetLocation(size_t index);
            void GetMoves(Array<Move>& ret);
            void MoveFromTo(Move move);
    };
}