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
    
}