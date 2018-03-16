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

int main(int argc, char* args[]) {
  auto renderer = std::make_shared<Renderer>();
  if (renderer == nullptr) {
    printf("Failed to initialize SDL renderer!\n");
    return 1;
  }

  auto player_texture_optional = renderer->loadTexture("assets/man.png", 255, 255, 255);
  if (!player_texture_optional.has_value()) {
    printf("Failed to initialize!\n");
    return 1;
  }
  auto player_texture = player_texture_optional.value();

  std::unique_ptr<Object> charlie = std::make_unique<Object>(player_texture, 100, 150);
  if (charlie == nullptr) {
    printf("Failed to initialize player!\n");
    return 1;
  }

  auto background_texture_optional = renderer->loadTexture("assets/space.png");
  if (!background_texture_optional.has_value()) {
    printf("Failed to initialize!\n");
    return 1;
  }
  auto background_texture = background_texture_optional.value();

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
    renderer->RenderBackground(background_texture);

    charlie->HandleInputs(inputs);

    renderer->Render(
      charlie->GetTexture(),
      charlie->x_position,
      charlie->y_position,
      charlie->k_player_width,
      charlie->k_player_height);

    renderer->DrawPresent();
  }

  return 0;
}
