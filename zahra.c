// zahra.c

#include "zahra.h"
#include <stdlib.h>
#include <math.h>

/* Variabel Global */
int circleX = 150;
int radius = 20;
float velocityY = 0;
float gravity = 0.5f;      // ✅ Gravitasi lebih besar agar jatuh lebih cepat
float jumpForce = -4.5f;   // ✅ Loncat lebih tinggi
float maxVelocityY = -8;   // ✅ Batasi kecepatan naik agar lebih smooth
int gameStarted = 0;
int historyIndex = 0;
float circleHistory[5] = {240, 240, 240, 240, 240};
float circleY = 240;
float pipeX = 640.0f;
float pipeWidth = 60.0f;
float pipeGap = 100.0f;
float pipeSpeed = 5;    // ✅ Pipa bergerak lebih cepat agar tantangan meningkat



/* Variabel SDL */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

/* Fungsi menggambar lingkaran */
void DrawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

/* Inisialisasi Game */
void InitGame()
{
    SDL_SetAppMetadata("Flappy Bird", "1.0", "com.c2.example");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        exit(1);
    }

    if (!SDL_CreateWindowAndRenderer("Flappy Bird", 640, 480, 0, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        exit(1);
    }

    ResetGame();
}

/* Fungsi Reset Game */
void ResetGame()
{
    circleX = 150;
    circleY = 240;
    velocityY = 0;
    gameStarted = 0;
    pipeX = 640.0f;

    for (int i = 0; i < 5; i++)
    {
        circleHistory[i] = 240;
    }
}

/* Handle Input */
void HandleEvent(SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        exit(0);
    }
    else if (event->type == SDL_EVENT_KEY_DOWN)
    {
        if (event->key.scancode == SDL_SCANCODE_SPACE)
        {
            if (!gameStarted)
            {
                gameStarted = 1;
            }
            velocityY += jumpForce;

            if (velocityY < maxVelocityY)
            {
                velocityY = maxVelocityY;
            }
        }
    }
}

/* Update Game */
void UpdateGame()
{
    if (gameStarted)
    {
        velocityY += gravity;
        if (velocityY > 1.5)
        {
            velocityY = 1.5;
        }

        historyIndex = (historyIndex + 1) % 5;
        circleHistory[historyIndex] = circleY + velocityY;
        circleY = circleHistory[historyIndex];

        pipeX -= pipeSpeed;

        if (pipeX + pipeWidth < 0)
        {
            pipeX = 640.0f;
        }

        if (circleY >= 460 - radius)
        {
            ResetGame();
        }

        if (circleY < 10)
        {
            circleY = 10;
            velocityY = 0;
        }
    }
}

/* Render Game */
void RenderGame()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    DrawCircle(renderer, circleX, (int)circleY, radius);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    SDL_FRect topPipe = {pipeX, 0.0f, pipeWidth, (480.0f - pipeGap) / 2.0f};
    SDL_RenderFillRect(renderer, &topPipe);

    SDL_FRect bottomPipe = {pipeX, 480.0f - ((480.0f - pipeGap) / 2.0f), pipeWidth, (480.0f - pipeGap) / 2.0f};
    SDL_RenderFillRect(renderer, &bottomPipe);

    if (CheckCollision(circleX, circleY, radius, topPipe) || CheckCollision(circleX, circleY, radius, bottomPipe))
    {
        ResetGame();
    }

    SDL_RenderPresent(renderer);
}

/* Fungsi untuk mengecek apakah lingkaran bertabrakan dengan pipa */
int CheckCollision(float cx, float cy, float cr, SDL_FRect rect)
{
    float nearestX = fmax(rect.x, fmin(cx, rect.x + rect.w));
    float nearestY = fmax(rect.y, fmin(cy, rect.y + rect.h));

    float dx = cx - nearestX;
    float dy = cy - nearestY;

    return (dx * dx + dy * dy) <= (cr * cr);
}
