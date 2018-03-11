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

    std::shared_ptr<SDL_Texture> loadTexture(std::string path);
    std::shared_ptr<SDL_Texture> loadTextureColorKey(std::string path, int red, int green, int blue);

    void Render(std::shared_ptr<SDL_Texture> texture, int xPos, int yPos, int width, int height);
    void RenderBackground(std::shared_ptr<SDL_Texture> texture);
    void Clear();
    void DrawPresent();
 private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
};

#endif  // RENDERER_H_
