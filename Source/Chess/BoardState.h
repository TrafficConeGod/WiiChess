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
            Vector2u kingLocs[2];
            bool kingChecks[2];
            
            void GetBasicMoves(Array<Vector2u>* ret);
        public:
            Array<Vector2u> pieceLocs;
            Space spaces[64];

            void operator=(const BoardState& state);
            BoardState(const BoardState& state);
            BoardState(Array<Space>& spaces);

            Space* GetSpace(const Vector2u& loc);
            size_t GetIndex(const Vector2u& loc);
            Vector2u GetLocation(size_t index);
            void GetMoves(Array<Vector2u>* ret);
            void MovePiece(const Move& move, Array<Move>& ret);
    };
}