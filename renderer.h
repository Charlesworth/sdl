// Copyright 2018 Charles Cochrane

#ifndef RENDERER_H_
#define RENDERER_H_

#include <string>
#include <memory>
#include <map>

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
    std::shared_ptr<SDL_Texture> loadTexture(std::string path, int r, int g, int b);

    void Render(std::shared_ptr<SDL_Texture> texture, int x_pos, int y_pos, int width, int height);
    void RenderBackground(std::shared_ptr<SDL_Texture> texture);
    void Clear();
    void DrawPresent();
 private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    std::map <std::string, std::weak_ptr<SDL_Texture>> textures_;
};

class Texture {
 public:
    // Initializes the texture with width and height
    Texture(std::shared_ptr<SDL_Texture> texture, int width, int height, std::string path)
    : texture(texture), width(width), height(height), path(path) {}

    // Destroys the texture
    ~Texture() {}

    std::shared_ptr<SDL_Texture> texture;
    std::string path;
    int height;
    int width;
};

#endif  // RENDERER_H_
