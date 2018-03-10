// Copyright 2018 Charles Cochrane

#include <stdio.h>
#include <string>
#include <vector>
#include <iterator>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "./renderer.h"
#include "./input.h"
#include "./object.h"

struct sdl_deleter
{
  void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
  void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
  void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
};

int main(int argc, char* args[]) {
  std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
  if (renderer == NULL) {
    printf("Failed to initialize SDL renderer!\n");
    return 1;
  }

  std::unique_ptr<SDL_Texture, sdl_deleter> player_texture = std::unique_ptr<SDL_Texture, sdl_deleter>(
    renderer->loadTexture("assets/man.png"),
    sdl_deleter());

  if (player_texture == NULL) {
    printf("Failed to initialize!\n");
    return 1;
  }

  std::unique_ptr<Object> charlie = std::make_unique<Object>(player_texture, 100, 150);
  if (charlie == NULL) {
    printf("Failed to initialize player!\n");
    return 1;
  }


  std::unique_ptr<SDL_Texture, sdl_deleter> background_texture = std::unique_ptr<SDL_Texture, sdl_deleter>(
    renderer->loadTexture("assets/space.png"),
    sdl_deleter());

  if (background_texture == nullptr) {
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

    renderer->Clear();

    // Fill screen with background image
    renderer->Render(background_texture, NULL);

    charlie->HandleInputs(inputs);
    charlie->Render(renderer);

    renderer->DrawPresent();
  }

  return 0;
}
