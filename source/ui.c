#include <stdlib.h>
#include <math.h>
#include <3ds.h>
#include <citro2d.h>

#include "ui.h"
#include "vec.h"
#include "world/gameObject.h"

static C2D_SpriteSheet uiSheet;
static C2D_Image radarScreen;
static C2D_Image radarArrrow;

void uiInit(void)
{
    uiSheet = C2D_SpriteSheetLoad("romfs:/gfx/ui.t3x");
    if (!uiSheet)
		svcBreak(USERBREAK_PANIC);

    radarScreen = C2D_SpriteSheetGetImage(uiSheet, 0);
    radarArrrow = C2D_SpriteSheetGetImage(uiSheet, 1);
}

void uiFree(void)
{
    C2D_SpriteSheetFree(uiSheet);
}

void uiDrawRadar(gameObject *player, gameObject* sprites, size_t numSprites) {
    C2D_DrawImageAt(radarScreen, 40, 0, 0, NULL, 1, 1);
    C2D_DrawImageAtRotated(radarArrrow, BOTTOM_SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.5, player->params.angle,  NULL, 1, 1);
    
    for (size_t i = 0; i < fmin(numSprites, 150); i++)
    {
        gameObject *object = &sprites[i];

        float radarX = (-player->params.pos.x + object->params.pos.x) / 100;
        float radarY = (-player->params.pos.y + object->params.pos.y) / 100;

        float radarMag = sqrt((radarX * radarX) + (radarY * radarY));
        float radarRot = atan2(radarX, radarY);

        if (radarMag > 105) {
            radarMag = 105;
            radarX = radarMag * sin(radarRot);
            radarY = radarMag * cos(radarRot);
        }

        C2D_DrawCircleSolid(
            radarX + BOTTOM_SCREEN_WIDTH / 2, 
            radarY + SCREEN_HEIGHT / 2,
            1, 1, C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f)
        );
    }
}
