#ifndef GOAT_GRAPHICS
#define GOAT_GRAPHICS

#include <NEMain.h>

#define MAX_MATERIAL 3
#define MAX_SPRITE 3
#define MAX_MODEL 3
#define MAX_PALETTE 1

typedef struct
{
    NE_Sprite *sprites[MAX_SPRITE];
    NE_Material *materials[MAX_MATERIAL];
    NE_Model *models[MAX_MODEL];
    NE_Palette *palettes[MAX_PALETTE];
} GraphicsPtrStore;

typedef enum
{
    MODEL_MainChara
} ModelKind;

typedef enum
{
    MAT_MainCharaTex,
    MAT_SpriteTest,
    MAT_TitleScreenBS
} MaterialKind;

typedef enum
{
    SPR_Test
} SpriteKind;

typedef enum
{
    PAL_TitleScreenBS
} PaletteKind;

NE_Model *CreateModel(ModelKind kind, NE_ModelType type);
NE_Model *GetModel(ModelKind kind);

NE_Material *CreateMaterial(MaterialKind kind);
NE_Material *GetMaterial(MaterialKind kind);

NE_Sprite *CreateSprite(SpriteKind kind);
NE_Sprite *GetSprite(SpriteKind kind);

NE_Palette *CreatePalette(PaletteKind kind);
NE_Palette *GetPalette(PaletteKind kind);

#endif