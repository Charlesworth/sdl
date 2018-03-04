// Copyright 2018 Charles Cochrane

#include <stdio.h>
#include <string>
#include <vector>
#include <iterator>
#include <memory>

#include "SDL2/SDL.h"

#include "./input.h"
#include "./player.h"

// TODO(charlesworth) namespace all globals
// Screen dimension constants
const int k_screen_width = 640;
const int k_screen_height = 480;

// Frame rate constants
const int k_60_fsp_single_frame_ms = 16;
const int k_30_fsp_single_frame_ms = 32;
const int k_1_fsp_single_frame_ms = 1000;

// TODO(charlesworth) remove as a global var
// The window we'll be rendering to
SDL_Window* g_sdl_window = NULL;

// TODO(charlesworth) remove as a global var
// The surface contained by the window
SDL_Surface* g_sdl_screen_surface = NULL;

// Starts up SDL and creates window
bool Init() {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    g_sdl_window = SDL_CreateWindow(
      "SDL",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      k_screen_width,
      k_screen_height,
      SDL_WINDOW_SHOWN);

    if (g_sdl_window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Get window surface
      g_sdl_screen_surface = SDL_GetWindowSurface(g_sdl_window);
    }
  }

  return success;
}

// Frees media and shuts down SDL
void Close() {
  // Destroy window
  SDL_DestroyWindow(g_sdl_window);
  g_sdl_window = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

// Load image at specified path
SDL_Surface* LoadBMPSurface(std::string path) {
  SDL_Surface* loaded_surface = SDL_LoadBMP(path.c_str());
  if (loaded_surface == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    return NULL;
  }

  // Convert surface to screen format
  SDL_Surface* optimized_surface = SDL_ConvertSurface(loaded_surface, g_sdl_screen_surface->format, 0);
  if (optimized_surface == NULL) {
    printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    return NULL;
  }

  // Get rid of old loaded surface
  SDL_FreeSurface(loaded_surface);

  return optimized_surface;
}

int main(int argc, char* args[]) {
  bool quit = false;

  // Start up SDL and create window
  if (!Init()) {
    printf("Failed to initialize!\n");
    return 1;
  }

  SDL_Surface* player_texture = LoadBMPSurface("assets/man.bmp");
  if (player_texture == NULL) {
    quit = true;
  }

  Player* charlie = new Player(player_texture, 100, 150);

  // Background image
  SDL_Surface* background_texture = LoadBMPSurface("assets/space.bmp");
  if (background_texture == NULL) {
    quit = true;
  }

  int tick = 0;

  while (!quit) {
    // Fill screen with background image
    SDL_BlitSurface(background_texture, NULL, g_sdl_screen_surface, NULL);

    // Handle events
    std::set<Input> inputs = GetInputs();

    if (inputs.count(Input::QUIT)) {
      // User requests quit
      quit = true;
    }

    charlie->HandleInputs(inputs);
    charlie->Render(g_sdl_screen_surface);

    // Update the surface
    SDL_UpdateWindowSurface(g_sdl_window);

    SDL_Delay(k_60_fsp_single_frame_ms);
    tick++;
  }

  // Deallocate surfaces
  SDL_FreeSurface(background_texture);
  background_texture = NULL;

  delete charlie;

  // Free resources and close SDL
  Close();

  return 0;
}
