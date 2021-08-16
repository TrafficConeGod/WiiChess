#pragma once
#include "BoardState.h"

namespace Chess {
    class Engine {
        public:
            BoardState* state;

            ~Engine();            

            void Initialize(Array<Space>& spaces);
            Move GetBestMoveFor(Space::Color color);
    };
}