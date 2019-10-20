#include "Window.h"
#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>
#include <iostream>

Window::Window(std::string title) {
    this->window = SDL_CreateWindow(title.c_str(), 0, 0, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    this->renderer = SDL_CreateRenderer(this->window, -1,
                                       SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!window || !renderer)
        throw std::runtime_error("No se pudo crear ventana");
}

Window::Window(std::string title, int w, int h) {
    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    this->renderer = SDL_CreateRenderer(this->window, -1,
                                        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!window)
        throw std::runtime_error("no se pudo crear ventana");
}

SDL_Texture* Window::createTextureFrom(std::string img) {
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface* aux = IMG_Load(img.c_str());
    SDL_Texture* text_ptr = SDL_CreateTextureFromSurface(this->renderer, aux);
    SDL_FreeSurface(aux);
    IMG_Quit();
    if (!aux || !text_ptr)
        throw std::runtime_error("No se pudo crear textura");


    return text_ptr;
}

void Window::render(SDL_Texture* texture, SDL_Rect &rect, SDL_Point& point, const double angle) {
    SDL_RenderCopyEx(this->renderer, texture, &rect, NULL, angle, &point, SDL_FLIP_NONE);
}

void Window::render(SDL_Texture *texture, SDL_Rect &rect) {
    SDL_Rect drawingRect = { rect.x - camera.x,
                             rect.y - camera.y,
                             rect.h - camera.w,
                             rect.w - camera.w };
    SDL_RenderCopy(this->renderer, texture, NULL, &drawingRect);
}

void Window::update() {
    SDL_RenderPresent(this->renderer);
}

void Window::clear() {
    SDL_RenderClear(this->renderer);
}

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}



