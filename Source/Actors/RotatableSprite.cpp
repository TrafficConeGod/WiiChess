#include "RotatableSprite.h"
#include <math.h>

bool RotatableSprite::IsOfType(short id) {
    return id == ID || Sprite::IsOfType(id);
}

void RotatableSprite::Load(DataStream& stream) {
    Sprite::Load(stream);
    uint degrees;
    stream >> degrees;
    radians = DegToRad(degrees);
}

static const Vector2u texCoords[] = {
    Vector2u(0, 0),
    Vector2u(1, 0),
    Vector2u(1, 1),
    Vector2u(0, 1),
};

void RotatableSprite::Draw() {
	#ifdef GFX_MODE
	TextureResource* texture = textureRef;
	if (texture == nullptr) {
		return;
	}
	texture->UseTexture();

    Vector2f rot(cos(radians), sin(radians));

    Vector2f quad[] = {
        Vector2f(0, 0),
        Vector2f(rot.x, rot.y),
        Vector2f(rot.x - rot.y, rot.y + rot.x),
        Vector2f(-rot.y, rot.x)
    };

    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
    for (uchar i = 0; i < 4; i++) {
        // rotation
        Vector2f vert = quad[i];

        // scale
        vert.x *= size.x - 1;
        vert.y *= size.y - 1;

        // translate
        vert.x += pos.x;
        vert.y += pos.y;

        GX_Position2f32(vert.x, vert.y);	
        GX_Position2f32(texCoords[i].x, texCoords[i].y);	
    }
	GX_End();
	#endif
}