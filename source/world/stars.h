#pragma once

#include <3ds.h>

#include "camera.h"

// a background element consisting of a small curcle
typedef struct
{
    // position of the star
    float px, py;
    // size of the star
    float radius;
} star;

/**
 * Generate some random stars
 * @param[out] star pointer to array of stars
 * @param[in] number of stars to write, should not be more than array length
*/
void generateStars(star array[], size_t numStars);

/**
 * draw stars to the screen
 * @param[out] star pointer to array of stars
 * @param[in] number of stars to draw, should not be more than array length
 * @param[in] cam Pointer to settings for the camera
*/
void drawStars(const star array[], size_t numStars, const camera *cam);
