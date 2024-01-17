#include <stdlib.h>
#include <math.h>
#include <3ds.h>

#include "input.h"

void circlePadRead(circlePadData *pos, s16 deadzone)
{
    hidCircleRead((circlePosition *) pos);
    u8 flag = 0;
    if (abs(pos->dx) < deadzone) {
        pos->dx = 0;
        flag++;
    } 
    if (abs(pos->dy) < deadzone) {
        pos->dy = 0;
        flag++;
    }
    if (flag & BIT(1)) {
        pos->mag = 0;
        pos->rot = 0;
        return;
    }
    pos->mag = sqrt((pos->dx * pos->dx) + (pos->dy * pos->dy));
    pos->rot = atan2(pos->dx, pos->dy);
}
