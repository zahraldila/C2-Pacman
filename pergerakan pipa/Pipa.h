#ifndef PIPA_H
#define PIPA_H

#include <SDL3/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PIPE_WIDTH 80
#define PIPE_GAP 200
#define PIPE_COUNT 4
#define PIPE_SPEED 2

typedef struct {
    int x, y;
    int height;
} Pipe;

// Deklarasi fungsi
void initPipes(Pipe pipes[], int count);
void updatePipes(Pipe pipes[], int count);
void renderPipes(SDL_Renderer *renderer, Pipe pipes[], int count);

#endif
