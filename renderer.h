// Copyright 2018 Charles Cochrane

#ifndef RENDERER_H_
#define RENDERER_H_

#include <string>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "./input.h"

class Renderer {
 public:
    // Initializes the renderer with default window width and height
    Renderer();

    // Destroys the renderer
    ~Renderer();

    SDL_Texture* loadTexture(std::string path);

    void Render(std::unique_ptr<SDL_Texture>, SDL_Rect*);
    void Clear();
    void DrawPresent();
 private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
};

#endif  // RENDERER_H_
