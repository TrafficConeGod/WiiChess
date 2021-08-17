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
	bool found = false;
	size_t index = 0;
	for (size_t i = 0; i < spriteDrawOrder.size; i++) {
		if (spriteDrawOrder[i] == this) {
			found = true;
			index = i;
			break;
		}
	}
	if (!found) {
		return;
	}
	for (size_t i = index; i < (spriteDrawOrder.size - 1); i++) {
		spriteDrawOrder[i] = spriteDrawOrder[i + 1];
	}
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

static const Vector2u texCoords[] = {
    Vector2u(0, 0),
    Vector2u(1, 0),
    Vector2u(1, 1),
    Vector2u(0, 1),
};

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

    Vector2f quad[] = {
        Vector2f(0, 0),
        Vector2f(1, 0),
        Vector2f(1, 1),
        Vector2f(0, 1)
    };

    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
    for (uchar i = 0; i < 4; i++) {
        Vector2f vert = quad[i];

        // origin
        vert += origin;

        // scale
        vert.x *= size.x - 1;
        vert.y *= size.y - 1;

        // translate
        vert += pos;

        GX_Position2f32(vert.x, vert.y);	
        GX_Position2f32(texCoords[i].x, texCoords[i].y);	
    }
	GX_End();
	#endif
}