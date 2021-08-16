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
	if (!visible) {
		return;
	}
	TextureResource* texture = textureRef;
	if (texture == nullptr) {
		return;
	}
	texture->UseTexture();

    Vector2f rot(cos(radians), sin(radians));

    Vector2f quad[] = {
        Vector2f(0, 0),
        Vector2f(1, 0),
        Vector2f(1, 1),
        Vector2f(0, 1)
    };

    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
    for (uchar i = 0; i < 4; i++) {
        Vector2f& orig = quad[i];
        Vector2f vert = quad[i];

        // origin
        vert += origin;

        // rotate
        vert.x = (orig.x * cos(radians)) - (orig.y * sin(radians));
        vert.y = (orig.x * sin(radians)) + (orig.y * cos(radians));

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