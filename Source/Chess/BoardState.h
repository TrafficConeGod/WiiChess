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
            Vector2u kingLocs[2];
            bool kingChecks[2];
            Space spaces[64];

            BoardState(const BoardState& state);
            BoardState(Array<Space>& spaces);

            Space* GetSpace(const Vector2u& loc);
            size_t GetIndex(const Vector2u& loc);
            Vector2u GetLocation(size_t index);
            void GetMoves(Array<Vector2u>* ret);
            void GetMovesAt(const Vector2u& loc, Array<Vector2u>& ret);
            void MovePiece(const Move& move);
    };
}