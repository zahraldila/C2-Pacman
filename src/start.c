#include <SDL3/SDL.h>
#include <stdbool.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void drawButton(SDL_Renderer *renderer, SDL_FRect buttonRect, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &buttonRect);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Flappy Bird - Start", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0);

    SDL_FRect startButton = {SCREEN_WIDTH / 2.0f - 100, SCREEN_HEIGHT / 2.0f - 30, 200, 60};
    SDL_Color buttonColor = {0, 128, 255, 255};

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                float x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= startButton.x && x <= startButton.x + startButton.w &&
                    y >= startButton.y && y <= startButton.y + startButton.h) {
                    SDL_Log("Start Button Clicked!");
                    running = false; // Gantilah dengan aksi untuk memulai game
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawButton(renderer, startButton, buttonColor);
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}