#pragma once

#include <3ds.h>

// circle pad position as x, y, angle, and magnitude
typedef struct
{
    // circle pad position
    s16 dx, dy;
    // circle pad direction
    float rot;
    // circle pad magnitude
    float mag;
} circlePadData;

/**
 * Get circle pad data
 * @param[out] pos Pointer to read position to
 * @param[in] deadzone Limt for smallest registered value
*/
void circlePadRead(circlePadData *pos, s16 deadzone);
