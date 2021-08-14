#include "Board.h"
#include "Piece.h"

bool Board::IsOfType(short id) {
    return id == ID || Sprite::IsOfType(id);
}

void Board::Load(DataStream& stream) {
    Sprite::Load(stream);
    stream >> pieceZIndex;
    blackPawnTextureRef.Load(stage, stream);
}

void Board::AddPiece(Piece* piece) {
    MakeChild(piece);
    piece->pos = (piece->loc * 60);
    piece->pos.x += 80;
    piece->zIndex = pieceZIndex;
    piece->textureRef = blackPawnTextureRef;
}