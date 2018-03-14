// Copyright 2018 Charles Cochrane

#include "./renderer.h"

#include <string>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

// TODO(charlesworth) namespace all globals
// Screen dimension constants
const int k_screen_width = 640;
const int k_screen_height = 480;

SDL_Window* CreateWindow() {
  SDL_Window* window = SDL_CreateWindow(
    "SDL",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    k_screen_width,
    k_screen_height,
    SDL_WINDOW_OPENGL);

  if (window == nullptr) {
    printf("SDL window could not be created! SDL_Error: %s\n", SDL_GetError());
    return nullptr;
  }

  SDL_GLContext gl_context = SDL_GL_CreateContext(window);

  if (SDL_GL_SetSwapInterval(1) != 0) {
    printf("SDL could not initialize with VSync! SDL_Error: %s\n", SDL_GetError());
    return nullptr;
  }

  return window;
}

SDL_Renderer* CreateRenderer(SDL_Window* window) {
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr) {
    printf("SDL renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return nullptr;
  }

  // Initialize renderer color
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  return renderer;
}

bool InitSDL() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  // Initialize SDL_IMG and PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    return false;
  }

  return true;
}

// Quit SDL subsystems
void CloseSDL() {
  IMG_Quit();
  SDL_Quit();
}

// Initializes the renderer with default window width and height
Renderer::Renderer() {
  // Start up SDL
  if (!InitSDL()) {
    printf("Failed to initialize!\n");
  }

  // Create window
  SDL_Window* window = CreateWindow();
  if (window == nullptr) {
    printf("Failed to initialize!\n");
  }

  // Create renderer
  renderer_ = CreateRenderer(window);
  if (renderer_ == nullptr) {
    printf("Failed to initialize!\n");
  }

  std::map <std::string, std::weak_ptr<SDL_Texture>> textures_;
}

struct sdl_deleter{
  void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
  void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
  void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
};

std::shared_ptr<SDL_Texture> Renderer::loadTexture(std::string path, int r, int g, int b) {
  if ( textures_.find(path) != textures_.end() ) {
    // if found check the weak_ptr is still live
    if (std::shared_ptr<SDL_Texture> shared_texture = textures_[path].lock()) {
      // still exists
      return shared_texture;
    }
  }

  SDL_Texture* new_texture = nullptr;

  // Load image at specified path
  SDL_Surface* loaded_surface = IMG_Load(path.c_str());
  if (loaded_surface == nullptr) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    return nullptr;
  }

  // Color key image
  SDL_SetColorKey(
    loaded_surface,
    SDL_TRUE,
    SDL_MapRGB(loaded_surface->format, r, g, b));

  // Create texture from surface pixels
  new_texture = SDL_CreateTextureFromSurface(renderer_, loaded_surface);
  if (new_texture == nullptr) {
    printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    return nullptr;
  }

  // Get rid of old loaded surface
  SDL_FreeSurface(loaded_surface);

  auto shared_texture = std::shared_ptr<SDL_Texture>(
    new_texture,
    sdl_deleter());

  // Add the weak_ptr to textures_ so it can be shared but not ref counted
  auto weak_shared_texture = std::weak_ptr<SDL_Texture>(shared_texture);

  textures_[path] = weak_shared_texture;

  return shared_texture;
}


std::shared_ptr<SDL_Texture> Renderer::loadTexture(std::string path) {
  if ( textures_.find(path) != textures_.end() ) {
    // if found check the weak_ptr is still live
    if (std::shared_ptr<SDL_Texture> shared_texture = textures_[path].lock()) {
      // still exists
      return shared_texture;
    }
  }

  SDL_Texture* new_texture = nullptr;

  // Load image at specified path
  SDL_Surface* loaded_surface = IMG_Load(path.c_str());
  if (loaded_surface == nullptr) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    return nullptr;
  }

  // Create texture from surface pixels
  new_texture = SDL_CreateTextureFromSurface(renderer_, loaded_surface);
  if (new_texture == nullptr) {
    printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    return nullptr;
  }

  // Get rid of old loaded surface
  SDL_FreeSurface(loaded_surface);

  auto shared_texture = std::shared_ptr<SDL_Texture>(
    new_texture,
    sdl_deleter());

  // Add the weak_ptr to textures_ so it can be shared but not ref counted
  auto weak_shared_texture = std::weak_ptr<SDL_Texture>(shared_texture);

  textures_[path] = weak_shared_texture;

  return shared_texture;
}

void Renderer::Render(std::shared_ptr<SDL_Texture> texture, int xPos, int yPos, int width, int height) {
  SDL_Rect rect;

  rect.x = xPos;
  rect.y = yPos;
  rect.w = width;
  rect.h = height;

  SDL_RenderCopy(renderer_, texture.get(), nullptr, &rect);
}

void Renderer::RenderBackground(std::shared_ptr<SDL_Texture> texture) {
  SDL_RenderCopy(renderer_, texture.get(), nullptr, nullptr);
}

void Renderer::DropTexture(std::string texture_name) {
  if (textures_[texture_name].use_count() == 1) {
    textures_.erase(texture_name);
  }
}

Renderer::~Renderer() {
  // Destroy window
  SDL_DestroyWindow(window_);
  window_ = nullptr;

  // Destroy the renderer
  SDL_DestroyRenderer(renderer_);
  renderer_ = nullptr;

  // Free resources and close SDL
  CloseSDL();
}

void Renderer::Clear() {
  SDL_RenderClear(renderer_);
}

void Renderer::DrawPresent() {
  SDL_RenderPresent(renderer_);
}
