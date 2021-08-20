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
    for (size_t i = 0; i < 64; i++) {
        Array<Vector2u>& moves = allMoves[i];
        Vector2u loc = GetLocation(i);
        Space* space = GetSpace(loc);
        if (space->type == Space::Type::None) {
            continue;
        }
        uint index = ((uint)space->type) - 1;
        (getMovesFuncs[index])(this, loc, moves);

        for (size_t j = 0; j < moves.size; j++) {
            const Vector2u& moveLoc = moves[j];
            uint kingIndex = !((bool)space->color);
            if (moveLoc == kingLocs[kingIndex]) {
                kingChecks[kingIndex] = true;
            }
        }
    }
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

            for (size_t j = 0; j < moves.size; j++) {
                BoardState state = *this;
                const Vector2u& toLoc = moves[j];
                Array<Move> auxMoves;
                state.MovePiece({ loc, toLoc }, auxMoves);
                Array<Vector2u> allStateMoves[64];
                state.GetBasicMoves(allStateMoves);
                
                if (!state.kingChecks[index]) {
                    newMoves << toLoc;
                }
            }
            allMoves[i] = newMoves;
        }
    }

    for (size_t i = 0; i < 2; i++) {
        const Vector2u& loc = kingLocs[i];
        uint index = GetIndex(loc);
        Array<Vector2u>& moves = allMoves[index];

        Array<Vector2u> newMoves;
        for (size_t j = 0; j < moves.size; j++) {
            BoardState state = *this;
            const Vector2u& toLoc = moves[j];
            Array<Move> auxMoves;
            state.MovePiece({ loc, toLoc }, auxMoves);
            Array<Vector2u> allStateMoves[64];
            state.GetBasicMoves(allStateMoves);
            
            if (!state.kingChecks[i]) {
                newMoves << toLoc;
            }
        }
        allMoves[index] = newMoves;
    }

    for (size_t i = 0; i < 64; i++) {
        Array<Vector2u>& moves = allMoves[i];
        Vector2u loc = GetLocation(i);
        Space* space = GetSpace(loc);
        if (space->type == Space::Type::None) {
            continue;
        }

        Array<Vector2u> newMoves;
        for (size_t j = 0; j < moves.size; j++) {
            Space* toSpace = GetSpace(moves[j]);
            if (toSpace->type != Space::Type::King) {
                newMoves << moves[j];
            }
        }
        allMoves[i] = newMoves;
    }
}

void BoardState::MovePiece(const Move& move, Array<Move>& auxMoves) {
    Space* fromSpace = GetSpace(move.from);
    Space* toSpace = GetSpace(move.to);
    fromSpace->modified = true;
    toSpace->modified = true;

    // handle aux moves

    // castle
    uint backRowY = fromSpace->color == Space::Color::Black ? 0 : 7;
    if (fromSpace->type == Space::Type::King && move.from == Vector2u(4, backRowY)) {
        if (move.to == Vector2u(2, backRowY)) {
            auxMoves << Move{ Vector2u(0, backRowY), Vector2u(3, backRowY) };
        } else if (move.to == Vector2u(6, backRowY)) {
            auxMoves << Move{ Vector2u(7, backRowY), Vector2u(5, backRowY) };
        }
    }
    //
    Array<Move> auxMovesBlank;
    for (size_t i = 0; i < auxMoves.size; i++) {
        MovePiece(auxMoves[i], auxMovesBlank);
    }

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
    kingChecks[0] = false;
    kingChecks[1] = false;
}