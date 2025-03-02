#include "zahra.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[])
{
    InitGame();

    SDL_Event event;
    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            HandleEvent(&event);
        }

        UpdateGame();
        RenderGame();

        SDL_Delay(40);
    }

    return 0;
}

