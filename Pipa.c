// fitur yang ada pada branch ini mengatur pergerakan pipa dan tabrakan
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PIPE_WIDTH 80
#define PIPE_GAP 150
#define PIPE_COUNT 5
#define PIPE_SPEED 2

typedef struct {
    int x, y;
    int height;
} Pipe;

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

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Flappy Bird Pipes", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Pipe pipes[PIPE_COUNT];
    initPipes(pipes, PIPE_COUNT);
    
    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        updatePipes(pipes, PIPE_COUNT);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderPipes(renderer, pipes, PIPE_COUNT);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}