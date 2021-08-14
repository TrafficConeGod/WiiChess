#include "Sprite.h"
#include "Wii/io.h"

bool Sprite::IsOfType(short id) {
	return id == ID || Actor::IsOfType(id);
}

void Sprite::Load(DataStream& stream) {
	Actor::Load(stream);
	stream >> pos;
	stream >> size;
	stream >> layer;
	textureRef.Load(stage, stream);
}

void Sprite::Draw() {
	#ifdef GFX_MODE
	TextureResource* texture = textureRef;
	if (texture == nullptr) {
		return;
	}
	texture->UseTexture();

	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);			// Draw A Quad
	GX_Position2f32(pos.x, pos.y);					// Top Left
	GX_TexCoord2f32(0, 0);
	GX_Position2f32(pos.x + size.x - 1, pos.y);			// Top Right
	GX_TexCoord2f32(1, 0);
	GX_Position2f32(pos.x + size.x - 1, pos.y + size.y - 1);	// Bottom Right
	GX_TexCoord2f32(1, 1);
	GX_Position2f32(pos.x, pos.y + size.y - 1);			// Bottom Left
	GX_TexCoord2f32(0, 1);
	GX_End();
	#endif
}

static void DrawAction(Sprite* sprite, Array<Array<Sprite*>*>* drawPriority) {
	if (sprite->layer == 0) {
		sprite->Draw();
	} else {
		if (drawPriority->size < sprite->layer) {
			for (size_t i = drawPriority->size; i < sprite->layer; i++) {
				(*drawPriority) << new Array<Sprite*>;
			}
		}
		(*(*drawPriority)[sprite->layer - 1]) << sprite;
	}
}

void Sprite::Draw(Stage* stage) {
	Array<Array<Sprite*>*> drawPriority;
	stage->UseActorsOfWith(&drawPriority, DrawAction);
	for (size_t i = 0; i < drawPriority.size; i++) {
		Array<Sprite*>* layerDrawPriority = drawPriority[i];
		for (size_t j = 0; j < layerDrawPriority->size; j++) {
			(*layerDrawPriority)[i]->Draw();
		}
		delete layerDrawPriority;
	}
}