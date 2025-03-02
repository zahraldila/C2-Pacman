#ifndef Zakky_H
#define Zakky_H

#include <SDL3/SDL.h>
#include <stdbool.h>

// Definisi tipe data Button
typedef struct {
    SDL_FRect rect;
    SDL_Color color;
} Button;

// Fungsi untuk membuat tombol
Button createButton(float x, float y, float w, float h, SDL_Color color);

// Fungsi untuk menggambar tombol
void drawButton(SDL_Renderer *renderer, Button *button);

// Fungsi untuk mengecek apakah tombol diklik
bool isButtonClicked(Button *button, float x, float y);

#endif

