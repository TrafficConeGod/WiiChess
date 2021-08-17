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
        uchar type = initialState[i];
        Chess::Space::Color color = Chess::Space::Color::Black;
        if (type % 10 == 0) {
            color = Chess::Space::Color::White;
            type /= 10;
        }
        spaces << Chess::Space((Chess::Space::Type)type, color);
    }
    engine.Initialize(spaces);

    Array<Vector2u>& pieceLocs = engine.state->pieceLocs;
    for (size_t i = 0; i < pieceLocs.size; i++) {
        Vector2u loc = pieceLocs[i];
        Chess::Space* space = engine.state->GetSpace(loc);
        size_t pieceTypeIndex = space->type;
        pieceTypeIndex--;
        pieceTypeIndex *= 2;
        if (space->color == Chess::Space::Color::White) {
            pieceTypeIndex++;
        }
        // PrintFmt("%d\n", pieceTypeIndex);
        Piece* pieceBase = pieceRefs[pieceTypeIndex];
        if (pieceBase != nullptr) {
            Piece* piece = CreateChildFrom(pieceBase);
            piece->active = true;
            piece->boardRef = this;
            piece->Initialize();
            piece->UpdateLocation(loc);
        }
    }

    engine.state->pieceLocs[2] = Vector2u(-1, -1);
    UpdateDisplay();
}

struct RemovePieceActionState {
    Board* board;
    size_t index;
};

void RemovePieceAction(Piece* piece, RemovePieceActionState* state) {
    Array<Vector2u>& pieceLocs = state->board->engine.state->pieceLocs;
    Vector2u loc = pieceLocs[state->index];
    if (loc == Vector2u(-1, -1)) {
        piece->Delete();
    }
    state->index++;
}

void Board::UpdateDisplay() {
    RemovePieceActionState state = { this, 0 };
    UseChildrenOfWith(&state, RemovePieceAction);
}