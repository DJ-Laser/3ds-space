#include <math.h>
#include <citro2d.h>

#include "gameObject.h"

static const camera topCam = {.x = 0, .y = 0, .w = 400, .h = 240};
static const camera bottomCam = {.x = 0, .y = 0, .w = 320, .h = 240};

void gameObjectSetPos(gameObject *object, float px, float py)
{
    object->params.pos.x = px;
    object->params.pos.y = py;
}

void gameObjectSetVel(gameObject *object, float dx, float dy)
{
    object->dx = dx;
    object->dy = dy;
}

void gameObjectSetRot(gameObject *object, float pr)
{
    object->params.angle = pr;
}

void GameObjectSetRotDegrees(gameObject *object, float pr)
{
    gameObjectSetRot(object, C3D_AngleFromDegrees(pr));
}

void gameObjectSetAngleVel(gameObject *object, float dr)
{
    object->dr = dr;
}

void GameObjectSetAngleVelDegrees(gameObject *object, float dr)
{
    gameObjectSetRot(object, C3D_AngleFromDegrees(dr));
}

void gameObjectSetScale(gameObject *object, float w, float h)
{
    float oldCenterX = object->params.center.x / object->params.pos.w;
    float oldCenterY = object->params.center.y / object->params.pos.h;
    object->params.pos.w = w * object->image.subtex->width;
    object->params.pos.h = h * object->image.subtex->height;
    object->params.center.x = fabsf(oldCenterX * object->params.pos.w);
    object->params.center.y = fabsf(oldCenterY * object->params.pos.h);
}

void gameObjectSetScaleRaw(gameObject *object, float w, float h)
{
    float oldCenterX = object->params.center.x / object->params.pos.w;
    float oldCenterY = object->params.center.y / object->params.pos.h;
    object->params.pos.w = w;
    object->params.pos.h = h;
    object->params.center.x = fabsf(oldCenterX * w);
    object->params.center.y = fabsf(oldCenterY * h);
}

void gameObjectSetCenter(gameObject *object, float x, float y)
{
    object->params.center.x = x * object->params.pos.w;
    object->params.center.y = y * object->params.pos.h;
}

void gameObjectSetCenterRaw(gameObject *object, float x, float y)
{
    object->params.center.x = x;
    object->params.center.y = y;
}

void gameObjectSetDepth(gameObject *object, float depth)
{
    object->params.depth = depth;
}

void gameObjectTranslate(gameObject *object, float dx, float dy)
{
    object->params.pos.x += dx;
    object->params.pos.y += dy;
}

void gameObjectAccelerate(gameObject *object, float dx, float dy)
{
    object->dx += dx;
    object->dy += dy;
}

void gameObjectRotate(gameObject *object, float dr)
{
    object->params.angle += dr;
}

void gameObjectRotateDegrees(gameObject *object, float dr)
{
    gameObjectRotate(object, C3D_AngleFromDegrees(dr));
}

void gameObjectAngleAccelerate(gameObject *object, float dr)
{
    object->dr += dr;
}

void gameObjectAngleAccelerateDegrees(gameObject *object, float dr)
{
    gameObjectRotate(object, C3D_AngleFromDegrees(dr));
}

void gameObjectScale(gameObject *object, float w, float h)
{
    object->params.pos.w *= w;
    object->params.pos.h *= h;
    object->params.center.x *= w;
    object->params.center.y *= h;
}

void gameObjectFromImage(gameObject *object, C2D_Image image)
{
    object->image = image;
    object->params.pos.x = 0.0f;
    object->params.pos.y = 0.0f;
    object->params.pos.w = image.subtex->width;
    object->params.pos.h = image.subtex->height;
    object->params.center.x = 0.0f;
    object->params.center.y = 0.0f;
    object->params.angle = 0.0f;
    object->params.depth = 0.0f;
}

void gameObjectFromSheet(gameObject *object, C2D_SpriteSheet sheet, size_t index)
{
    gameObjectFromImage(object, C2D_SpriteSheetGetImage(sheet, index));
}

void gameObjectDeltaUpdate(gameObject *object, float physicsDelta)
{
    object->params.pos.x += object->dx * physicsDelta;
    object->params.pos.y += object->dy * physicsDelta;
    object->params.angle += object->dr * physicsDelta;
}

void gameObjectUpdate(gameObject *object)
{
    gameObjectDeltaUpdate(object, 1);
}

bool gameObjectDraw(const gameObject *object, const camera *cam)
{
    // this is easier than getting rotated width / height
    float radius = fmax(object->params.pos.w - object->params.center.x, object->params.pos.h - object->params.center.y);

    // dont draw if offscreen
    if (object->params.pos.x + radius < -cam->x || object->params.pos.x - radius > -cam->x + cam->w ||
        object->params.pos.y + radius < -cam->y || object->params.pos.y - radius > -cam->y + cam->h)
    {
        return false;
    }

    C2D_DrawImage(object->image, &object->params, NULL);
    return true;
}

bool gameObjectDrawTopScreen(const gameObject *object)
{
    return gameObjectDraw(object, &topCam);
}

bool gameObjectDrawBottomScreen(const gameObject *object)
{
    return gameObjectDraw(object, &bottomCam);
}
