#include "Board.h"
#include "Piece.h"

bool Board::IsOfType(short id) {
    return id == ID || Sprite::IsOfType(id);
}

void Board::Load(DataStream& stream) {
    Sprite::Load(stream);
    blackPawnTextureRef.Load(stage, stream);
}

void Board::AddPiece(Piece* piece) {
    MakeChild(piece);
    piece->pos = (piece->loc * 8);
    piece->pos.x += 80;
    piece->textureRef = blackPawnTextureRef;
}