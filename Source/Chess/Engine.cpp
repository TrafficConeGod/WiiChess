#include "Engine.h"
using namespace Chess;

Engine::~Engine() {
    delete state;
}

void Engine::Initialize(Array<Space>& spaces) {
    state = new BoardState(spaces);

    for (size_t i = 0; i < 64; i++) {
        currentMoves[i] = Array<Vector2u>();
    }
    state->GetMoves(currentMoves);
}

void Engine::MoveFromTo(const Move& move) {
    // handle moving
    //
    //

    

    for (size_t i = 0; i < 64; i++) {
        currentMoves[i] = Array<Vector2u>();
    }
    state->GetMoves(currentMoves);
}