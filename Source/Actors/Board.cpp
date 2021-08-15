#include "Board.h"
#include "Piece.h"

bool Board::IsOfType(short id) {
    return id == ID || Sprite::IsOfType(id);
}

void Board::Load(DataStream& stream) {
    Sprite::Load(stream);
    blackPawnRef.Load(stage, stream);
}

void Board::Create() {
    
}

void Board::AddPiece(Piece* piece) {
    
}