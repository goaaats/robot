#include "graphics.h"

GraphicsPtrStore g_graphicsStore;

NE_Model *CreateModel(ModelKind kind, NE_ModelType type)
{
    assert(!g_graphicsStore.models[kind]);

    NE_Model *res = NE_ModelCreate(type);
    g_graphicsStore.models[kind] = res;

    return res;
}

NE_Model *GetModel(ModelKind kind)
{
    NE_Model *res = g_graphicsStore.models[kind];

    assert(res);

    return res;
}


NE_Material *CreateMaterial(MaterialKind kind)
{
    assert(!g_graphicsStore.materials[kind]);

    NE_Material *res = NE_MaterialCreate();
    g_graphicsStore.materials[kind] = res;

    return res;
}

NE_Material *GetMaterial(MaterialKind kind)
{
    NE_Material *res = g_graphicsStore.materials[kind];

    assert(res);

    return res;
}


NE_Sprite *CreateSprite(SpriteKind kind)
{
    assert(!g_graphicsStore.sprites[kind]);

    NE_Sprite *res = NE_SpriteCreate();
    g_graphicsStore.sprites[kind] = res;

    return res;
}

NE_Sprite *GetSprite(SpriteKind kind)
{
    NE_Sprite *res = g_graphicsStore.sprites[kind];

    assert(res);

    return res;
}


NE_Palette *CreatePalette(PaletteKind kind)
{
    assert(!g_graphicsStore.palettes[kind]);

    NE_Palette *res = NE_PaletteCreate();
    g_graphicsStore.palettes[kind] = res;

    return res;
}

NE_Palette *GetPalette(PaletteKind kind)
{
    NE_Palette *res = g_graphicsStore.palettes[kind];

    assert(res);

    return res;
}