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
            Space spaces[64];

            BoardState(const BoardState& state);
            BoardState(Array<Space>& spaces);

            Space* GetSpace(Vector2u loc);
            Vector2u GetLoc(size_t index);
            void GetMoves(Array<Move>& ret);
            void MoveFromTo(Move move);
    };
}