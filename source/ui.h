#pragma once

#define TOP_SCREEN_WIDTH 400
#define BOTTOM_SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#include "vec.h"
#include "world/gameObject.h"

void uiInit(void);

void uiFree(void);

void uiDrawRadar(gameObject *player, gameObject* sprites, size_t numSprites);
