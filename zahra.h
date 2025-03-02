// zahra.h

#ifndef ZAHRA_H
#define ZAHRA_H

#include <SDL3/SDL.h>

/* Variabel global */
extern int circleX, radius;
extern float velocityY, gravity, jumpForce, maxVelocityY;
extern int gameStarted;
extern int historyIndex;
extern float circleHistory[];
extern float circleY;
extern float pipeX, pipeWidth, pipeGap, pipeSpeed;

/* Fungsi utama game */
void InitGame();
void ResetGame();
void HandleEvent(SDL_Event *event);
void UpdateGame();
void RenderGame();
int CheckCollision(float cx, float cy, float cr, SDL_FRect rect);

#endif
