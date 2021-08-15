#include "Sprite.h"
#include "Wii/io.h"
#include <unistd.h>

static size_t currentSpriteDrawOrderIndex;
static Array<Sprite*> spriteDrawOrder;

bool Sprite::IsOfType(short id) {
	return id == ID || Actor::IsOfType(id);
}

void Sprite::Load(DataStream& stream) {
	Actor::Load(stream);
	stream >> pos;
	stream >> size;
	stream >> origin;
	stream >> visible;
	stream >> layer;
	textureRef.Load(stage, stream);
}

void Sprite::Create() {
	Actor::Create();

	spriteDrawOrder << this;
	// Why wont this code wont work? I dont fucking know, all i know is im done with trying to get it to work
	
	// bool inserted = false;
	// for (size_t i = 0; i < spriteDrawOrder.size; i++) {
	// 	if (spriteDrawOrder[i]->layer > layer && spriteDrawOrder.size) {
	// 		spriteDrawOrder << spriteDrawOrder[spriteDrawOrder.size - 1];
	// 		if (i != (spriteDrawOrder.size - 2)) {
	// 			Sprite* curSprite = spriteDrawOrder[i];
	// 			for (size_t j = i; j < (spriteDrawOrder.size - 1); j++) {
	// 				Sprite* nextCurSprite = spriteDrawOrder[j + 1];
	// 				spriteDrawOrder[j + 1] = curSprite;
	// 				curSprite = nextCurSprite;
	// 			}
	// 		}
	// 		spriteDrawOrder[i] = this;
	// 		inserted = true;
	// 		break;
	// 	}
	// }
	// if (!inserted) {
	// 	spriteDrawOrder << this;
	// }
}

void Sprite::UpdateDrawOrder() {
	if (currentSpriteDrawOrderIndex != 0) {
		Sprite* previousSprite = spriteDrawOrder[currentSpriteDrawOrderIndex - 1];
		if (previousSprite->layer > layer) {
			// swap sprites
			spriteDrawOrder[currentSpriteDrawOrderIndex - 1] = this;
			spriteDrawOrder[currentSpriteDrawOrderIndex] = previousSprite;
		}
	}
}

void Sprite::Destroy() {
	Actor::Destroy();
	for (size_t i = currentSpriteDrawOrderIndex; i < (spriteDrawOrder.size - 1); i++) {
		spriteDrawOrder[i] = spriteDrawOrder[i + 1];
	}
	// into the trash it goes
	Sprite* trashSprite;
	spriteDrawOrder >> trashSprite;
}

void Sprite::Draw(Stage* stage /* Pretend like this does something with stage to allow this */) {
	for (currentSpriteDrawOrderIndex = 0; currentSpriteDrawOrderIndex < spriteDrawOrder.size; currentSpriteDrawOrderIndex++) {
		spriteDrawOrder[currentSpriteDrawOrderIndex]->UpdateDrawOrder();
	}
	for (size_t i = 0; i < spriteDrawOrder.size; i++) {
		spriteDrawOrder[i]->Draw();
	}
}

void Sprite::Draw() {
	#ifdef GFX_MODE
	if (!visible) {
		return;
	}
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