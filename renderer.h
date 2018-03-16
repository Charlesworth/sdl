// Copyright 2018 Charles Cochrane

#ifndef RENDERER_H_
#define RENDERER_H_

#include <string>
#include <memory>
#include <map>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "./input.h"

class Texture {
 public:
    std::shared_ptr<SDL_Texture> texture;
    int height;
    int width;
};

class Renderer {
 public:
    // Initializes the renderer with default window width and height
    Renderer();

    // Destroys the renderer
    ~Renderer();

    std::optional<Texture> loadTexture(std::string path);
    std::optional<Texture> loadTexture(std::string path, int r, int g, int b);

    void Render(Texture texture, int x_pos, int y_pos, int width, int height);
    void RenderBackground(Texture texture);
    void Clear();
    void DrawPresent();
 private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    std::map <std::string, std::weak_ptr<SDL_Texture>> textures_;
};

#endif  // RENDERER_H_
