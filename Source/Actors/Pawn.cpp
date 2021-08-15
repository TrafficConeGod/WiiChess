#include "Pawn.h"

Pawn::Pawn(Stage* _stage) : Piece(_stage), Sprite(_stage), Inputtable(_stage), Actor(_stage) {}

bool Pawn::IsOfType(short id) {
    return id == ID || Piece::IsOfType(id);
}