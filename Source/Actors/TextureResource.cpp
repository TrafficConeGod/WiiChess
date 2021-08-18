#include "TextureResource.h"

TextureResource* currentTexture = nullptr;

bool TextureResource::IsOfType(short id) {
    return id == ID || Resource::IsOfType(id);
}

void TextureResource::Load(DataStream& stream) {
    Resource::Load(stream);
    TPLFile tplFile;
	TPL_OpenTPLFromFile(&tplFile, path);
	TPL_GetTexture(&tplFile, 0, &texObj);
}

void TextureResource::UseTexture() {
    #ifdef DEBUG_MODE
	if (gfxVisible) {
	#else
	{
    #endif
        if (currentTexture == this) {
            return;
        }
        currentTexture = this;
        GX_LoadTexObj(&texObj, GX_TEXMAP0);
    }
}