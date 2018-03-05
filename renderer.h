// Copyright 2018 Charles Cochrane

#ifndef RENDERER_H_
#define RENDERER_H_

#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "./input.h"

class Renderer {
 public:
    // Initializes the renderer with default window width and height
    Renderer();

    // Initializes the renderer with defined window width and height
    // Renderer(int screen_width, int screen_height);

    // Destroys the renderer
    ~Renderer();

    SDL_Texture* loadTexture(std::string path);
 private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
};

#endif  // RENDERER_H_
