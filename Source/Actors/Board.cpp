#include "Board.h"
#include "Piece.h"
#include "MoveHint.h"

bool Board::IsOfType(short id) {
    return id == ID || Sprite::IsOfType(id);
}

void Board::Load(DataStream& stream) {
    Sprite::Load(stream);
    ActorReference<Piece>::Load(stage, stream, pieceRefs);
    initialState.Load(stream);
    moveHintRef.Load(stage, stream);
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
        const Vector2u& loc = pieceLocs[i];
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
            piece->color = space->color;
            piece->boardRef = this;
            piece->Initialize();
            piece->UpdateLocation(loc);
        }
    }

    UpdateDisplay();
}

struct RemovePieceActionState {
    Board* board;
    size_t index;
};

void UpdateRemovedPieceIndex(RemovePieceActionState* state) {
    for (size_t i = 0; i < state->board->removedPieceIndices.size; i++) {
        size_t index = state->board->removedPieceIndices[i];
        if (state->index == index) {
            state->index++;
            UpdateRemovedPieceIndex(state);
            break;
        }
    }
}

void RemovePieceAction(Piece* piece, RemovePieceActionState* state) {
    UpdateRemovedPieceIndex(state);

    Array<Vector2u>& pieceLocs = state->board->engine.state->pieceLocs;
    const Vector2u& loc = pieceLocs[state->index];
    if (loc == Vector2u(-1, -1)) {
        state->board->removedPieceIndices << state->index;
        piece->Delete();
    }
    state->index++;
}

void Board::UpdateDisplay() {
    RemovePieceActionState state = { this, 0 };
    UseChildrenOfWith(&state, RemovePieceAction);
}

void Board::ShowMoves(const Vector2u& loc) {
    size_t index = engine.state->GetIndex(loc);
    Array<Vector2u>& moves = engine.currentMoves[index];
    for (size_t i = 0; i < moves.size; i++) {
        const Vector2u& moveLoc = moves[i];
        MoveHint* hintBase = moveHintRef;
        if (hintBase != nullptr) {
            MoveHint* hint = CreateChildFrom(hintBase);
            hint->active = true;
            hint->pos += (moveLoc * hint->size);
            hint->Initialize();
        }
    }
}

void RemoveHintAction(MoveHint* hint) {
    hint->Delete();
}

void Board::HideMoves() {
    UseChildrenOf(RemoveHintAction);
}

bool Board::MovePiece(const Vector2u& from, const Vector2u& to) {
    size_t index = engine.state->GetIndex(from);
    Array<Vector2u>& moves = engine.currentMoves[index];

    bool valid = false;
    for (size_t i = 0; i < moves.size; i++) {
        const Vector2u& moveLoc = moves[i];
        if (moveLoc == to) {
            valid = true;
            break;
        }
    }
    if (!valid) {
        return false;
    }

    engine.MoveFromTo({ from, to });

    turnColor = (Chess::Space::Color)(!((bool)turnColor));
    return true;
}