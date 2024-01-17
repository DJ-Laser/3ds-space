#include <citro2d.h>

#include "camera.h"

void cameraTopScreen(camera *cam)
{
    cam->x = 0;
    cam->y = 0;
    cam->w = 400;
    cam->h = 240;
}

void cameraBotomScreen(camera *cam)
{
    cam->x = 0;
    cam->y = 0;
    cam->w = 320;
    cam->h = 240;
}

void useCamera(camera *cam)
{
    C2D_ViewReset();
    C2D_ViewTranslate(cam->x, cam->y);
}

void resetCamera(void)
{
    C2D_ViewReset();
}
