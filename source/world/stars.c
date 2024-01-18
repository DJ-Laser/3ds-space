#include <stdlib.h>
#include <time.h>
#include <citro2d.h>

#include "stars.h"
#include "camera.h"

#define STAR_MAP_SIZE 1000
#define STAR_SCROLL_SPEED 10
#define SCROLL_RADIUS_MUL 0.5

void generateStars(star array[], size_t numStars)
{
    srand(time(NULL));
    for (size_t i = 0; i < numStars; i++)
    {
        star *item = &array[i];
        item->radius = (rand() / 100 % 3) + 1;
        item->px = (rand() / 100 % (STAR_MAP_SIZE));
        item->py = (rand() / 100 % (STAR_MAP_SIZE));
    }
}

void drawStars(const star array[], size_t numStars, const camera *cam)
{
    srand(cam->x * cam->y);
    for (size_t i = 0; i < numStars; i++)
    {
        const star *item = &array[i];
        int x = ((int)(item->px + cam->x / (STAR_SCROLL_SPEED - SCROLL_RADIUS_MUL * item->radius)) % STAR_MAP_SIZE + STAR_MAP_SIZE) % STAR_MAP_SIZE;
        int y = ((int)(item->py + cam->y / (STAR_SCROLL_SPEED - SCROLL_RADIUS_MUL * item->radius)) % STAR_MAP_SIZE + STAR_MAP_SIZE) % STAR_MAP_SIZE;
        C2D_DrawCircleSolid(x, y, 0, item->radius, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF));
    }
}