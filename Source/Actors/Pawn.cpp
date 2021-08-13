#include "Pawn.h"

bool Pawn::IsOfType(short id) {
    return id == ID || Piece::IsOfType(id);
}