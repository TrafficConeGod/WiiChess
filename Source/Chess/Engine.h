#pragma once
#include "BoardState.h"

namespace Chess {
    struct Move {
        Vector2u from;
        Vector2u to;
    };
    class Engine {
        public:
            BoardState* state;
            Array<Vector2u> currentMoves[64];

            ~Engine();            

            void Initialize(Array<Space>& spaces);
            void MoveFromTo(const Move& move);
            Move GetBestMoveFor(Space::Color color);
    };
}