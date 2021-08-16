#include "Board.h"
#include "Piece.h"

bool Board::IsOfType(short id) {
    return id == ID || Sprite::IsOfType(id);
}

void Board::Load(DataStream& stream) {
    Sprite::Load(stream);
    ActorReference<Piece>::Load(stage, stream, pieceRefs);
    initialState.Load(stream);
}

void Board::Create() {
    Sprite::Create();
    Array<Chess::Space> spaces;
    for (size_t i = 0; i < initialState.size; i++) {
        spaces << Chess::Space((Chess::Space::Type)(initialState[i]), Chess::Space::Color::Black);
    }
    boardState = new Chess::BoardState(spaces);


    for (size_t i = 0; i < boardState->pieceLocs.size; i++) {
        Vector2u loc = boardState->pieceLocs[i];
        Chess::Space* space = boardState->GetSpace(loc);
        size_t pieceTypeIndex = space->type;
        pieceTypeIndex--;
        Piece* pieceBase = pieceRefs[pieceTypeIndex];
        if (pieceBase != nullptr) {
            Piece* piece = CreateChildFrom(pieceBase);
            piece->active = true;
            piece->pos = Vector2u(piece->pos.x + (loc.x * piece->size.x), piece->pos.y + (loc.y * piece->size.y));
            piece->Initialize();
        }
    }
}

void Board::Destroy() {
    Sprite::Destroy();
    delete boardState;
}