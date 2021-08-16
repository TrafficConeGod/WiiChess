#pragma once
#include "BoardState.h"

namespace Chess {
    class Engine {
        private:
            BoardState state;
        public:
            Engine(Array<Space>& spaces);

            void GetPieceSpaces(Array<Space*>& ret);
            void GetMoves(Array<Move>& ret);
            Move GetBestMoveFor(Space::Color color);
            void MoveFromTo(Move move);
    };
}