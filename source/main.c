#include <stdlib.h>
#include <3ds.h>
#include <math.h>
#include <citro2d.h>

#include "world/gameObject.h"
#include "world/stars.h"
#include "input.h"

#define MAX_SPRITES 1000
#define NUM_STARS 200
#define TOP_SCREEN_WIDTH 400
#define BOTTOM_SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

static C2D_SpriteSheet spriteSheet;
//static gameObject sprites[MAX_SPRITES];
static star stars[NUM_STARS];

int main(int argc, char *argv[])
{
	// Init libs
	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget *topScreen2D = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	// Load graphics
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet)
		svcBreak(USERBREAK_PANIC);

	// Pointer to circle pad pos
	circlePadData *circlePadPos = malloc(sizeof(circlePadData));

	gameObject player = {};
	gameObjectFromSheet(&player, spriteSheet, 46);
	gameObjectSetCenter(&player, 0.5f, 0.53f);
	gameObjectSetPos(&player, TOP_SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	camera playerCam;
	cameraTopScreen(&playerCam);

	generateStars(stars, NUM_STARS);

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();
		circlePadRead(circlePadPos, 30);
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		if (circlePadPos->mag == 0)
		{
			gameObjectSetVel(&player, player.dx * 0.999, player.dy * 0.999);
		}
		else
		{
			gameObjectAccelerate(&player, circlePadPos->dy * sin(player.params.angle) / 500, circlePadPos->dy * cos(player.params.angle) / -500);
			if (abs(circlePadPos->dx) >= 70)
			{
				gameObjectRotate(&player, (float)(circlePadPos->dx + circlePadPos->dx > 0 ? -40 : 40) / -700);
			}
		}

		gameObjectUpdate(&player);

		playerCam.x = -player.params.pos.x + TOP_SCREEN_WIDTH / 2;
		playerCam.y = -player.params.pos.y + SCREEN_HEIGHT / 2;

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(topScreen2D, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(topScreen2D);

		resetCamera();
		// draw all circles before everything else
		drawStars(stars, NUM_STARS, &playerCam);

		useCamera(&playerCam);
		gameObjectDraw(&player, &playerCam);

		C3D_FrameEnd(0);
	}

	// Delete sprite sheet
	C2D_SpriteSheetFree(spriteSheet);
	free(circlePadPos);

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
	return 0;
}
