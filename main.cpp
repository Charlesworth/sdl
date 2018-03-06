// Copyright 2018 Charles Cochrane

#include <stdio.h>
#include <string>
#include <vector>
#include <iterator>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "./renderer.h"
#include "./input.h"
#include "./object.h"

int main(int argc, char* args[]) {
  Renderer* renderer = new Renderer();
  if (renderer == NULL) {
    printf("Failed to initialize SDL renderer!\n");
    return 1;
  }

  SDL_Texture* player_texture = renderer->loadTexture("assets/man.png");
  if (player_texture == NULL) {
    printf("Failed to initialize!\n");
    return 1;
  }

  Object* charlie = new Object(player_texture, 100, 150);
  if (charlie == NULL) {
    printf("Failed to initialize player!\n");
    return 1;
  }

  SDL_Texture* background_texture = renderer->loadTexture("assets/space.png");
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

    renderer->Clear();

    // Fill screen with background image
    renderer->Render(background_texture, NULL);

    charlie->HandleInputs(inputs);
    charlie->Render(renderer);

    renderer->DrawPresent();
  }

  // Deallocate surfaces
  SDL_DestroyTexture(background_texture);
  background_texture = NULL;

  delete charlie;
  delete renderer;

  return 0;
}
