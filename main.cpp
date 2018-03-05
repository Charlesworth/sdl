// Copyright 2018 Charles Cochrane

#include <stdio.h>
#include <string>
#include <vector>
#include <iterator>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "./input.h"
#include "./player.h"

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

  if (window == NULL) {
    printf("SDL window could not be created! SDL_Error: %s\n", SDL_GetError());
    return NULL;
  }

  SDL_GLContext gl_context = SDL_GL_CreateContext(window);

  if (SDL_GL_SetSwapInterval(1) != 0) {
    printf("SDL could not initialize with VSync! SDL_Error: %s\n", SDL_GetError());
    return NULL;
  }

  return window;
}

SDL_Renderer* CreateRenderer(SDL_Window* window) {
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
    printf("SDL renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return NULL;
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

// TODO(charlesworth) this is a mess, sort error handling
SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer) {
  SDL_Texture* newTexture = NULL;

  // Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    return NULL;
  }

  // Create texture from surface pixels
  newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
  if (newTexture == NULL) {
    printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    return NULL;
  }

  // Get rid of old loaded surface
  SDL_FreeSurface(loadedSurface);

  return newTexture;
}

int main(int argc, char* args[]) {
  // Start up SDL
  if (!InitSDL()) {
    printf("Failed to initialize!\n");
    return 1;
  }

  // Create window
  SDL_Window* window = CreateWindow();
  if (window == NULL) {
    printf("Failed to initialize!\n");
    return 1;
  }

  // Create renderer
  SDL_Renderer* renderer = CreateRenderer(window);
  if (renderer == NULL) {
    printf("Failed to initialize!\n");
    return 1;
  }

  SDL_Texture* player_texture = loadTexture("assets/man.png", renderer);
  if (player_texture == NULL) {
    printf("Failed to initialize!\n");
    return 1;
  }

  Player* charlie = new Player(player_texture, 100, 150);

  SDL_Texture* background_texture = loadTexture("assets/space.png", renderer);
  if (background_texture == NULL) {
    printf("Failed to initialize!\n");
    return 1;
  }

  bool quit = false;
  while (!quit) {
    // Handle events
    std::set<Input> inputs = GetInputs();

    if (inputs.count(Input::QUIT)) {
      // User requests quit
      quit = true;
    }

    SDL_RenderClear(renderer);

    // Fill screen with background image
    SDL_RenderCopy(renderer, background_texture, NULL, NULL);

    charlie->HandleInputs(inputs);
    charlie->Render(renderer);

    SDL_RenderPresent(renderer);
  }

  // Deallocate surfaces
  SDL_DestroyTexture(background_texture);
  background_texture = NULL;

  delete charlie;

  // Destroy window
  SDL_DestroyWindow(window);
  window = NULL;

  // Destroy the renderer
  SDL_DestroyRenderer(renderer);
  renderer = NULL;

  // Free resources and close SDL
  CloseSDL();

  return 0;
}
