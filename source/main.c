/* ROBOT GAME */
/* By: goat, yoe, ryan */

#include <NEMain.h>
#include <nds/ndstypes.h>
#include <stdio.h>
#include <maxmod9.h>

#include "asset.h"
#include "cmath.h"
#include "state.h"
#include "graphics.h"

#include "testsprite_bin.h"

int frame = 0;

/* CONSTANT */

#define DS_SCREEN_WIDTH 256
#define DS_SCREEN_HEIGHT 192

#define TEXT_SLOT_DEBUG 0

#define MODEL_HEIGHT_OFFSET 2.5f

/* END CONSTANT */

GAME_MainState g_gameState;

/* CAMERA */

NE_Camera *TSCamera;

void HandleCamInput()
{
	Point p;
	NE_Model *mainChara = GetModel(MODEL_MainChara);

	p = GetPointInCircle(mainChara->x, mainChara->y, mainChara->z, g_gameState.overviewZoomRadius, g_gameState.overviewTurnDeg);
	NE_CameraSet(TSCamera, p.x, MODEL_HEIGHT_OFFSET, p.z, mainChara->x, mainChara->y + MODEL_HEIGHT_OFFSET, mainChara->z, 0, 1, 0);
}

/* END CAMERA */

void DrawDebug()
{
	char text[180];
	sprintf(text, "X: %f / Y: %f / Z: %f / D: %i / C: %d%% / %i",
		f32tofloat(TSCamera->from[0]), f32tofloat(TSCamera->from[1]), f32tofloat(TSCamera->from[2]), g_gameState.overviewTurnDeg, NE_GetCPUPercent(), frame);
	NE_TextPrint(0, 0, 0, NE_White, text);
}

void DrawOverviewFrame()
{
	
}

void DrawTopScreen(void)
{
	// Set rear plane color
	NE_ClearColorSet(NE_DarkGray, 31, 63);

	NE_CameraUse(TSCamera);
	NE_PolyFormat(31, 0, NE_LIGHT_0, NE_CULL_NONE, 0);
	NE_ModelDraw(GetModel(MODEL_MainChara));

	NE_2DViewInit();
	NE_SpriteDrawAll();

	DrawOverviewFrame();
}

void DrawBottomScreen(void)
{
	NE_2DViewInit();

	NE_2DDrawTexturedQuad(0, 0,
			      DS_SCREEN_WIDTH, DS_SCREEN_HEIGHT,
			      0, GetMaterial(MAT_TitleScreenBS));

	DrawDebug();
}

void SetUpTextAsset()
{
	CreateMaterial(MAT_TextDebug);
	NE_MaterialTexLoadBMPtoRGBA(GetMaterial(MAT_TextDebug), (void *)debugtext_bmp_bin, true);

	NE_TextInit(TEXT_SLOT_DEBUG,
		    GetMaterial(MAT_TextDebug),
		    8, 8); // Size of one character (x, y)
}

void SetUpTitleScreenAsset()
{
	CreateMaterial(MAT_TitleScreenBS);
	CreatePalette(PAL_TitleScreenBS);

	NE_MaterialTexLoad(GetMaterial(MAT_TitleScreenBS), GL_RGB256, DS_SCREEN_WIDTH, DS_SCREEN_HEIGHT, TEXGEN_OFF,
			   (u8 *) titlebs_tex_bin);

	NE_PaletteLoad(GetPalette(PAL_TitleScreenBS), (u16 *)titlebs_pal_bin, 256, GL_RGB256);

	NE_MaterialTexSetPal(GetMaterial(MAT_TitleScreenBS), GetPalette(PAL_TitleScreenBS));
}

void SetUp3DAsset()
{
	// Allocate space for the objects we'll use
	TSCamera = NE_CameraCreate();
	CreateModel(MODEL_MainChara, NE_Static);
	CreateMaterial(MAT_MainCharaTex);

	// Set coordinates for the camera
	NE_CameraSet(TSCamera,
		     -4, 4, 0, // Position
		     0, 0, 0,  // Look at
		     0, 3, 0); // Up direction

	// Load mesh from RAM and assign it to the object "Model".
	NE_ModelLoadStaticMesh(GetModel(MODEL_MainChara), (u32 *)goat_bin);
	// Load a RGB texture from RAM and assign it to "Material".
	NE_MaterialTexLoad(GetMaterial(MAT_MainCharaTex), GL_RGB, 128, 128, TEXGEN_TEXCOORD,
			   (u8 *) texture_bin);

	// Assign texture to model...
	NE_ModelSetMaterial(GetModel(MODEL_MainChara), GetMaterial(MAT_MainCharaTex));

	// We set up a light and its color
	NE_LightSet(0, NE_White, -0.5, -0.5, -0.5);

	// Enable shading...
	//NE_ShadingEnable(true);
	NE_OutliningEnable(true);
	NE_OutliningSetColor(0, NE_White);

	NE_AntialiasEnable(true);
}

int main(void)
{
	irqEnable(IRQ_HBLANK);
	irqSet(IRQ_VBLANK, NE_VBLFunc);
	irqSet(IRQ_HBLANK, NE_HBLFunc);

	mmInitDefaultMem( (mm_addr)soundbank_bin );
	mmLoad( MOD_ELYSIUM );
	//mmStart( MOD_ELYSIUM, MM_PLAY_LOOP );

	// Init Nitro Engine in dual 3D mode
	NE_InitDual3D();

	CreateMaterial(MAT_SpriteTest);
	NE_MaterialTexLoadBMPtoRGBA(GetMaterial(MAT_SpriteTest), (void *)testsprite_bin, 1);

	NE_ClearColorSet(NE_Gray, 31, 63);

	CreateSprite(SPR_Test);
	NE_SpriteSetPos(GetSprite(SPR_Test), 0, 0);
	NE_SpriteSetSize(GetSprite(SPR_Test), 128, 128);
	NE_SpriteSetPriority(GetSprite(SPR_Test), 10);
	NE_SpriteSetMaterial(GetSprite(SPR_Test), GetMaterial(MAT_SpriteTest));

	SetUp3DAsset();
	SetUpTitleScreenAsset();
	SetUpTextAsset();

	g_gameState.mode = Overview;
	g_gameState.overviewZoomRadius = 1.5f;

	while (1) {
		// Get keys information
		scanKeys();
		uint32 keys = keysHeld();

		printf("\x1b[0;0H%i", frame);
		frame++;

		switch (g_gameState.mode)
		{
		case Overview:
			/* code */

			if (keys & KEY_UP)
			{
				g_gameState.overviewTurnDeg++;
			}

			if (keys & KEY_DOWN)
			{
				g_gameState.overviewTurnDeg--;
			}
			break;

		default:
			break;
		}

		HandleCamInput();

		// Draw scene
		NE_ProcessDual(DrawTopScreen, DrawBottomScreen);
		// Wait for next frame
		NE_WaitForVBL(0);
	}

	return 0;
}
