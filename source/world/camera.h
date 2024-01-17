#pragma once

//gamera to display gameObjects
typedef struct
{
    // Position of the top left corner of the camera in pixels
    float x, y;

    // Width and height of the camera in pixels
    int w, h;
} camera;

void cameraTopScreen(camera *cam);

void cameraBotomScreen(camera *cam);

void useCamera(camera *cam);

void resetCamera(void);
