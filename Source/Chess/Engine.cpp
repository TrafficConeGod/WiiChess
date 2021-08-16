#include "Engine.h"
using namespace Chess;

Engine::~Engine() {
    delete state;
}

void Engine::Initialize(Array<Space>& spaces) {
    state = new BoardState(spaces);
}