#include "Zakky.h"

// Fungsi untuk membuat tombol dengan ukuran dan warna tertentu
Button createButton(float x, float y, float w, float h, SDL_Color color) {
    Button button;
    button.rect.x = x;
    button.rect.y = y;
    button.rect.w = w;
    button.rect.h = h;
    button.color = color;
    return button;
}

// Fungsi untuk menggambar tombol
void drawButton(SDL_Renderer *renderer, Button *button) {
    SDL_SetRenderDrawColor(renderer, button->color.r, button->color.g, button->color.b, button->color.a);
    SDL_RenderFillRect(renderer, &button->rect);
}

// Fungsi untuk mengecek apakah tombol diklik
bool isButtonClicked(Button *button, float x, float y) {
    return (x >= button->rect.x && x <= button->rect.x + button->rect.w &&
            y >= button->rect.y && y <= button->rect.y + button->rect.h);
}
