#include "Texture.h"
#include "Window.h"
#include <SDL2/SDL.h>
#include <iostream>

Texture::Texture(SDL_Texture* txd, Window& mainWindow) :
    window(mainWindow) {
        this->texture = txd;
}

Texture::Texture(Texture&& other) :
    window(other.window) {
        this->texture = other.texture;
        other.texture = NULL;
}

void Texture::render(SDL_Rect& dimensions) {
    this->window.render(this->texture, dimensions);
}

Texture::~Texture() {
    if (texture != nullptr)
        SDL_DestroyTexture(this->texture);
}
