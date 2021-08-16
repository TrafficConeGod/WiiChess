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

            Space* GetSpace(Vector2u loc);
            Vector2u GetLoc(size_t index);
        public:
            BoardState(const BoardState& state);
            BoardState(Array<Space>& spaces);

            Array<Space> GetPieceSpaces();

            Array<Move> GetMoves();
            void MoveFromTo(Move move);
    };
}