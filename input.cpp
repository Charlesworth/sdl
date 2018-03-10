// Copyright 2018 Charles Cochrane

#include <vector>
#include <set>

#include "SDL2/SDL.h"

#include "./input.h"

std::set<Input> GetInputs() {
  SDL_Event event;

  while (SDL_PollEvent(&event) != 0) {
    // Check for quit events
    if (event.type == SDL_QUIT) {
      return std::set<Input>{QUIT};
    }
  }

  // All events must be processed before checking GetKeyboardState
  const Uint8 *keys = SDL_GetKeyboardState(nullptr);

  // Check for quit keys
  if (keys[SDL_SCANCODE_ESCAPE]) {
      return std::set<Input>{QUIT};
  }

  // Process key presses
  std::set<Input> inputSet;

  if (keys[SDL_SCANCODE_RETURN]) {
      inputSet.insert(ENTER);
  }

  if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) {
      inputSet.insert(UP);
  }

  if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) {
      inputSet.insert(DOWN);
  }

  if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
      inputSet.insert(LEFT);
  }

  if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
      inputSet.insert(RIGHT);
  }

  return inputSet;
}
