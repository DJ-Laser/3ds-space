#include <stdlib.h>
#include <math.h>
#include <3ds.h>
#include <citro2d.h>

#include "world/gameObject.h"
#include "world/stars.h"
#include "input.h"
#include "vec.h"
#include "ui.h"

#define MAX_SPRITES 1000
#define NUM_STARS 200

typedef gameObject *gameObject_vec;

static C2D_SpriteSheet spriteSheet;
static gameObject_vec sprites;
static gameObject player = {};
static star stars[NUM_STARS];

gameObject *generateSpaceObject(int imageIdx)
{
	gameObject *temp = vector_add_asg(&sprites);
	gameObjectFromSheet(temp, spriteSheet, imageIdx);
	gameObjectSetCenter(temp, 0.5f, 0.5f);
	gameObjectSetPos(temp, ((rand() / 100) % 20000) - 10000, ((rand() / 100) % 20000) - 10000);
	gameObjectSetRot(temp, rand() % 10);
	gameObjectSetDepth(temp, 0.1 + (rand() % 500) / 1000);
	return temp;
}

void generateShip(int imageIdx)
{
	gameObject *temp = generateSpaceObject(imageIdx);
}

void generateMeteor(int imageIdx)
{
	gameObject *temp = generateSpaceObject(imageIdx);
	gameObjectSetAngleVel(temp, (rand() / 1000 % 2) / 10);
}

int playerDistComparator(const void *vA, const void *vB)
{
	gameObject *a = (gameObject *)vA;
	gameObject *b = (gameObject *)vB;

	float px = player.params.pos.x;
	float py = player.params.pos.y;

	float aDistx = fabs(px - a->params.pos.x);
	float aDisty = fabs(py - a->params.pos.y);
	float bDistx = fabs(px - b->params.pos.x);
	float bDisty = fabs(py - b->params.pos.y);

	float aDist = sqrt((aDistx * aDistx) + (aDisty * aDisty));
	float bDist = sqrt((bDistx * bDistx) + (bDisty * bDisty));
	return aDist - bDist;
}

int main(int argc, char *argv[])
{
	// Init libs
	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	uiInit();

	// Create screens
	C3D_RenderTarget *topScreen2D = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget *bottomScreen2D = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	// Load graphics
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet)
		svcBreak(USERBREAK_PANIC);

	// Pointer to circle pad pos
	circlePadData *circlePadPos = malloc(sizeof(circlePadData));

	gameObjectFromSheet(&player, spriteSheet, 46);
	gameObjectSetCenter(&player, 0.5f, 0.53f);
	gameObjectSetPos(&player, 0, 0);
	gameObjectSetDepth(&player, 0.5);

	camera playerCam;
	cameraTopScreen(&playerCam);

	generateStars(stars, NUM_STARS);

	sprites = vector_create();

	srand(time(NULL));
	for (int i= 0; i < 100; i++)
	{
		generateMeteor((rand() % 20) + 20);
	}

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
			if (circlePadPos->dy > 20)
			{
				gameObjectAccelerate(&player, circlePadPos->dy * sin(player.params.angle) / 500, circlePadPos->dy * cos(player.params.angle) / -500);
			}

			if (abs(circlePadPos->dx) >= 40)
			{
				gameObjectRotate(&player, (float)(circlePadPos->dx + circlePadPos->dx > 0 ? -40 : 40) / -700);
			}
		}

		gameObjectUpdate(&player);

		playerCam.x = -player.params.pos.x + TOP_SCREEN_WIDTH / 2;
		playerCam.y = -player.params.pos.y + SCREEN_HEIGHT / 2;

		// sort other gameObjects by distance to player
		size_t numSprites = vector_size(sprites);
		qsort(sprites, numSprites, sizeof(gameObject), playerDistComparator);

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(topScreen2D, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(topScreen2D);
		resetCamera();

		// draw all circles before everything else
		drawStars(stars, NUM_STARS, &playerCam);

		useCamera(&playerCam);
		gameObjectDraw(&player, &playerCam);

		for (int i = 0; i < numSprites; i++)
		{
			gameObjectDraw(&sprites[i], &playerCam);
		}

		C2D_TargetClear(bottomScreen2D, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(bottomScreen2D);
		resetCamera();

		uiDrawRadar(&player, sprites, numSprites);

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
	uiFree();

	return 0;
}
