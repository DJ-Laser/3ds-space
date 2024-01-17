#pragma once

#include "camera.h"

// An object in space
typedef struct
{
    C2D_Image image;
    C2D_DrawParams params;
    // velocity in pixels / update
    float dx, dy;
    // angular velocity in radians / update
    float dr;
} gameObject;

/**
 * Set the position of the gameObject
 * @param[out] object Pointer to object
 * @param[in] px X position
 * @param[in] py Y position
 */
void gameObjectSetPos(gameObject *object, float px, float py);

/**
 * Set the velocity of the gameObject
 * @param[out] object Pointer to object
 * @param[in] px X velocity
 * @param[in] py Y velocity
 */
void gameObjectSetVel(gameObject *object, float dx, float dy);

/**
 * Set the rotation of the gameObject
 * @param[out] object Pointer to object
 * @param[in] pr angle in radians
 */
void gameObjectSetRot(gameObject *object, float pr);

/**
 * Set the rotation of the gameObject
 * @param[out] object Pointer to object
 * @param[in] pr angle in degrees
 */
void gameObjectSetRotDegrees(gameObject *object, float pr);

/**
 * Set the angular velocity of the gameObject
 * @param[out] object Pointer to object
 * @param[in] dr angular velocity in radians / update
 */
void gameObjectSetAngleVel(gameObject *object, float dr);

/**
 * Set the angular velocity of the gameObject
 * @param[out] object Pointer to object
 * @param[in] dr angular velocity in degrees / update
 */
void GameObjectSetAngleVelDegrees(gameObject *object, float dr);

/**
 * Set the scale of the gameObject
 * @param[out] object gameObject Pointer to object
 * @param[in] w width (1.0f is default scaling)
 * @param[in] h height (1.0f is default scaling)
 */
void gameObjectSetScale(gameObject *object, float w, float h);

/**
 * Set the raw scale of the gameObject
 * @param[out] object Pointer to object
 * @param[in] w raw width in pixels
 * @param[in] h raw height in pixels
 */
void gameObjectSetScaleRaw(gameObject *object, float w, float h);

/**
 * Set the center of the gameObject
 * @param[in] object Pointer to object
 * @param[in] x X position of the center (0.5f is centered)
 * @param[in] y Y position of the center (0.5f is centered)
 */
void gameObjectSetCenter(gameObject *object, float x, float y);

/**
 * Set the raw center of the gameObject
 * @param[in] object Pointer to object
 * @param[in] x raw X position of the center in pixels
 * @param[in] y raw Y position of the center in pixels
 */
void gameObjectSetCenterRaw(gameObject *object, float x, float y);

/**
 * Sets the depth level of a object (absolute)
 * @param[in] object Pointer to object
 * @param[in] depth Depth value
 */
void gameObjectSetDepth(gameObject *object, float depth);

/**
 * Translate the gameObject by dx and dy
 * @param[out] object Pointer to object
 * @param[in] dx X translation
 * @param[in] dy Y translation
 */
void gameObjectTranslate(gameObject *object, float dx, float dy);

/**
 * Accelerate the gameObject by dx and dy
 * @param[out] object Pointer to object
 * @param[in] dx X acceleration
 * @param[in] dy Y acceleration
 */
void gameObjectAccelerate(gameObject *object, float dx, float dy);

/**
 * Rotate the gameObject by dr
 * @param[out] object Pointer to object
 * @param[in] pr angle in radians
 */
void gameObjectRotate(gameObject *object, float dr);

/**
 * Rotate the gameObject by dr
 * @param[out] object Pointer to object
 * @param[in] pr angle in degrees
 */
void gameObjectRotateDegrees(gameObject *object, float dr);

/**
 * Angular accelerate the gameObject by dr
 * @param[out] object Pointer to object
 * @param[in] pr angular acceleration in radians / update
 */
void gameObjectAngleAccelerate(gameObject *object, float dr);

/**
 * Angular accelerate the gameObject by dr
 * @param[out] object Pointer to object
 * @param[in] pr angular acceleration in degrees / update
 */
void gameObjectAngleAccelerateDegrees(gameObject *object, float dr);

/**
 * Scale gameObject
 * @param[out] object gameObject Pointer to object
 * @param[in] w width (2.0f is float previous scale)
 * @param[in] h height (2.0f is float previous scale)
 */
void gameObjectScale(gameObject *object, float w, float h);

/**
 * Initializes a object from an image
 * @param[out] object Pointer to object
 * @param[in] image Image to use
 */
void gameObjectFromImage(gameObject *object, C2D_Image image);

/**
 * Initializes a object from an image stored in a object sheet
 * @param[out] object Pointer to object
 * @param[in] sheet object sheet handle
 * @param[in] index Index of the image inside the object sheet
 */
void gameObjectFromSheet(gameObject *object, C2D_SpriteSheet sheet, size_t index);

/**
 * Update position and rotation based on velocities
 * @param[out] object pointer to object
 * @param[in] physicsDelta multiplier for position change
 */
void gameObjectDeltaUpdate(gameObject *object, float physicsDelta);

/**
 * Update position and rotation based on velocities
 * @param[out] object pointer to object
 */
void gameObjectUpdate(gameObject *object);

/**
 * Draw the gameObject with a set camera
 * @param[in] object Pointer to object
 * @param[in] cam Pointer to settings for the camera
 * @return true if object was drawn, false otherwise
 */
bool gameObjectDraw(const gameObject *object, const camera *cam);

/**
 * Draw the gameObject with the default camera for top screen
 * @param[in] onject Pointer to object
 * @return true if object was drawn, false otherwise
 */
bool gameObjectDrawTopScreen(const gameObject *object);

/**
 * Draw the gameObject with the default camera for bottom screen
 * @param[in] onject Pointer to object
 * @return true if object was drawn, false otherwise
 */
bool gameObjectDrawBottomScreen(const gameObject *object);
