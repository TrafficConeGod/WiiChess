#pragma once
#include "BoardState.h"

namespace Chess {
    class Engine {
        public:
            BoardState* state;
            Array<Vector2u> currentMoves[64];

            ~Engine();            

            void Initialize(Array<Space>& spaces);
            void MoveFromTo(const Move& move, Array<Move>& ret);
            Move GetBestMoveFor(Space::Color color);
    };
}