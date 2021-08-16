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
        private:
            Array<Vector2u> pieceLocs;
            Space spaces[64];
        public:
            Array<Move> GetMoves();
            void MoveFromTo(Move move);

            BoardState(Array<Space> spaces);
            BoardState(const BoardState& state);
    };
}