#pragma once
#include "BoardState.h"

namespace Chess {
    class Engine {
        private:
            BoardState state;
        public:
            Engine(Array<Space>& spaces);

            Array<Space> GetPieceSpaces();

            Array<Move> GetMoves();
            Move GetBestMoveFor(Space::Color color);
            void MoveFromTo(Move move);
    };
}