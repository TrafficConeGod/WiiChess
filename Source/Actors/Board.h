#pragma once
#include "Sprite.h"

class Piece;

class Board : public virtual Sprite {
    private:
        uint pieceLayer;
        ActorReference<TextureResource> blackPawnTextureRef;
    public:
        static const short ID = 4;

        ActorConstructor(Board)
        virtual bool IsOfType(short id);

        virtual void Load(DataStream& stream);

        void AddPiece(Piece* piece);
};