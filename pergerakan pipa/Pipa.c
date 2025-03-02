// fitur yang ada pada branch ini mengatur pergerakan pipa dan tabrakan
#include "Pipa.h"
#include <stdlib.h>


void initPipes(Pipe pipes[], int count) {
    for (int i = 0; i < count; i++) {
        pipes[i].x = SCREEN_WIDTH + i * 200;
        pipes[i].height = rand() % (SCREEN_HEIGHT / 2) + 100;
        pipes[i].y = pipes[i].height + PIPE_GAP;
    }
}

void updatePipes(Pipe pipes[], int count) {
    for (int i = 0; i < count; i++) {
        pipes[i].x -= PIPE_SPEED;
        if (pipes[i].x + PIPE_WIDTH < 0) {
            pipes[i].x = SCREEN_WIDTH;
            pipes[i].height = rand() % (SCREEN_HEIGHT / 2) + 100;
            pipes[i].y = pipes[i].height + PIPE_GAP;
        }
    }
}

void renderPipes(SDL_Renderer *renderer, Pipe pipes[], int count) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < count; i++) {
        SDL_FRect topPipe = {pipes[i].x, 0, PIPE_WIDTH, pipes[i].height};
        SDL_FRect bottomPipe = {pipes[i].x, pipes[i].y, PIPE_WIDTH, SCREEN_HEIGHT - pipes[i].y};
        SDL_RenderFillRect(renderer, &topPipe);
        SDL_RenderFillRect(renderer, &bottomPipe);
    }
}

