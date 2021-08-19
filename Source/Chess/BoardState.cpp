#include "BoardState.h"
#include "pieces.h"
using namespace Chess;

void BoardState::operator=(const BoardState& state) {
    pieceLocs = state.pieceLocs;
    for (size_t i = 0; i < 2; i++) {
        kingLocs[i] = state.kingLocs[i];
        kingChecks[i] = state.kingChecks[i];
    }
    for (size_t i = 0; i < 64; i++) {
        spaces[i] = state.spaces[i];
    }
}

BoardState::BoardState(const BoardState& state) {
    *this = state;
}

BoardState::BoardState(Array<Space>& spacesToAdd) {
    kingChecks[0] = false;
    kingChecks[1] = false;
    for (size_t i = 0; i < 64; i++) {
        if (i < spacesToAdd.size) {
            spaces[i] = spacesToAdd[i];
            Space* space = &spaces[i];
            if (space->type > 0) {
                pieceLocs << GetLocation(i);
            }
            if (space->type == Space::Type::King) {
                kingLocs[(uint)space->color] = GetLocation(i);
            }
        } else {
            spaces[i] = Space();
        }
    }
}

Space* BoardState::GetSpace(const Vector2u& loc) {
    return &spaces[GetIndex(loc)];
}

size_t BoardState::GetIndex(const Vector2u& loc) {
    return loc.x + (loc.y * 8);
}

Vector2u BoardState::GetLocation(size_t index) {
    return Vector2u(index % 8, index / 8);
}

void BoardState::GetBasicMoves(Array<Vector2u>* allMoves) {
    bool currentKingChecks[2] = { false, false };

    for (size_t i = 0; i < 64; i++) {
        Array<Vector2u>& moves = allMoves[i];
        Vector2u loc = GetLocation(i);
        Space* space = GetSpace(loc);
        if (space->type == Space::Type::None) {
            continue;
        }
        uint index = ((uint)space->type) - 1;
        (getMovesFuncs[index])(this, loc, moves);

        for (size_t i = 0; i < moves.size; i++) {
            const Vector2u& moveLoc = moves[i];
            uint kingIndex = !((bool)space->color);
            if (moveLoc == kingLocs[kingIndex]) {
                currentKingChecks[kingIndex] = true;
            }
        }
    }
    kingChecks[0] = currentKingChecks[0];
    kingChecks[1] = currentKingChecks[1];
}

void BoardState::GetMoves(Array<Vector2u>* allMoves) {
    GetBasicMoves(allMoves);

    for (size_t i = 0; i < 64; i++) {
        Array<Vector2u>& moves = allMoves[i];
        Vector2u loc = GetLocation(i);
        Space* space = GetSpace(loc);
        if (space->type == Space::Type::None) {
            continue;
        }
        uint index = (uint)space->color;

        if (kingChecks[index]) {
            Array<Vector2u> newMoves;

            for (size_t i = 0; i < moves.size; i++) {
                BoardState state = *this;
                const Vector2u& toLoc = moves[i];
                state.MovePiece({ loc, toLoc });
                Array<Vector2u> allStateMoves[64];
                state.GetBasicMoves(allStateMoves);
                
                if (!state.kingChecks[index]) {
                    newMoves << toLoc;
                }
            }
            allMoves[i] = newMoves;
        }
    }
}

void BoardState::MovePiece(const Move& move) {
    Space* fromSpace = GetSpace(move.from);
    Space* toSpace = GetSpace(move.to);
    if (move.from == kingLocs[(uint)fromSpace->color]) {
        kingLocs[(uint)fromSpace->color] = move.to;
    }
    for (size_t i = 0; i < pieceLocs.size; i++) {
        if (pieceLocs[i] == move.to) {
            pieceLocs[i] = Vector2u(-1, -1);
        }
    }
    for (size_t i = 0; i < pieceLocs.size; i++) {
        if (pieceLocs[i] == move.from) {
            pieceLocs[i] = move.to;
        }
    }
    toSpace->type = fromSpace->type;
    toSpace->color = fromSpace->color;
    *fromSpace = Space();
}